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

    //Select which layer to draw
    layerToDraw = layer1;

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

    //Draw layer #1
    masker.beginLayer(layer1);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::blue, 160);
    drawGrid(width, height, 25, 16);
    ofSetColor(ofColor::wheat);
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
    if(layerToDraw == layer1 || layerToDraw == layer2) {
        masker.drawLayer(layerToDraw);
    } else {
        masker.draw();
    }

    //Instructions
    ofDrawBitmapString("Press 1 for layer 1\n\nPress 2 for layer 2\n\nAny other key for all layers", 30, 50);
}

void ofApp::drawGrid(int _width, int _height, float increment, float blockSize){
    for(int i = 0; i < _width; i+=increment) {
        for(int j = 0; j < _height; j+=increment) {
            ofRect(i, j, blockSize, blockSize);
        }
    }
}

float ofApp::animate(float from, float to){
    return ofMap(sin(ofGetFrameNum() * 0.02), -1, 1, from, to);
}

void ofApp::keyPressed(int key){
    if(key == 49) {
        layerToDraw = layer1;
    } else if(key == 50) {
        layerToDraw = layer2;
    } else {
        layerToDraw = -1;
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