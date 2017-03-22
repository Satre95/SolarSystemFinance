#pragma once
#include "ofMain.h"
#include "SSParticle.hpp"
#include "SSPlanet.hpp"

class SolarSystem {
public:
	//----------------------------------------------
	//MARK: Public Methods
	SolarSystem(int numParticles = 10000, int numPlanets = 20);

	//----------------------------------------------
	//MARK: Public Vars
	int numParticles, numPlanets;

private:
	//----------------------------------------------
	//MARK: Private Methods
	void initBuffers();

	//----------------------------------------------
	//MARK: Private Vars

	vector<SSParticle> particles;
	vector<SSPlanet> planets;

	ofBufferObject particlesBuf;
	ofBufferObject planetsBuf;
	ofVbo particlesVbo, planetsVbo;
	ofShader celestialShader;
};