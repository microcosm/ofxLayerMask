#pragma once

#include "ofMain.h"
#include "ofxLayerMask.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void drawGrid(int _width, int _height, float increment, float blockSize);
    void drawText(string text, int x, int marginY, int _height);
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
    ofColor red, green, blue;
    int width, height, halfWidth, halfHeight;
    int layer1, layer2;
};
