#include "SolarSystem.hpp"
#include "Utilities.hpp"

float SSParticle::mass = 10.0f;

SolarSystem::SolarSystem(vector<string> & stockSymbols, int numParticles) {
	this->numParticles = numParticles;
	this->numPlanets = (int)stockSymbols.size();
	this->stocks = stockSymbols;

	//Init the particles
	for (int i = 0; i < numParticles; i++) {
		particles.emplace_back(Utilities::randomPointInSphere(200.0f));
	}

	//Init the planets
	for (int j = 0; j < numPlanets; j++) {
		ofVec3f pos = Utilities::randomPointOnSphere(200.0f);
		ofVec3f vel = Utilities::randomPointBetweenSpheres(10, 15);
		planets.emplace_back(pos,
							vel,
							ofRandom(2000, 4000));
	}

	//setup shaders
	celestialShader.load("CelestialShaderVert.glsl", "CelestialShaderFrag.glsl");
	//Setup buffers and vbo's
	initBuffers();

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
}

void SolarSystem::drawParticles() {
	celestialShader.begin();
	float currPointSize;
	glGetFloatv(GL_POINT_SIZE, &currPointSize);
	glPointSize(5.0f);
	particlesVbo.draw(GL_POINTS, 0, numParticles);
	glPointSize(currPointSize);
	celestialShader.end();
}

void SolarSystem::drawPlanets() {
	celestialShader.begin();
	float currPointSize;
	glGetFloatv(GL_POINT_SIZE, &currPointSize);
	glPointSize(5.0f);
	planetsVbo.draw(GL_POINTS, 0, numPlanets);
	glPointSize(currPointSize);
	celestialShader.end();
}

void SolarSystem::update() {
	updatePlanets();
	updateParticles();
}

void SolarSystem::updateParticles() {
	//Iterate over every planet, adding up forces along the way.
	for (SSParticle & p : particles) {
		p.force = ofVec3f(0);

		for (const SSPlanet & aPlanet : planets) {
			//F = G * M * m / r^2
			float f = gravityConstant * aPlanet.mass * p.mass / pow(aPlanet.pos.distance(p.pos), 2);
			ofVec3f force((aPlanet.pos - p.pos) * f);
			p.force += force;
		}
	}

	//Perform foward Euler integration 
	for (SSParticle & p : particles) {
		ofVec3f acc = p.force / p.mass;
		p.vel = p.vel + acc * timeStep;
		p.pos = p.pos + ofVec4f(p.vel * timeStep);
	}

	//Update buffer and vbo
	particlesBuf.updateData(particles);
}

void SolarSystem::updatePlanets() {
	//Imagine there is a star at origin
	for (SSPlanet & aPlanet : planets) {
		aPlanet.force = ofVec3f(0);
		float fMag = gravityConstant * solarMass * aPlanet.mass / pow(ofVec3f(aPlanet.pos).length(), 2);
		aPlanet.force = -ofVec3f(aPlanet.pos) * fMag;
		ofVec3f acc = aPlanet.force / aPlanet.mass;
		aPlanet.vel = aPlanet.vel + acc * timeStep;
		aPlanet.pos = aPlanet.pos + ofVec4f(aPlanet.vel * timeStep);
	}

	//Update the buffer
	planetsBuf.updateData(planets);
}

void SolarSystem::updateStocks() {
	//Do all of the stock fetching in a parallel thread 
	//Avoid clogging up framerate.

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
		}
	}
}