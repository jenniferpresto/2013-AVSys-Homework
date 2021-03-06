#pragma once

#include "ofMain.h"
#include "ofxMacamPs3Eye.h"

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
    
    vector<ofImage> images;
    vector<ofImage> images2;
    vector<ofImage> images3;
    vector<ofImage> images4;
    
    ofImage displayImage;
    ofImage displayImage2;
    ofImage displayImage3;
    ofImage displayImage4;
    
    
    ofImage displayCutOut;
    ofImage displayCutOut2;
    ofImage displayCutOut3;
    ofImage displayCutOut4;
    
    //threshold of comparison
    float threshold;
    
    // fake (delightful!) background for testing
    ofImage tulips;
};
