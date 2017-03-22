#include "SolarSystem.hpp"
#include "Utilities.hpp"

SolarSystem::SolarSystem(int numParticles, int numPlanets) {
	this->numParticles = numParticles;
	this->numPlanets = numPlanets;

	//Init the particles
	for (int i = 0; i < numParticles; i++) {
		particles.emplace_back(Utilities::randomPointInSphere(3.0f));
	}

	//Init the planets
	for (int j = 0; j < numPlanets; j++) {
		planets.emplace_back(Utilities::randomPointBetweenSpheres(10.0f, 20.0f));
	}
}

void SolarSystem::initBuffers() {
	//allocated the particles buffer and setup pointer for shader
	particlesBuf.allocate(particles, GL_DYNAMIC_DRAW);
	particlesVbo.setAttributeBuffer(celestialShader.getAttributeLocation("position"),
		particlesBuf, 
		3, 
		sizeof(SSParticle), 
		offsetof(SSParticle, pos));
	particlesVbo.setAttributeBuffer(celestialShader.getAttributeLocation("color"),
		particlesBuf,
		4,
		sizeof(SSParticle),
		offsetof(SSParticle, color));

	//allocated the planets buffer and setup the poointer for the shader.
	planetsBuf.allocate(planets, GL_DYNAMIC_DRAW);
	planetsVbo.setAttributeBuffer(celestialShader.getAttributeLocation("position"),
		planetsBuf,
		3,
		sizeof(SSPlanet),
		offsetof(SSPlanet, pos));
	planetsVbo.setAttributeBuffer(celestialShader.getAttributeLocation("color"),
		planetsBuf,
		4,
		sizeof(SSPlanet),
		offsetof(SSPlanet, color));


}
