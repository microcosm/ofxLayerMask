#include "ofApp.h"

void ofApp::setup(){
    width = 500; height = 500;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    
    ofSetWindowShape(width, height);
    masker.setup(width, height);
    
    ofSetCircleResolution(60);
}

void ofApp::update(){
    masker.beginBackground();
    ofTranslate(12, 12);
    ofSetColor(ofColor::red);
    for(int i = 0; i < width; i += 50) {
        for(int j = 0; j < height; j += 50) {
            ofRect(i, j, 25, 25);
        }
    }
    masker.endBackground();
    
    masker.beginMask();
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    diameter = ofMap(sin(ofGetFrameNum() * 0.01), -1, 1, 50, 170);
    ofCircle(halfWidth, halfHeight, diameter);
    masker.endMask();
    
    masker.beginForeground();
    ofTranslate(12, 12);
    ofSetColor(ofColor::blue);
    for(int i = 0; i < width; i += 25) {
        for(int j = 0; j < height; j += 25) {
            ofRect(i, j, 12, 12);
        }
    }
    masker.endForeground();
}

void ofApp::draw(){
    masker.draw();
}

void ofApp::keyPressed(int key){
    
}

void ofApp::keyReleased(int key){
    
}

void ofApp::mouseMoved(int x, int y ){
    
}

void ofApp::mouseDragged(int x, int y, int button){
    
}

void ofApp::mousePressed(int x, int y, int button){
    
}

void ofApp::mouseReleased(int x, int y, int button){
    
}

void ofApp::windowResized(int w, int h){
    
}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){
    
}