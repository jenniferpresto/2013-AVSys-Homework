#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    grabber.initGrabber(320,240);
    
    
 
    ofSetVerticalSync(true);
    ofSetFrameRate(30);
}

//--------------------------------------------------------------
void testApp::update(){
    
    
    
    if (ofGetKeyPressed('a')){
        
        
        if (grabber.isFrameNew()){
            
            ofImage temp;
            temp.setUseTexture(false);
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