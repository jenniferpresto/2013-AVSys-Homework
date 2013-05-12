#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"

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
    
    // ofxOpenCv stuff
    // color images
    vector<ofxCvColorImage> images;
    ofxCvColorImage displayImage;
    ofxCvColorImage background;
    ofxCvGrayscaleImage bwBackground;
    
    // black-and-white images
    ofxCvGrayscaleImage bwDisplayImage;
    ofxCvGrayscaleImage displayImageDiff;
    
    // cut-out image
//    ofImage cutOutImage;
    
    ofImage tulips;
    
    
};
