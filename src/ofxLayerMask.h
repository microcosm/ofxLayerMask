#pragma once

#include "ofMain.h"

class ofxLayerMask {

public:
    void setup(int _width, int _height);
    void draw();

    void beginBackground();
    void endBackground();

    void beginMask();
    void endMask();

    void beginForeground();
    void endForeground();

private:
    void setupFbo(ofFbo &fbo);
    string shader(string name);

    int width, height;
    ofShader maskShader;
    ofFbo background, mask, foreground, composite;
};
