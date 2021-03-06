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
    
    // general variables
        ofTrueTypeFont helvetica;
        ofImage bgPic;
    
    // music variables
		
        ofSoundPlayer drums;
        ofSoundPlayer conga;
        ofSoundPlayer bass;
        ofSoundPlayer guitar;
    
        bool bDrums;
        bool bConga;
        bool bBass;
        bool bGuitar;
    
        float volumeMultiplier;
    
    // computer vision variables
    
        int threshold;
        float prevMovement;
        float movement;
        float buildMovement;
        int width, height;
    
        float averageRed;
        float averageBright;
    
        ofVideoGrabber cam;
        ofxCvColorImage camColorCv;
        ofxCvGrayscaleImage camGrayCv;
        ofxCvGrayscaleImage camPrevGrayCv;
        ofxCvGrayscaleImage camDiff;
};
