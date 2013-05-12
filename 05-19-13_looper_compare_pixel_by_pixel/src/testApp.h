#pragma once

#include "ofMain.h"
//#include "ofxOpenCv.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int camWidth = 320;
    int camHeight = 240;
    
    // non ofxOpenCv stuff
    ofVideoGrabber grabber;
    
    // color images
    vector<ofImage> images;
    ofImage displayImage;
    ofImage background;
    
    // threshold of comparison
    float threshold;
    
    // fake (delightful!) background for now
    ofImage tulips;
    
    
};
