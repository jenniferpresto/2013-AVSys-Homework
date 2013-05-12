#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    grabber.initGrabber(camWidth, camHeight);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
    // allocate images (only 2 parameters when image is ofxOpenCv image,
    // need three when they are ofImages)
    displayImage.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    background.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    
    threshold = 400;
    
    tulips.loadImage("holland_tulips.jpg");
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // when press spacebar, capture the background
    if(ofGetKeyPressed(' ')){
        if(grabber.isFrameNew()){
            background.setFromPixels(grabber.getPixelsRef());
        }
    }
    
    
    // when press a, record from camera (each frame adds an image to vector)
    if(ofGetKeyPressed('a')){
        
        if(grabber.isFrameNew()){
            ofImage temp;
            temp.setUseTexture(false); // none have texture; stores only in RAM
            temp.setFromPixels(grabber.getPixelsRef());
            images.push_back(temp);
        }
    }
    
    grabber.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    grabber.draw(0,0);
    
    if (images.size() > 0){
        int whichImage = ofGetFrameNum() % images.size();
        displayImage.setFromPixels(images[whichImage].getPixelsRef());
        displayImage.draw(320,0);
    }
    
    background.draw(640,0);
    tulips.draw(640, 480, 320, 240);
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
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
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