#include "testApp.h"
#include "imageManager.h"
#include "imageGrain.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofFill();
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    pictureManager.grain.redMin = 10;
    pictureManager.grain.redMax = 255;
    pictureManager.grain.blueMin = 10;
    pictureManager.grain.blueMax = 255;
}

//--------------------------------------------------------------
void testApp::update(){
    pictureManager.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    pictureManager.display();
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Red", 20, ofGetHeight()/2);
    ofDrawBitmapString("Blue", 600, ofGetHeight()/2);
    ofDrawBitmapString("More constraint", ofGetWidth()/2-40, 20);
    ofDrawBitmapString("Less constraint", ofGetWidth()/2-36, 440);
//    ofDrawBitmapString(ofToString(ofGetFrameRate(), 2), 20, 20);
    
    cout << "duration: " << pictureManager.durationInMillis << " mouse: " << ofGetMouseX() << " " << ofGetMouseY() << endl;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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