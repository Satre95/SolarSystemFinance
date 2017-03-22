#pragma once
#include "ofMain.h"
#include "SSParticle.hpp"
#include "SSPlanet.hpp"

class SolarSystem {
public:
	SolarSystem(int numParticles = 10000, int numPlanets = 20);
	int numParticles, numPlanets;
private:
	vector<SSParticle> particles;
	vector<SSPlanet> planets;
};

