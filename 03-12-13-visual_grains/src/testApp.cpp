#include "testApp.h"
#include "imageManager.h"
#include "imageGrain.h"


//--------------------------------------------------------------
void testApp::setup(){
    ofFill();
    ofSetBackgroundAuto(false);
    pictureManager.grain.redMin = 100;
    pictureManager.grain.redMax = 200;
    pictureManager.grain.blueMin = 100;
    pictureManager.grain.blueMax = 200;
}

//--------------------------------------------------------------
void testApp::update(){
    pictureManager.update();

}

//--------------------------------------------------------------
void testApp::draw(){
    pictureManager.display();
    
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