#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef TARGET_OPENGLES
    ofGLESWindowSettings settings;
    settings.glesVersion = 2;
    auto window = ofCreateWindow(settings);
    auto app = make_shared<ofApp>();
    ofRunApp(window, app);
    return ofRunMainLoop();
#else
    ofSetupOpenGL(1024,768,OF_WINDOW);
    ofRunApp(new ofApp());
#endif
}
