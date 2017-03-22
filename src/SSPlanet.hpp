#pragma once
#include "ofMain.h"

struct SSPlanet {
	SSPlanet() {
		pos = vel = ofVec3f(0);
	}

	SSPlanet(ofVec3f pos) {
		this->pos = pos;
		vel = ofVec3f(0);
	}

	ofVec3f pos;
	ofVec3f vel;
};

