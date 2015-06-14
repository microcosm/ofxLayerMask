#include "ofxLayerMask.h"

void ofxLayerMask::setup(int _width, int _height) {
    width = _width;
    height = _height;
    maskShader.load(shader("alphaMask"));
    overlayOn = false;
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
    int padding = 20;
    int doublePadding = padding * 2;
    int margin = 20;
    int width = 100;
    int height = 100;
    int x = ofGetWidth() - width - doublePadding - margin;
    int y = ofGetHeight() - height - doublePadding - margin;
    drawDebugBox(x, y, width + doublePadding, height + doublePadding);
    drawDebugBox(x + padding - 1, y + padding - 1, width + 2, height + 2, ofColor(255, 255, 255, 150));
    draw(x + padding, y + padding, width, height);
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