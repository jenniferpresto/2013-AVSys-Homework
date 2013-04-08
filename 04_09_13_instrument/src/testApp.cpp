/*
 Jennifer Presto
 AVSys Homework
 04-09-13
 
 Assignment:
 Create an instrument based on
 data from the computer's camera.
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255, 255, 255);
    
    drums.loadSound("drums.mp3");
    cowbell.loadSound("cowbell.mp3");
    
    drums.setLoop(true);
    cowbell.setLoop(true);

    drums.play();
    cowbell.play();

}

//--------------------------------------------------------------
void testApp::update(){
    if(mouseY>ofGetHeight()*0.5){
        cowbell.setVolume(1);
    }
    else {
        cowbell.setVolume(0);
    }

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

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