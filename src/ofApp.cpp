#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
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
}

//--------------------------------------------------------------
void ofApp::update() {
    if(paused) return;
	ss->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofBackground(0);
	camera.begin();
	ss->draw();
    camera.end();

	stringstream sstream;
	sstream << "Framerate: " << ofGetFrameRate();
	ofDrawBitmapString(sstream.str(), ofPoint(10, 10));
   
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
