#include "ofApp.h"

void ofApp::setup(){
    width = 500; height = 500;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    
    ofSetWindowShape(width, height);
    masker.setup(width, height);
    
    //Init a new layer / mask combo
    masker.newLayer();
    
    ofSetCircleResolution(60);
}

void ofApp::update(){
    
}

void ofApp::draw(){
    //Draw a background
    ofBackground(ofColor::black);
    ofTranslate(6, 6);
    ofSetColor(ofColor::red, 90);
    drawGrid(width, height, 50, 35);
    ofSetColor(ofColor::wheat);
    drawText("This is the background", 30, 50, height);

    //Draw the layer
    masker.beginLayer();
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::blue, 160);
    drawGrid(width, height, 25, 16);
    ofSetColor(ofColor::wheat);
    drawText("This is layer one", halfWidth, 50, height);
    masker.endLayer();

    //Draw the mask
    masker.beginMask();
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    ofCircle(halfWidth, halfHeight, animate(30, 280));
    masker.endMask();

    //Draw the combined result (and overlay when enabled - see keyPressed below)
    masker.draw();
    masker.drawOverlay();
}

void ofApp::drawGrid(int _width, int _height, float increment, float blockSize){
    for(int i = 0; i < _width; i+=increment) {
        for(int j = 0; j < _height; j+=increment) {
            ofRect(i, j, blockSize, blockSize);
        }
    }
}

void ofApp::drawText(string text, int x, int marginY, int _height){
    for(int i = marginY; i < _height; i+=marginY) {
        ofDrawBitmapString(text, x, i);
    }
}

float ofApp::animate(float from, float to){
    return ofMap(sin(ofGetFrameNum() * 0.02), -1, 1, from, to);
}

void ofApp::keyPressed(int key){
    if(key == 'p') {
        masker.toggleOverlay();
    }
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