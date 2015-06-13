#pragma once

#include "ofMain.h"

class ofxLayerMask {

public:
    void setup(int _width, int _height);
    void draw();
    void draw(int x, int y);
    void drawLayer(int layerId);
    void drawLayer(int layerId, int x, int y);

    int newLayer();
    void beginMask();
    void beginMask(int _id);
    void endMask();
    void endMask(int _id);
    void beginLayer();
    void beginLayer(int _id);
    void endLayer();
    void endLayer(int _id);

private:
    void initFbo(ofFbo &fbo);
    string shader(string name);

    int width, height;
    ofShader maskShader;
    vector<ofFbo> masks, layers;
    ofFbo newFbo;
};
