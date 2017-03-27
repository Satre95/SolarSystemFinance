#include "ofApp.h"
#include <thread>

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
	stocks = {
		"FB", "JNJ",
        "XOM", "JPM", "WFC", "DIS", "GE", "NUGT", "SNAP"
	};
	ss = new SolarSystem(stocks, 20000);
	camera.setTarget(ofVec3f(0));
	camera.setAutoDistance(true);
	camera.setNearClip(1.0f);
    camera.setFarClip(10000.0f);
    
    paused = true;
    
    gui.setup("Parameters");
    gui.add(ss->gravityConstant.set("Gravity Constant (G)", 0.01f, 0.01f, 1.0f));
    gui.add(ss->timeStep.set("Time Step", 0.4f, 0.01f, 0.8f));
    gui.add(ss->solarMass.set("Star Mass", 100000, 100, 1000000));
    gui.add(fps.set("FPS", 0, 0, 60));
    
}

//--------------------------------------------------------------
void ofApp::update() {
    if(paused) return;
	ss->update();
    fps = ofGetFrameRate();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0);
	camera.begin();
	ss->draw();
    camera.end();
   
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if(key == 'f') {
        ofToggleFullscreen();
    } else if(key == 'p') {
        paused = !paused;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
}

//--------------------------------------------------------------
void ofApp::exit() {
	ss->stop();
	delete ss;
}
