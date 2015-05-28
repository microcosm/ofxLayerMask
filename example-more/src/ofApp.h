#pragma once

#include "ofMain.h"
#include "ofxLayerMask.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    float animate(float from, float to);
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxLayerMask masker;
    int width, height, halfWidth, halfHeight;
    int layer1, layer2;
};
