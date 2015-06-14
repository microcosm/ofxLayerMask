#include "ofxLayerMask.h"

void ofxLayerMask::setup(int _width, int _height) {
    width = _width;
    height = _height;
    maskShader.load(shader("alphaMask"));
    overlayOn = false;
    overlayPadding = 20;
    doublePadding = overlayPadding * 2;
    overlayMargin = 20;
    overlayWidth = 100;
    overlayHeight = 100;
    thumbWidth = 100;
    thumbHeight = 100;
}

void ofxLayerMask::toggleOverlay() {
    overlayOn = !overlayOn;
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

void ofxLayerMask::drawLayer(int layerId, int x, int y, int _width, int _height) {
    maskShader.begin();
    maskShader.setUniformTexture("maskTex", masks.at(layerId).getTextureReference(), 1);
    layers.at(layerId).draw(x, y, _width, _height);
    maskShader.end();
}

void ofxLayerMask::drawOverlay() {
    if(overlayOn) {
        overlayHeight = 100 * (layers.size() + 1) + (overlayPadding * layers.size());

        //Draw overlay panel
        x = ofGetWidth() - overlayWidth - doublePadding - overlayMargin;
        y = ofGetHeight() - overlayHeight - doublePadding - overlayMargin;
        drawDebugBox(x, y, overlayWidth + doublePadding, overlayHeight + doublePadding);

        //Draw layers
        x += overlayPadding;
        y += overlayPadding;
        for(int i = 0; i < layers.size(); i++) {
            drawDebugBox(x - 1, y - 1, thumbWidth + 2, thumbHeight + 2, ofColor(255, 255, 255, 150));
            drawLayer(i, x, y, thumbWidth, thumbHeight);
            y += thumbHeight + overlayPadding;
        }

        //Draw composite thumbnail
        drawDebugBox(x - 1, y - 1, thumbWidth + 2, thumbHeight + 2, ofColor(255, 255, 255, 150));
        draw(x, y, thumbWidth, thumbHeight);
    }
}

int ofxLayerMask::newLayer() {
    masks.push_back(newFbo);
    initFbo(masks.back());
    layers.push_back(newFbo);
    initFbo(layers.back());
    return layers.size() - 1;
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