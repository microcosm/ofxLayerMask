#include "ofApp.h"

void ofApp::setup(){
    width = 500; height = 500;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;

    ofSetWindowShape(width, height);
    masker.setup(width, height);

    //Init new layers
    layer1 = masker.newLayer();
    layer2 = masker.newLayer();

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

    //Draw layer #1
    masker.beginLayer(layer1);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::blue, 160);
    drawGrid(width, height, 25, 16);
    ofSetColor(ofColor::wheat);
    drawText("This is layer one", halfWidth, 50, height);
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
    drawGrid(width, height, 35, 25);
    ofSetColor(ofColor::wheat);
    drawText("And this is layer two", halfWidth, 50, height);
    masker.endLayer(layer2);

    //Draw mask #2
    masker.beginMask(layer2);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::white);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(halfWidth, animate(height - 100, 100), 360, 120);
    ofSetRectMode(OF_RECTMODE_CORNER);
    masker.endMask(layer2);

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
    return ofMap(sin(ofGetElapsedTimeMicros() * 0.000001), -1, 1, from, to);
}

void ofApp::keyPressed(int key){
    if(key == 'o') {
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