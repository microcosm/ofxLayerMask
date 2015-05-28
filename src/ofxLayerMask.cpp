#include "ofxLayerMask.h"

void ofxLayerMask::setup(int _width, int _height) {
    width = _width;
    height = _height;
    maskShader.load(shader("alphaMask"));
}

void ofxLayerMask::draw() {
    ofSetColor(ofColor::white);
    for(int i = 0; i < layers.size(); i++) {
        maskShader.begin();
        maskShader.setUniformTexture("maskTex", masks.at(i).getTextureReference(), 1);
        layers.at(i).draw(0, 0);
        maskShader.end();
    }
}

int ofxLayerMask::newLayerMask() {
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