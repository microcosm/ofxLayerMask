#pragma once

#include "ofMain.h"

class ofxLayerMask {

public:
    void setup(int _width, int _height);
    void toggleOverlay();
    void draw();
    void draw(int x, int y);
    void drawLayer(int layerId);
    void drawLayer(int layerId, int x, int y);
    void drawOverlay();

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
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(0, 0, 0, 150));

    int width, height;
    ofShader maskShader;
    vector<ofFbo> masks, layers;
    ofFbo newFbo;
    bool overlayOn;
};
