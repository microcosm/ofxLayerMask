#include "ofApp.h"

void ofApp::setup(){
    width = 500; height = 500;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    
    ofSetWindowShape(width, height);
    masker.setup(width, height);
    
    //Init a new layer mask
    layer1 = masker.newLayerMask();
    
    ofSetCircleResolution(60);
}

void ofApp::update(){
    
}

void ofApp::draw(){
    //Draw a background
    ofBackground(ofColor::black);
    ofTranslate(6, 6);
    ofSetColor(ofColor::red, 90);
    for(int i = 0; i < width; i += 50) {
        for(int j = 0; j < height; j += 50) {
            ofRect(i, j, 35, 35);
        }
    }
    ofSetColor(ofColor::wheat);
    for(int i = 50; i < height; i+=50) {
        ofDrawBitmapString("This is the background", 30, i);
    }

    //Draw the layer
    masker.beginLayer(layer1);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::blue, 160);
    for(int i = 0; i < width; i += 25) {
        for(int j = 0; j < height; j += 25) {
            ofRect(i, j, 16, 16);
        }
    }
    ofSetColor(ofColor::wheat);
    for(int i = 50; i < height; i+=50) {
        ofDrawBitmapString("This is the masked layer", halfWidth, i);
    }
    masker.endLayer(layer1);

    //Draw the mask
    masker.beginMask(layer1);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    diameter = ofMap(sin(ofGetFrameNum() * 0.03), -1, 1, 30, 280);
    ofCircle(halfWidth, halfHeight, diameter);
    masker.endMask(layer1);

    //Draw the combined result
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