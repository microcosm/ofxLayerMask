#include "ofxLayerMask.h"

void ofxLayerMask::setup(int _width, int _height) {
    width = _width;
    height = _height;
    maskShader.load(shader("alphaMask"));

    setupFbo(mask);
    setupFbo(foreground);
}

void ofxLayerMask::drawLayer() {
    ofSetColor(ofColor::white);
    maskShader.begin();
    maskShader.setUniformTexture("maskTex", mask.getTextureReference(), 1);
    foreground.draw(0, 0);
    maskShader.end();
}

void ofxLayerMask::beginMask() {
    mask.begin();
}

void ofxLayerMask::endMask() {
    mask.end();
}

void ofxLayerMask::beginLayer() {
    foreground.begin();
}

void ofxLayerMask::endLayer() {
    foreground.end();
}

void ofxLayerMask::setupFbo(ofFbo &fbo) {
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