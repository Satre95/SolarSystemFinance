#pragma once
#include "ofMain.h"

struct SSParticle
{
	SSParticle() {
		pos = vel = force = ofVec3f(0);
		color = ofFloatColor(1.0f);
	}

	SSParticle(ofVec3f pos) {
		this->pos = pos;
		vel = force = ofVec3f(0);
		color = ofFloatColor(1.0f);
	}
	ofVec3f pos;
	ofVec3f vel;
	ofVec3f force;
	ofFloatColor color;
};
