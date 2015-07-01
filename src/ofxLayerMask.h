#pragma once

#include "ofMain.h"

class ofxLayerMask {

public:
    vector<int> setup(int numLayers=0);
    vector<int> setup(int _width, int _height, int numLayers=0);
    int setupSingleLayer();
    int setupSingleLayer(int _width, int _height);
    void toggleOverlay();
    void setOverlayThumbSize(int _thumbSize);
    void draw();
    void draw(int x, int y);
    void draw(int x, int y, int _width, int _height);
    void drawLayer(int layerId);
    void drawLayer(int layerId, bool masked);
    void drawLayer(int layerId, int x, int y);
    void drawLayer(int layerId, int x, int y, int _width, int _height, bool masked=true);
    void drawLayers(int fromId, int throughId);
    void drawLayers(int fromId, int throughId, int x, int y);
    void drawLayers(int fromId, int throughId, int x, int y, int _width, int _height, bool masked=true);
    void drawMask(int maskId, int x, int y, int _width, int _height);
    void drawOverlay();

    int newLayer();
    vector<int> newLayers(int numLayers);
    void beginMask();
    void beginMask(int _id);
    void endMask();
    void endMask(int _id);
    void begin();
    void beginLayer();
    void beginLayer(int _id);
    void end();
    void endLayer();
    void endLayer(int _id);

    float getWidth();
    float getHeight();
    int numLayers();

private:
    void initOverlay();
    void initFbo(ofFbo &fbo);
    void initMaskFbo(ofFbo &fbo);
    string shader(string name);
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(0, 0, 0, 150));

    int width, height;
    ofShader maskShader;
    vector<ofFbo> masks, layers;
    ofFbo newFbo, newMaskFbo;

    bool overlayOn;
    int thumbSize;
    int overlayPadding, doublePadding, triplePadding, quadruplePadding;
    int overlayMargin;
    int overlayWidth, overlayHeight;
    int thumbWidth, thumbHeight, halfThumbHeight, doubleThumbWidth, tripleThumbWidth;
    int textAreaWidth;
    int x, y;
};
