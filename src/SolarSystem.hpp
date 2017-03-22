#pragma once
#include "ofMain.h"
#include "SSParticle.hpp"
#include "SSPlanet.hpp"
#include "ofxGui.h"

class SolarSystem {
public:
	//----------------------------------------------
	//MARK: Public Methods
	SolarSystem(int numParticles = 10000, int numPlanets = 20);

	void draw();
	void update();

	//----------------------------------------------
	//MARK: Public Vars
	int numParticles, numPlanets;
	ofParameter<float> gravityConstant = 0.01f;
	ofParameter<float> timeStep = 0.1f;
	ofParameter<float> solarMass = 10000.0f;

private:
	//----------------------------------------------
	//MARK: Private Methods
	void initBuffers();
	void drawParticles();
	void drawPlanets();

	void updateParticles();
	void updatePlanets();

	//----------------------------------------------
	//MARK: Private Vars

	vector<SSParticle> particles;
	vector<SSPlanet> planets;

	ofBufferObject particlesBuf;
	ofBufferObject planetsBuf;
	ofVbo particlesVbo, planetsVbo;
	ofShader celestialShader;
};