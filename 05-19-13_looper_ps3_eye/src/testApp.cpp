#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
	camWidth = 320;
	camHeight = 240;
	
    // ps3eye-specific settings
	ps3eye.listDevices(); // goes to console
	
	ps3eye.setDesiredFrameRate(60);
	ps3eye.initGrabber(camWidth,camHeight);
	
	ps3eye.setAutoGainAndShutter(false); // otherwise we can't set gain or shutter
	ps3eye.setGain(0.2);  // if use 640x480 image, make 0.4
	ps3eye.setShutter(1.0);
	ps3eye.setGamma(0.4);
	ps3eye.setBrightness(0.4); // if use 640x480 image, make 0.5
	ps3eye.setContrast(0.7);
    //	ps3eye.setHue(0.0); // this made things really yellow
	
	ps3eye.setFlicker(0);
    
    // images to be used
    displayImage.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    background.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    tulips.loadImage("holland_tulips.jpg");
    
    // threshold for background subtractions
    threshold = 400;
}


//--------------------------------------------------------------
void testApp::update(){
	
    // when press spacebar, capture the background
    if(ofGetKeyPressed(' ')){
        if(ps3eye.isFrameNew()){
            background.setFromPixels(ps3eye.getPixelsRef());
        }
    }
    
    
    // when press a, record from camera (each frame adds an image to vector)
    if(ofGetKeyPressed('a')){
        
        if(ps3eye.isFrameNew()){
            ofImage temp;
            temp.setUseTexture(false); // none have texture; stores only in RAM
            temp.setFromPixels(ps3eye.getPixelsRef());
            images.push_back(temp);
        }
    }
    
	ps3eye.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ps3eye.draw(0,0);
    
    if (images.size() > 0){
        int whichImage = ofGetFrameNum() % images.size();
        displayImage.setFromPixels(images[whichImage].getPixelsRef());
        displayImage.draw(320,0);
    }
    
    background.draw(640,0);
    tulips.draw(640, 240, 320, 240);
    ofDrawBitmapString("Press spacebar to set background", 10, 10);
    
    // create the cut-out image
    if(images.size()>0){
        ofPixels & origPixels = displayImage.getPixelsRef(); // color live image
        ofPixels & diffPixels = background.getPixelsRef(); // background image
        
        
        // loop through the live and background images pixel by pixel
        for(int i=0; i<camWidth; i++){
            for (int j=0; j<camHeight; j++){
                ofColor pixellive = origPixels.getColor(i, j);
                ofColor pixelbg = diffPixels.getColor(i, j);
                
                // convert RGB values of each one into a vector
                ofVec3f p2(pixellive.r, pixellive.g, pixellive.b);
                ofVec3f p1(pixelbg.r, pixelbg.g, pixelbg.b);
                
                // measure the distance between the two vectors
                // if the distance if large enough, draw a 1-pixel rectangle
                // the same color as that point on the live screen
                if(p1.squareDistance(p2) > threshold){
                    ofColor cutOut = origPixels.getColor(i, j);
                    ofSetColor(cutOut);
                    ofRect(i+640, j+480, 1, 1);
                }
            }
        }
        // set the color back to white
        ofSetColor(255);
    }

	
	ofDrawBitmapString("Ps3Eye FPS: "+ ofToString(ps3eye.getRealFrameRate()), 20,15);
}



//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key == ' '){
        images.clear();
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    
}
