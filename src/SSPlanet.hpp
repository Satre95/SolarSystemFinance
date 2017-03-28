#pragma once
#include "ofMain.h"
#include <mutex>
#include <atomic>

struct SSPlanet {
	SSPlanet() {
		pos = ofVec4f(0, 0, 0, 1.0f);
		vel = ofVec3f(0);
		color = ofFloatColor(1.0f, 0, 0, 1.0f);
	}

	SSPlanet(ofVec3f pos, ofVec3f vel, double mass = 1000) {
		this->pos = ofVec4f(pos.x, pos.y, pos.z, 1.0f);
		this->vel = vel;
		color = ofFloatColor(1.0f, 0, 0, 1.0f);
		this->mass = mass;
	}

	SSPlanet(const SSPlanet & other) {
		pos = other.pos;
		vel = other.vel;
		force = other.force;
		color = other.color;
		mass = other.mass;
	}

	float getMass() {
        while(isWritingMass){} //Simple spin lock to enforce synch
        //Condition var would be better, but situation is simple enough that
        //performance impact is minimal.
		return mass;
	}

    void setMass(double m) {
        isWritingMass = true;
		mass = m;
        isWritingMass = false;
	}

    std::atomic_bool isWritingMass;
	ofVec4f pos;
	ofVec3f vel;
	ofVec3f force;
	ofFloatColor color;
	double mass = 1.0f;
    
};

