#include "ofApp.h"

void ofApp::setup(){
    width = 500; height = 500;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;

    ofSetWindowShape(width, height);
    masker.setup(width, height);

    //Init a new layer mask
    layer1 = masker.newLayerMask();
    layer2 = masker.newLayerMask();

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

    //Draw layer #1
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
        ofDrawBitmapString("This is layer one", halfWidth, i);
    }
    masker.endLayer(layer1);

    //Draw mask #1
    masker.beginMask(layer1);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    ofCircle(halfWidth, halfHeight, animate(30, 280));
    masker.endMask(layer1);

    //Draw layer #2
    masker.beginLayer(layer2);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::green, 100);
    for(int i = 0; i < width; i += 35) {
        for(int j = 0; j < height; j += 35) {
            ofRect(i, j, 25, 25);
        }
    }
    ofSetColor(ofColor::wheat);
    for(int i = 50; i < height; i+=50) {
        ofDrawBitmapString("And this is layer two", halfWidth, i);
    }
    masker.endLayer(layer2);

    //Draw mask #2
    masker.beginMask(layer2);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(halfWidth, animate(height - 100, 100), 360, 120);
    ofSetRectMode(OF_RECTMODE_CORNER);
    masker.endMask(layer2);

    //Draw the combined result
    masker.draw();
}

float ofApp::animate(float from, float to){
    return ofMap(sin(ofGetFrameNum() * 0.02), -1, 1, from, to);
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