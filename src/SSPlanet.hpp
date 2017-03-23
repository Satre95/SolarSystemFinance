#pragma once
#include "ofMain.h"
#include <mutex>

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

	SSPlanet(const SSPlanet & other) {
		pos = other.pos;
		vel = other.vel;
		force = other.force;
		color = other.color;
		mass = other.mass;
	}

	float getMass() {
		std::lock_guard<std::mutex> lock(massMutex);
		return mass;
	}

	void setMass(float m) {
		std::lock_guard<std::mutex> lock(massMutex);
		mass = m;
	}

	std::mutex massMutex;

	ofVec4f pos;
	ofVec3f vel;
	ofVec3f force;
	ofFloatColor color;
	float mass = 1.0f;
};

