#pragma once

#include "ofMain.h"

enum ofxLayerIsolation {
    DO_NOT_ISOLATE_LAYERS,
    ISOLATE_LAYERS
};

class ofxLayerMask {

public:
    vector<int> setup(int numLayers=0, ofxLayerIsolation isolation=DO_NOT_ISOLATE_LAYERS);
    vector<int> setup(ofVec2f size, int numLayers=0, ofxLayerIsolation isolation=DO_NOT_ISOLATE_LAYERS);
    vector<int> setup(int _width, int _height, int numLayers=0, ofxLayerIsolation isolation=DO_NOT_ISOLATE_LAYERS);
    int setupSingleLayer();
    int setupSingleLayer(int _width, int _height);
    void toggleOverlay();
    void setOverlayThumbSize(int _thumbSize);
    void draw(int x=0, int y=0, int _width=-1, int _height=-1);
    void drawLayer(int layerId, bool masked);
    void drawLayer(int layerId, int x=0, int y=0, int _width=-1, int _height=-1, bool masked=true);
    void drawLayers(int fromId, int throughId, int x=0, int y=0, int _width=-1, int _height=-1, bool masked=true);
    void drawMask(int maskId, int x=0, int y=0, int _width=-1, int _height=-1);
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
    void beginLayerIsolation();
    void endLayerIsolation();
    int validWidth(int _width);
    int validHeight(int _height);

    int width, height;
    ofShader maskShader;
    vector<ofFbo> masks, layers;
    ofFbo newFbo, newMaskFbo;
    ofxLayerIsolation layerIsolation;

    int numSamples;
    bool overlayOn;
    int thumbSize;
    int overlayPadding, doublePadding, triplePadding, quadruplePadding;
    int overlayMargin;
    int overlayWidth, overlayHeight;
    int thumbWidth, thumbHeight, halfThumbHeight, doubleThumbWidth, tripleThumbWidth;
    int textAreaWidth;
    int x, y;
};
