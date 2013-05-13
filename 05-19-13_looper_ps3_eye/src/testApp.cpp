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
    
    // allocate background
    background.allocate(camWidth, camHeight, OF_IMAGE_COLOR);

    
    // images to be used (set 1)
    displayImage.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);

    // images to be used (set 2)
    displayImage2.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut2.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);

    // images to be used (set 3)
    displayImage3.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut3.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);

    // images to be used (set 4)
    displayImage4.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut4.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);

    // temp (and awesome) background
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
    
    // when press b, record a different loop from the camera (each frame adds an image to a different vector)
    if(ofGetKeyPressed('b')){        
        if(ps3eye.isFrameNew()){
            ofImage temp;
            temp.setUseTexture(false); // store only in RAM
            temp.setFromPixels(ps3eye.getPixelsRef());
            images2.push_back(temp);
        }
    }
    
    // when press c, record a different loop from the camera (each frame adds an image to a different vector)
    if(ofGetKeyPressed('c')){        
        if(ps3eye.isFrameNew()){
            ofImage temp;
            temp.setUseTexture(false); // store only in RAM
            temp.setFromPixels(ps3eye.getPixelsRef());
            images3.push_back(temp);
        }
    }

    // when press d, record a different loop from the camera (each frame adds an image to a different vector)
    if(ofGetKeyPressed('d')){        
        if(ps3eye.isFrameNew()){
            ofImage temp;
            temp.setUseTexture(false); // store only in RAM
            temp.setFromPixels(ps3eye.getPixelsRef());
            images4.push_back(temp);
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
        displayImage.draw(0,240);
    }
    
    if(images2.size() > 0){
        int whichImage = ofGetFrameNum() % images2.size();
        displayImage2.setFromPixels(images2[whichImage].getPixelsRef());
        displayImage2.draw(320, 240);
    }

    if(images3.size() > 0){
        int whichImage = ofGetFrameNum() % images3.size();
        displayImage3.setFromPixels(images3[whichImage].getPixelsRef());
        displayImage3.draw(0, 480);
    }

    if(images4.size() > 0){
        int whichImage = ofGetFrameNum() % images4.size();
        displayImage4.setFromPixels(images4[whichImage].getPixelsRef());
        displayImage4.draw(320, 480);
    }

    background.draw(640,0, 320, 240);
    tulips.draw(640, 240, 320, 240);
    
    // create the cut-out image
    if(images.size()>0){
        ofPixels & origPixels = background.getPixelsRef(); // background image
        ofPixels & diffPixels = displayImage.getPixelsRef(); // color live image
        ofPixels & newPixels = displayCutOut.getPixelsRef(); // color cut-out moving image
        
        
        // loop through the live and background images pixel by pixel
        for(int i=0; i<camWidth; i++){
            for (int j=0; j<camHeight; j++){
                ofColor pixelbg = origPixels.getColor(i, j);
                ofColor pixellive = diffPixels.getColor(i, j);
                
                // convert RGB values of each one into a vector
                ofVec3f p2(pixellive.r, pixellive.g, pixellive.b);
                ofVec3f p1(pixelbg.r, pixelbg.g, pixelbg.b);
                
                // measure the distance between the two vectors
                // if the distance if large enough, draw a 1-pixel rectangle
                // the same color as that point on the live screen
                
                if(p1.squareDistance(p2)>threshold){
                    ofColor cutOut(pixellive.r, pixellive.g, pixellive.b, 255);
                    newPixels.setColor(i, j, cutOut);
                } else {
                    ofColor cutOut(0,0,0,0);
                    newPixels.setColor(i, j, cutOut);
                }
                
            }
        }
        displayCutOut.update();
        displayCutOut.draw(640, 240, 320, 240);
    }
    
    
    // create the cut-out image2
    if(images2.size()>0){
        ofPixels & origPixels = background.getPixelsRef(); // background image
        ofPixels & diffPixels = displayImage2.getPixelsRef(); // color live image
        ofPixels & newPixels = displayCutOut2.getPixelsRef(); // color cut-out moving image
        
        
        // loop through the live and background images pixel by pixel
        for(int i=0; i<camWidth; i++){
            for (int j=0; j<camHeight; j++){
                ofColor pixelbg = origPixels.getColor(i, j);
                ofColor pixellive = diffPixels.getColor(i, j);
                
                // convert RGB values of each one into a vector
                ofVec3f p2(pixellive.r, pixellive.g, pixellive.b);
                ofVec3f p1(pixelbg.r, pixelbg.g, pixelbg.b);
                
                // measure the distance between the two vectors
                // if the distance if large enough, draw a 1-pixel rectangle
                // the same color as that point on the live screen
                
                if(p1.squareDistance(p2)>threshold){
                    ofColor cutOut(pixellive.r, pixellive.g, pixellive.b, 255);
                    newPixels.setColor(i, j, cutOut);
                } else {
                    ofColor cutOut(0,0,0,0);
                    newPixels.setColor(i, j, cutOut);
                }
                
            }
        }
        displayCutOut2.update();
        displayCutOut2.draw(640, 240, 320, 240);
    }

    // create the cut-out image3
    if(images3.size()>0){
        ofPixels & origPixels = background.getPixelsRef(); // background image
        ofPixels & diffPixels = displayImage3.getPixelsRef(); // color live image
        ofPixels & newPixels = displayCutOut3.getPixelsRef(); // color cut-out moving image
        
        
        // loop through the live and background images pixel by pixel
        for(int i=0; i<camWidth; i++){
            for (int j=0; j<camHeight; j++){
                ofColor pixelbg = origPixels.getColor(i, j);
                ofColor pixellive = diffPixels.getColor(i, j);
                
                // convert RGB values of each one into a vector
                ofVec3f p2(pixellive.r, pixellive.g, pixellive.b);
                ofVec3f p1(pixelbg.r, pixelbg.g, pixelbg.b);
                
                // measure the distance between the two vectors
                // if the distance if large enough, draw a 1-pixel rectangle
                // the same color as that point on the live screen
                
                if(p1.squareDistance(p2)>threshold){
                    ofColor cutOut(pixellive.r, pixellive.g, pixellive.b, 255);
                    newPixels.setColor(i, j, cutOut);
                } else {
                    ofColor cutOut(0,0,0,0);
                    newPixels.setColor(i, j, cutOut);
                }
                
            }
        }
        displayCutOut3.update();
        displayCutOut3.draw(640, 240, 320, 240);
    }
    
    // create the cut-out image4
    if(images4.size()>0){
        ofPixels & origPixels = background.getPixelsRef(); // background image
        ofPixels & diffPixels = displayImage4.getPixelsRef(); // color live image
        ofPixels & newPixels = displayCutOut4.getPixelsRef(); // color cut-out moving image
        
        
        // loop through the live and background images pixel by pixel
        for(int i=0; i<camWidth; i++){
            for (int j=0; j<camHeight; j++){
                ofColor pixelbg = origPixels.getColor(i, j);
                ofColor pixellive = diffPixels.getColor(i, j);
                
                // convert RGB values of each one into a vector
                ofVec3f p2(pixellive.r, pixellive.g, pixellive.b);
                ofVec3f p1(pixelbg.r, pixelbg.g, pixelbg.b);
                
                // measure the distance between the two vectors
                // if the distance if large enough, draw a 1-pixel rectangle
                // the same color as that point on the live screen
                
                if(p1.squareDistance(p2)>threshold){
                    ofColor cutOut(pixellive.r, pixellive.g, pixellive.b, 255);
                    newPixels.setColor(i, j, cutOut);
                } else {
                    ofColor cutOut(0,0,0,0);
                    newPixels.setColor(i, j, cutOut);
                }
                
            }
        }
        displayCutOut4.update();
        displayCutOut4.draw(640, 240, 320, 240);
    }
    
    
    ofDrawBitmapString("Press spacebar to set background", 10, 10);
	ofDrawBitmapString("Ps3Eye FPS: "+ ofToString(ps3eye.getRealFrameRate()), 10, 20);
}






//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key == ' '){
        images.clear();
        images2.clear();
        images3.clear();
        images4.clear();
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
