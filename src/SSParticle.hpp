#pragma once
#include "ofMain.h"

struct SSParticle
{
	SSParticle() {
		pos = vel = force = ofVec3f(0);
	}

	SSParticle(ofVec3f pos) {
		this->pos = pos;
		vel = force = ofVec3f(0);
	}
	ofVec3f pos;
	ofVec3f vel;
	ofVec3f force;
};
