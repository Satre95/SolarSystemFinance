#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ss = new SolarSystem(5000, 25);
	camera.setTarget(ofVec3f(0));
	//camera.setAutoDistance(true);
	camera.setNearClip(1.0f);
}

//--------------------------------------------------------------
void ofApp::update() {
	ss->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	camera.begin();
	ss->draw();
	camera.end();

	stringstream ss;
	ss << "Framerate: " << ofGetFrameRate();
	ofDrawBitmapString(ss.str(), ofPoint(10, 10));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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