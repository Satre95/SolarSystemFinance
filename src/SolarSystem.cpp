#include "SolarSystem.hpp"
#include "Utilities.hpp"

double SSParticle::mass = 20000;

SolarSystem::SolarSystem(vector<string> & stockSymbols, int numParticles):
numThreads( ofClamp(std::thread::hardware_concurrency(), 2, 128))

{
    numParticles = Utilities::roundUp(numParticles, numThreads-1);
    this->numParticles = numParticles;
	this->numPlanets = (int)stockSymbols.size();
	this->stocks = stockSymbols;

	//Init the particles
	for (int i = 0; i < numParticles; i++) {
		particles.emplace_back(Utilities::randomPointBetweenSpheres(1000.0f, 3000.0f));
	}

	//Init the planets
	for (int j = 0; j < numPlanets; j++) {
		ofVec3f pos = Utilities::randomPointBetweenSpheres(1000.0f, 3000.0f);
		ofVec3f vel = Utilities::randomPointBetweenSpheres(10, 50);
		planets.emplace_back(pos,
							vel,
							ofRandom(2000, 4000));
	}

	//setup shaders
	celestialShader.load("CelestialShaderVert.glsl", "CelestialShaderFrag.glsl");
	//Setup buffers and vbo's
	initBuffers();

	//Load the texture for the billboards
	ofDisableArbTex();
	planetImage.load("Planet.png");
	particleImage.load("Particle.png");
	ofEnableAlphaBlending();

	//Setup the texcoords

	dataFetcher.stocksPtr = &stocks;
	dataFetcher.planetsPtr = &planets;
	dataFetcher.startThread(true);

}

void SolarSystem::initBuffers() {
	//allocated the particles buffer and setup pointer for shader
	particlesBuf.allocate(particles, GL_DYNAMIC_DRAW);
	particlesVbo.setAttributeBuffer(celestialShader.getAttributeLocation("position"),
		particlesBuf,
		4,
		sizeof(SSParticle),
		offsetof(SSParticle, pos));
	particlesVbo.setAttributeBuffer(celestialShader.getAttributeLocation("color"),
		particlesBuf,
		4,
		sizeof(SSParticle),
		offsetof(SSParticle, color));

	//allocated the planets buffer and setup the poointer for the shader.
	planetsBuf.allocate(planets, GL_DYNAMIC_DRAW);
	int loc = celestialShader.getAttributeLocation("position");
	int loc2 = celestialShader.getAttributeLocation("color");
	planetsVbo.setAttributeBuffer(celestialShader.getAttributeLocation("position"),
		planetsBuf,
		4,
		sizeof(SSPlanet),
		offsetof(SSPlanet, pos));
	planetsVbo.setAttributeBuffer(celestialShader.getAttributeLocation("color"),
		planetsBuf,
		4,
		sizeof(SSPlanet),
		offsetof(SSPlanet, color));
}


void SolarSystem::draw() {
	drawParticles();
	drawPlanets();
    
    for(int i = 0; i < (int)planets.size(); i++) {
        auto & aPlanet = planets.at(i);
        ofDrawBitmapString(stocks.at(i), aPlanet.pos.x, aPlanet.pos.y,aPlanet.pos.z);
    }
}

void SolarSystem::drawParticles() {
	celestialShader.begin();
	particleImage.getTexture().bind();
    glPointSize(8.0f);
	particlesVbo.draw(GL_POINTS, 0, numParticles);
	particleImage.getTexture().unbind();
	celestialShader.end();
}

void SolarSystem::drawPlanets() {
	celestialShader.begin();
	planetImage.getTexture().bind();
    glPointSize(20.0f);
	planetsVbo.draw(GL_POINTS, 0, numPlanets);
	planetImage.getTexture().unbind();
	celestialShader.end();
}

void SolarSystem::update() {
	updatePlanets();
	updateParticles();
	if (!dataFetcher.isThreadRunning()) {
		dataFetcher.startThread(true);
	}
}

void SolarSystem::updateParticles() {
    vector<thread> threads;
    //figure out starting points.
    int start = 0;
    int chunkSize = (int)particles.size() / (numThreads - 1);
    
    while (start < particles.size()) {
        threads.emplace_back(&SolarSystem::threadedUpdateParticles, this, ref(particles), start, start + chunkSize, ref(planets));
        start += chunkSize;
    }
    
    for(auto & aThread: threads)
        aThread.join();
    
	//Update buffer and vbo
	particlesBuf.updateData(particles);
}

void SolarSystem::updatePlanets() { 
    vector<thread> threads;
    //figure out starting points
    int start = 0;
    int chunkSize = (int)planets.size() / (numThreads - 1);
    while(start < planets.size()) {
        int end = ofClamp(start + chunkSize, start, planets.size());
        threads.emplace_back(&SolarSystem::threadedUpdatePlanets, this, ref(planets), start, end);
        start += chunkSize;
    }
    
    for(auto & aThread: threads)
        aThread.join();
    
	//Update the buffer
	planetsBuf.updateData(planets);
}

void SolarSystem::StockUpdater::threadedFunction() {
	auto & stocks = *stocksPtr;
	auto & planets = *planetsPtr;
	ofxJSONElement json;

	for (int i = 0; i < stocks.size(); i++) {
		string & aStock = stocks.at(i);
		ofHttpResponse resp = ofLoadURL(stockURL + aStock);
		string data = resp.data.getText();
		data.erase(0, 6);
		data.erase(data.end() - 2, data.end());

		bool parseSuccess = json.parse(data);

		if (parseSuccess) {
			ofLogNotice() << "Stock " << json["t"].asString() << " price is " << json["l"].asString();
			float price = std::stof(json["l"].asString());
            planets.at(i).setMass(price * stockMassMultiplier);
		}
	}
}

void SolarSystem::threadedUpdateParticles(vector<SSParticle> & particles, int start, int end, vector<SSPlanet> & planets) {
    //Iterate over every planet, adding up forces along the way.
    for (int i = start; i < end; i++) {
        auto & p = particles.at(i);
        p.force = ofVec3f(0);
        
        for (SSPlanet & aPlanet : planets) {
            //F = G * M * m / r^2
            float f = gravityConstant * aPlanet.getMass() * p.mass / pow(aPlanet.pos.distance(p.pos), 2);
            ofVec3f force((aPlanet.pos - p.pos).normalize() * f);
            p.force += force;
        }
    }
    
    //Perform foward Euler integration
    for (int i = start; i < end; i++) {
        auto & p = particles.at(i);
        ofVec3f acc = p.force / p.mass;
        p.vel = p.vel + acc * timeStep;
        p.pos = p.pos + ofVec4f(p.vel * timeStep);
    }
}

void SolarSystem::threadedUpdatePlanets(vector<SSPlanet> &planets, int start, int end) {
    //Imagine there is a star at origin
    for (int i = start; i < end; i++) {
        auto & aPlanet = planets.at(i);
        aPlanet.force = ofVec3f(0);
        float fMag = gravityConstant * solarMass * aPlanet.getMass() / pow(ofVec3f(aPlanet.pos).length(), 2);
        aPlanet.force = -ofVec3f(aPlanet.pos).normalize() * fMag;
        ofVec3f acc = aPlanet.force / aPlanet.getMass();
        aPlanet.vel = aPlanet.vel + acc * timeStep;
        aPlanet.pos = aPlanet.pos + ofVec4f(aPlanet.vel * timeStep);
    }
}

void SolarSystem::stop() {
	dataFetcher.stopThread();
	ofThread::getCurrentThread()->sleep(10);
}

SolarSystem::~SolarSystem() {
	dataFetcher.stopThread();
}
