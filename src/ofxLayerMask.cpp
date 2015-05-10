#include "ofxLayerMask.h"

void ofxLayerMask::setup(int _width, int _height) {
    width = _width;
    height = _height;
    maskShader.load(shader("alphaMask"));

    setupFbo(background);
    setupFbo(mask);
    setupFbo(foreground);
    setupFbo(composite);
}

void ofxLayerMask::draw() {
    ofSetColor(255, 255, 255, 255);

    composite.begin();
    ofClear(0, 0, 0, 0);

    maskShader.begin();
    maskShader.setUniformTexture("maskTex", mask.getTextureReference(), 1);
    foreground.draw(0, 0);
    maskShader.end();
    composite.end();

    background.draw(0, 0);
    composite.draw(0, 0);
}

void ofxLayerMask::beginBackground() {
    background.begin();
}

void ofxLayerMask::endBackground() {
    background.end();
}

void ofxLayerMask::beginMask() {
    mask.begin();
}

void ofxLayerMask::endMask() {
    mask.end();
}

void ofxLayerMask::beginForeground() {
    foreground.begin();
}

void ofxLayerMask::endForeground() {
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