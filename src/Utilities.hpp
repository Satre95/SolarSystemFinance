#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "ofMain.h"

class Utilities {
public:

	static void purgeCharsFromString(std::string & line) {
		line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
		line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
	}

	template <typename T>
	static void removeEmptySlots(std::vector<T> & src, std::vector<T> & dest) {
		assert(&src != &dest);

		//Remove empty slots
		for (auto aData : src) {
			if (aData.compare("") != 0)
				dest.push_back(aData);
		}
	}

	static bool isNumber(std::string line)
	{
		char* p;
		strtol(line.c_str(), &p, 10);
		return *p == 0;
	}

	static ofVec3f randomPointInSphere(float radius = 1.0f) {
		float u = ofRandom(0, 1.0f);
		float v = ofRandom(0, 1.0f);

		float theta = 2 * PI * u;
		float phi = acos(2 * v - 1);
		float r = ofRandom(radius);

		float x = r * sin(phi) * cos(theta);
		float y = r * sin(phi) * sin(theta);
		float z = r * cos(phi);

		return ofVec3f(x, y, z);
	}

	static ofVec3f randomPointBetweenSpheres(float innerRad, float outerRad) {
		float u = ofRandom(0, 1.0f);
		float v = ofRandom(0, 1.0f);

		float theta = 2 * PI * u;
		float phi = acos(2 * v - 1);
		float r = ofRandom(innerRad, outerRad);

		float x = r * sin(phi) * cos(theta);
		float y = r * sin(phi) * sin(theta);
		float z = r * cos(phi);

		return ofVec3f(x, y, z);
	}

	static ofVec3f randomUnitVector() {
		float u = ofRandom(0, 1.0f);
		float v = ofRandom(0, 1.0f);

		float theta = 2 * PI * u;
		float phi = acos(2 * v - 1);

		float x = sin(phi) * cos(theta);
		float y = sin(phi) * sin(theta);
		float z = cos(phi);

		return ofVec3f(x, y, z);
	}

	static ofVec3f randomPointOnSphere(float radius = 1.0f) {
		float u = ofRandom(0, 1.0f);
		float v = ofRandom(0, 1.0f);

		float theta = 2 * PI * u;
		float phi = acos(2 * v - 1);

		float x = radius * sin(phi) * cos(theta);
		float y = radius * sin(phi) * sin(theta);
		float z = radius * cos(phi);

		return ofVec3f(x, y, z);
	}
    
    static int roundUp(int numToRound, int multiple)
    {
        if (multiple == 0)
            return numToRound;
        
        int remainder = numToRound % multiple;
        if (remainder == 0)
            return numToRound;
        
        return numToRound + multiple - remainder;
    }
};
