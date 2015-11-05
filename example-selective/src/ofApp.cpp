#include "ofApp.h"

void ofApp::setup(){
    width = 500; height = 500;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;

    ofSetWindowShape(width, height);
    masker.setup(width, height);

    //Switch overlay on
    masker.toggleOverlay();

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

    //Draw layer #1
    masker.beginLayer(layer1);
    ofClear(0, 0, 0, 255);
    ofSetColor(ofColor::blue);
    drawGrid(width, height, 70, 50);
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

    masker.drawOverlay();

    //Instructions
    ofDrawBitmapString("Press 'o' to toggle thumbnail overlays\n\nPress 1 for layer 1, press 2 for layer 2\n\nAny other key for all layers", 10, 20);
}

void ofApp::drawGrid(int _width, int _height, float increment, float blockSize){
    for(int i = 0; i < _width; i+=increment) {
        for(int j = 0; j < _height; j+=increment) {
            ofRect(i, j, blockSize, blockSize);
        }
    }
}

float ofApp::animate(float from, float to){
    return ofMap(sin(ofGetElapsedTimeMicros() * 0.000001), -1, 1, from, to);
}

void ofApp::keyPressed(int key){
    if(key == 49) {
        layerToDraw = layer1;
    } else if(key == 50) {
        layerToDraw = layer2;
    } else if(key == 'o') {
        masker.toggleOverlay();
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