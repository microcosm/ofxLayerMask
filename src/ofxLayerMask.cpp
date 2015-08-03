#include "ofxLayerMask.h"

vector<int> ofxLayerMask::setup(int numLayers, ofxLayerIsolation isolation) {
    return setup(ofGetWidth(), ofGetHeight(), numLayers, isolation);
}

vector<int> ofxLayerMask::setup(int _width, int _height, int numLayers, ofxLayerIsolation isolation) {
    width = _width, height = _height;
    maskShader.load(shader("alphaMask"));
    setOverlayThumbSize(86);
    layerIsolation = isolation;
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

void ofxLayerMask::draw(int x, int y, int _width, int _height) {
    ofSetColor(ofColor::white);
    for(int i = 0; i < layers.size(); i++) {
        drawLayer(i, x, y, validWidth(_width), validHeight(_height));
    }
}

void ofxLayerMask::drawLayer(int layerId, bool masked) {
    drawLayer(layerId, 0, 0, width, height, masked);
}

void ofxLayerMask::drawLayer(int layerId, int x, int y, int _width, int _height, bool masked) {
    if(masked) {
        maskShader.begin();
        maskShader.setUniformTexture("maskTex", masks.at(layerId).getTextureReference(), 1);
        layers.at(layerId).draw(x, y, validWidth(_width), validHeight(_height));
        maskShader.end();
    } else {
        layers.at(layerId).draw(x, y, validWidth(_width), validHeight(_height));
    }
}

void ofxLayerMask::drawLayers(int fromId, int throughId, int x, int y, int _width, int _height, bool masked) {
    for(int i = fromId; i <= throughId; i++) {
        drawLayer(i, x, y, validWidth(_width), validHeight(_height), masked);
    }
}

void ofxLayerMask::drawMask(int maskId, int x, int y, int _width, int _height) {
    masks.at(maskId).draw(x, y, validWidth(_width), validHeight(_height));
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
    layers.push_back(newFbo);
    initFbo(layers.back());
    masks.push_back(newMaskFbo);
    initMaskFbo(masks.back());
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

void ofxLayerMask::begin() {
    beginLayer();
}

void ofxLayerMask::beginLayer() {
    beginLayerIsolation();
    layers.back().begin();
}

void ofxLayerMask::beginLayer(int _id) {
    beginLayerIsolation();
    layers.at(_id).begin();
}

void ofxLayerMask::end() {
    endLayer();
}

void ofxLayerMask::endLayer() {
    layers.back().end();
    endLayerIsolation();
}

void ofxLayerMask::endLayer(int _id) {
    layers.at(_id).end();
    endLayerIsolation();
}

float ofxLayerMask::getWidth() {
    return width;
}

float ofxLayerMask::getHeight() {
    return height;
}

int ofxLayerMask::numLayers() {
    return layers.size();
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
    ofBackground(ofColor(ofColor::black, 0));
    fbo.end();
}

void ofxLayerMask::initMaskFbo(ofFbo &fbo) {
    fbo.allocate(width, height, GL_RGB);
    fbo.begin();
    ofBackground(ofColor::white);
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

void ofxLayerMask::beginLayerIsolation() {
    if(layerIsolation == ISOLATE_LAYERS) {
        ofPushMatrix();
        ofPushStyle();
    }
}

void ofxLayerMask::endLayerIsolation() {
    if(layerIsolation == ISOLATE_LAYERS) {
        ofPopStyle();
        ofPopMatrix();
    }
}

int ofxLayerMask::validWidth(int _width) {
    return _width >= 0 ? _width : width;
}

int ofxLayerMask::validHeight(int _height) {
    return _height >= 0 ? _height : height;
}