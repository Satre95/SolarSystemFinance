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