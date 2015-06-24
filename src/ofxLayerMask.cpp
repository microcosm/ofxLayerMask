#include "ofxLayerMask.h"

vector<int> ofxLayerMask::setup(int numLayers) {
    return setup(ofGetWidth(), ofGetHeight(), numLayers);
}

vector<int> ofxLayerMask::setup(int _width, int _height, int numLayers) {
    width = _width, height = _height;
    maskShader.load(shader("alphaMask"));
    setOverlayThumbSize(86);
    return newLayers(numLayers);
}

int ofxLayerMask::setupSingleLayer() {
    return setup(1).at(0);
}

int ofxLayerMask::setupSingleLayer(int _width, int _height) {
    return setup(_width, _height, 1).at(0);
}

void ofxLayerMask::toggleOverlay() {
    overlayOn = !overlayOn;
}

void ofxLayerMask::setOverlayThumbSize(int _thumbSize) {
    thumbSize = _thumbSize;
    initOverlay();
}

void ofxLayerMask::draw() {
    draw(0, 0);
}

void ofxLayerMask::draw(int x, int y) {
    draw(x, y, width, height);
}

void ofxLayerMask::draw(int x, int y, int _width, int _height) {
    ofSetColor(ofColor::white);
    for(int i = 0; i < layers.size(); i++) {
        drawLayer(i, x, y, _width, _height);
    }
}

void ofxLayerMask::drawLayer(int layerId) {
    drawLayer(layerId, 0, 0);
}

void ofxLayerMask::drawLayer(int layerId, int x, int y) {
    drawLayer(layerId, x, y, width, height);
}

void ofxLayerMask::drawLayer(int layerId, int x, int y, int _width, int _height, bool masked) {
    if(masked) {
        maskShader.begin();
        maskShader.setUniformTexture("maskTex", masks.at(layerId).getTextureReference(), 1);
        layers.at(layerId).draw(x, y, _width, _height);
        maskShader.end();
    } else {
        layers.at(layerId).draw(x, y, _width, _height);
    }
}

void ofxLayerMask::drawMask(int maskId, int x, int y, int _width, int _height) {
    masks.at(maskId).draw(x, y, _width, _height);
}

void ofxLayerMask::drawOverlay() {
    if(overlayOn) {
        overlayHeight = thumbSize * (layers.size() + 1) + (overlayPadding * layers.size());

        //Draw overlay panel
        x = ofGetWidth() - tripleThumbWidth - textAreaWidth - quadruplePadding - overlayMargin;
        y = ofGetHeight() - overlayHeight - doublePadding - overlayMargin;
        drawDebugBox(x, y, tripleThumbWidth + textAreaWidth + quadruplePadding, overlayHeight + doublePadding);
        
        //Draw layers
        x += overlayPadding;
        y += overlayPadding;
        for(int i = 0; i < layers.size(); i++) {
            ofDrawBitmapString("Layer " + ofToString(i + 1), x, y + halfThumbHeight + 4);
            drawDebugBox(x - 1 + textAreaWidth, y - 1, thumbWidth + 2, thumbHeight + 2, ofColor(255, 255, 255, 150));
            drawLayer(i, x + textAreaWidth, y, thumbWidth, thumbHeight, false);
            drawDebugBox(x - 1 + textAreaWidth + thumbWidth + overlayPadding, y - 1, thumbWidth + 2, thumbHeight + 2, ofColor(255, 255, 255, 150));
            drawMask(i, x + textAreaWidth + thumbWidth + overlayPadding, y, thumbWidth, thumbHeight);
            drawDebugBox(x - 1 + textAreaWidth + doubleThumbWidth + doublePadding, y - 1, thumbWidth + 2, thumbHeight + 2, ofColor(255, 255, 255, 150));
            drawLayer(i, x + textAreaWidth + doubleThumbWidth + doublePadding, y, thumbWidth, thumbHeight);
            y += thumbHeight + overlayPadding;
        }

        //Draw composite thumbnail
        ofDrawBitmapString("Composite", x, y + halfThumbHeight + 4);
        drawDebugBox(x - 1 + textAreaWidth + doubleThumbWidth + doublePadding, y - 1, thumbWidth + 2, thumbHeight + 2, ofColor(255, 255, 255, 150));
        draw(x + textAreaWidth + doubleThumbWidth + doublePadding, y, thumbWidth, thumbHeight);
    }
}

int ofxLayerMask::newLayer() {
    masks.push_back(newFbo);
    initFbo(masks.back());
    layers.push_back(newFbo);
    initFbo(layers.back());
    return layers.size() - 1;
}

vector<int> ofxLayerMask::newLayers(int numLayers) {
    vector<int> layerIds;
    for(int i = 0; i < numLayers; i++) {
        layerIds.push_back(newLayer());
    }
    return layerIds;
}

void ofxLayerMask::beginMask() {
    masks.back().begin();
}

void ofxLayerMask::beginMask(int _id) {
    masks.at(_id).begin();
}

void ofxLayerMask::endMask() {
    masks.back().end();
}

void ofxLayerMask::endMask(int _id) {
    masks.at(_id).end();
}

void ofxLayerMask::beginLayer() {
    layers.back().begin();
}

void ofxLayerMask::beginLayer(int _id) {
    layers.at(_id).begin();
}

void ofxLayerMask::endLayer() {
    layers.back().end();
}

void ofxLayerMask::endLayer(int _id) {
    layers.at(_id).end();
}

float ofxLayerMask::getWidth() {
    return width;
}

float ofxLayerMask::getHeight() {
    return height;
}

void ofxLayerMask::initOverlay() {
    overlayOn = false;
    overlayPadding = 20;
    doublePadding = overlayPadding * 2;
    triplePadding = overlayPadding * 3;
    quadruplePadding = overlayPadding * 4;
    overlayMargin = 20;
    overlayWidth = thumbSize;
    textAreaWidth = 80;
    overlayHeight = thumbSize;
    thumbWidth = thumbSize;
    doubleThumbWidth = thumbWidth * 2;
    tripleThumbWidth = thumbWidth * 3;
    thumbHeight = thumbSize;
    halfThumbHeight = thumbHeight * 0.5;
}

void ofxLayerMask::initFbo(ofFbo &fbo) {
    fbo.allocate(width, height, GL_RGBA);
    fbo.begin();
    ofClear(0, 0, 0, 255);
    fbo.end();
}

string ofxLayerMask::shader(string name) {
    string shaderPath = "../../../../../addons/ofxLayerMask/src/shader/" + name;
#ifdef TARGET_OPENGLES
    return shaderPath + "_ES2";
#else
    if(ofIsGLProgrammableRenderer()){
        return shaderPath + "_GL3";
    }else{
        return shaderPath + "_GL2";
    }
#endif
}

void ofxLayerMask::drawDebugBox(int x, int y, int width, int height, ofColor color) {
    ofSetLineWidth(1);
    ofSetColor(color);
    ofFill();
    ofRect(x, y, width, height);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofRect(x, y, width, height);
    ofFill();
}