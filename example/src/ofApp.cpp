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
    
}

void ofApp::draw(){
    //Draw a background as normal
    ofBackground(ofColor::black);
    ofTranslate(12, 12);
    ofSetColor(ofColor::red);
    for(int i = 0; i < width; i += 50) {
        for(int j = 0; j < height; j += 50) {
            ofRect(i, j, 25, 25);
        }
    }

    //Draw the layer you'd like to mask
    masker.beginLayer();
    ofTranslate(12, 12);
    ofSetColor(ofColor::blue);
    for(int i = 0; i < width; i += 25) {
        for(int j = 0; j < height; j += 25) {
            ofRect(i, j, 12, 12);
        }
    }
    masker.endLayer();

    //Draw the mask to apply to the layer
    masker.beginMask();
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    diameter = ofMap(sin(ofGetFrameNum() * 0.01), -1, 1, 50, 170);
    ofCircle(halfWidth, halfHeight, diameter);
    masker.endMask();

    //Draw the result
    masker.drawLayer();
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