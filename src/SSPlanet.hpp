#pragma once
#include "ofMain.h"

struct SSPlanet {
	SSPlanet() {
		pos = vel = ofVec3f(0);
		color = ofFloatColor(1.0f);
	}

	SSPlanet(ofVec3f pos) {
		this->pos = pos;
		vel = ofVec3f(0);
		color = ofFloatColor(1.0f);
	}

	ofVec3f pos;
	ofVec3f vel;
	ofFloatColor color;
};

