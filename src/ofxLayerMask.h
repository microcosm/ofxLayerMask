#pragma once

#include "ofMain.h"

class ofxLayerMask {

public:
    void setup(int _width, int _height);
    void drawLayer();

    void beginMask();
    void endMask();

    void beginLayer();
    void endLayer();

private:
    void setupFbo(ofFbo &fbo);
    string shader(string name);

    int width, height;
    ofShader maskShader;
    ofFbo mask, foreground;
};
