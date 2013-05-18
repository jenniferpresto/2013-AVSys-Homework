#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"

#define CAMWIDTH 320
#define CAMHEIGHT 240

class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		ofxMacamPs3Eye ps3eye;
	
		int 				camWidth;
		int 				camHeight;
    
    // color images
    ofImage background;
    unsigned char * backgroundPixels;
    ofVec3f bgPixels[CAMHEIGHT*CAMWIDTH]; // this will store each bg pixel as a vector for comparison
    ofVec3f rgbPixels[CAMHEIGHT*CAMWIDTH]; // this will store each live pixel as a vector for comparison
    ofImage grayImageForAlpha;
    
    vector<ofImage> images;     // first looping image
    vector<ofImage> images2;    // second looping image
    vector<ofImage> images3;    // third looping image
    vector<ofImage> images4;    // fourth looping image
    
    ofImage displayImage;
    ofImage displayImage2;
    ofImage displayImage3;
    ofImage displayImage4;
    
    
    ofImage displayCutOut;  // first image plus alpha
    ofImage displayCutOut2; // second image plus alpha
    ofImage displayCutOut3; // third image plus alpha
    ofImage displayCutOut4; // fourth image plus alpha
    
    //threshold of comparison
    float threshold;
    
    // fake (delightful!) background for testing
    ofImage tulips;
};
