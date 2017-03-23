#pragma once
#include "ofMain.h"

struct SSParticle
{
	SSParticle() {
		pos = ofVec4f(0, 0, 0, 1.0f);
		vel = force = ofVec3f(0);
	}

	SSParticle(ofVec3f pos) {
		this->pos = ofVec4f(pos.x, pos.y, pos.z, 1.0f);
		vel = force = ofVec3f(0);
	}
	ofVec4f pos;
	ofVec3f vel;
	ofVec3f force;
    ofFloatColor color = ofFloatColor(0.6745f, 0.9529f, 0.980f, 0.8f);
	static float mass;
};
