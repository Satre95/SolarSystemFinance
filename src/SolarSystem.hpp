#pragma once
#include "ofMain.h"
#include "SSParticle.hpp"
#include "SSPlanet.hpp"
#include "ofxGui.h"
#include "ofxJSON.h"

class SolarSystem {
public:
	class StockUpdater : public ofThread {
	public:
		const string stockURL = "http://finance.google.com/finance/info?client=ig&q=";
		vector<string> * stocksPtr = nullptr;
		vector<SSPlanet> * planetsPtr = nullptr;
		void threadedFunction();
	};
	//----------------------------------------------
	//MARK: Public Methods
	SolarSystem(vector<string> & stockSymbols, int numParticles = 10000);

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
	void updateStocks();

	//----------------------------------------------
	//MARK: Private Vars

	vector<SSParticle> particles;
	vector<SSPlanet> planets;

	ofBufferObject particlesBuf;
	ofBufferObject planetsBuf;
	ofVbo particlesVbo, planetsVbo;
	ofShader celestialShader;
	vector<string> stocks;
	StockUpdater dataFetcher;

};