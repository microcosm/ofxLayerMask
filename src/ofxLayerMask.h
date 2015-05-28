#pragma once

#include "ofMain.h"

class ofxLayerMask {

public:
    void setup(int _width, int _height);
    void draw();

    int newLayerMask();
    void beginMask();
    void endMask();
    void beginLayer();
    void endLayer();

private:
    void initFbo(ofFbo &fbo);
    string shader(string name);

    int width, height;
    ofShader maskShader;
    vector<ofFbo> masks, layers;
    ofFbo newFbo;
};
