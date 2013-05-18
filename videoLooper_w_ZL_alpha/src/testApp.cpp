#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    grabber.initGrabber(320,240);
    
    grayImageForAlpha.allocate(320, 240, OF_IMAGE_GRAYSCALE);
    thisFramePlusAlpha.allocate(320, 240, OF_IMAGE_COLOR_ALPHA);
    
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    
    if (ofGetKeyPressed('a')){
        
        
        if (grabber.isFrameNew()){
            
            
            unsigned char * grayPixels = grayImageForAlpha.getPixels();
            unsigned char * colorAlphaPixels = thisFramePlusAlpha.getPixels();
            unsigned char * colorPixels = grabber.getPixels();
            
            
            for (int i = 0; i < 320; i++){
                for (int j = 0; j < 240; j++){
                    //grayPixels[j * 320 + i] = ofRandom(0,255);
                    
                    grayPixels[j * 320 + i] =  colorPixels[ (j * 320 + i) * 3] < 127 ? 255 : 0;
                }
            }
            
            
            for (int i = 0; i < 320; i++){
                for (int j = 0; j < 240; j++){
                    colorAlphaPixels[ (j * 320 + i) * 4] = colorPixels[ (j * 320 + i) * 3];
                    colorAlphaPixels[ (j * 320 + i) * 4 + 1] = colorPixels[ (j * 320 + i) * 3+1];
                    colorAlphaPixels[ (j * 320 + i) * 4 + 2] = colorPixels[ (j * 320 + i) * 3+2];
                    colorAlphaPixels[ (j * 320 + i) * 4 + 3] = grayPixels[j * 320 + i];
                }
            }
            
            thisFramePlusAlpha.update();
            
            
            
            ofImage temp;
            temp.setUseTexture(false);
            temp.setFromPixels(thisFramePlusAlpha.getPixelsRef());
            images.push_back(temp);
            
        }
        
        
    }
    
    
    grabber.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    
    grabber.draw(0,0);
    
    ofEnableAlphaBlending();
    
    if (images.size() > 0){
        int whichImage = ofGetFrameNum() % images.size();
        displayImage.setFromPixels(images[whichImage].getPixelsRef());
        displayImage.draw(320,0);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    if (key == ' '){
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