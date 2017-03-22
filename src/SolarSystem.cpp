#include "SolarSystem.hpp"
#include "Utilities.hpp"

float SSParticle::mass = 10.0f;

SolarSystem::SolarSystem(int numParticles, int numPlanets) {
	this->numParticles = numParticles;
	this->numPlanets = numPlanets;

	//Init the particles
	for (int i = 0; i < numParticles; i++) {
		particles.emplace_back(Utilities::randomPointInSphere(40.0f));
	}

	//Init the planets
	for (int j = 0; j < numPlanets; j++) {
		planets.emplace_back(Utilities::randomPointBetweenSpheres(15.0f, 30.0f), 400.0f);
	}

	//setup shaders
	celestialShader.load("CelestialShaderVert.glsl", "CelestialShaderFrag.glsl");
	//Setup buffers and vbo's
	initBuffers();
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

		for (SSPlanet & aPlanet : planets) {
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
}