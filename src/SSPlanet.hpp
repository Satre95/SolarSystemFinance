#pragma once
#include "ofMain.h"

struct SSPlanet {
	SSPlanet() {
		pos = ofVec4f(0, 0, 0, 1.0f);
		vel = ofVec3f(0);
		color = ofFloatColor(1.0f, 0, 0, 1.0f);
	}

	SSPlanet(ofVec3f pos, ofVec3f vel, float mass = 1000.0f) {
		this->pos = ofVec4f(pos.x, pos.y, pos.z, 1.0f);
		this->vel = vel;
		color = ofFloatColor(1.0f, 0, 0, 1.0f);
		this->mass = mass;
	}

	ofVec4f pos;
	ofVec3f vel;
	ofVec3f force;
	ofFloatColor color;
	float mass = 1.0f;
};

