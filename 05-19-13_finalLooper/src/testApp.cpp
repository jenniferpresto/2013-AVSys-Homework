#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    grabber.initGrabber(camWidth, camHeight);
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
    //allocate images (only 2 arguments when image is ofxOpenCv image)
    displayImage.allocate(camWidth, camHeight);
    background.allocate(camWidth, camHeight);
    bwBackground.allocate(camWidth, camHeight);
    // cutOutImage.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    
    tulips.loadImage("holland_tulips.jpg");
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    // when press spacebar, capture the background, save B&W version of it
    if(ofGetKeyPressed(' ')){
        if(grabber.isFrameNew()){
            background.setFromPixels(grabber.getPixelsRef());
            bwBackground = background;
        }
    }
    
    
    // when press a, record from camera (each frame adds an image to vector)
    if(ofGetKeyPressed('a')){
        
        if(grabber.isFrameNew()){
            ofxCvColorImage temp;
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
        
        // convert looping frames to b&w
        bwDisplayImage = displayImage;
        bwDisplayImage.draw(320, 240);
        
        // create a threshold image of difference of looping image from background
        displayImageDiff.absDiff(bwDisplayImage, bwBackground);
        displayImageDiff.threshold(20);
        displayImageDiff.erode();
        displayImageDiff.dilate();
        displayImageDiff.erode();
        displayImageDiff.dilate();
        displayImageDiff.draw(320, 480);
    }
    
    background.draw(640,0);
    bwBackground.draw(640, 240);
    tulips.draw(640, 480, 320, 240);
    //    cutOutImage.draw(640, 480);
    ofDrawBitmapString("Press spacebar to set background", 10, 10);
    
    // create the cut-out image
    if(images.size()>0){
        ofPixels & diffPixels = displayImageDiff.getPixelsRef(); // b & w threshold image
        ofPixels & origPixels = displayImage.getPixelsRef(); // color live image
        //        ofPixels & newPixels = cutOutImage.getPixelsRef(); // will be new cut-out image
        
        for(int i=0; i<camWidth; i++){
            for (int j=0; j<camHeight; j++){
                ofColor pixel = diffPixels.getColor(i, j);
                if(pixel.r == 255){
                    ofColor cutOut = origPixels.getColor(i, j);
                    ofSetColor(cutOut);
                    ofRect(i+640, j+480, 1, 1);
                    // newPixels.setColor(i, j, cutOut);
                }
                // else {
                // ofColor cutOut = (0, 0, 0, 0);
                // newPixels.setColor(i, j, cutOut);
                // }
            }
        }
        // cutOutImage.update();
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