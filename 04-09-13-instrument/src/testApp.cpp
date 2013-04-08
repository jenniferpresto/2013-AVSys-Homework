/*
 Jennifer Presto
 AVSys Homework
 04-09-13
 
 Assignment:
 Create an instrument based on
 data from the computer's camera.
 
 This version:
 The more movement in the screen, the
 more instruments are introduced.
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(255, 255, 255);
    
    drums.loadSound("drums.mp3");
    conga.loadSound("conga.mp3");
    bass.loadSound("bass.mp3");
    guitar.loadSound("guitar.mp3");
    
    drums.setLoop(true);
    conga.setLoop(true);
    bass.setLoop(true);
    guitar.setLoop(true);

    drums.play();
    conga.play();
    bass.play();
    guitar.play();

}

//--------------------------------------------------------------
void testApp::update(){
//    if(mouseY>ofGetHeight()*0.5){
//    }
//    else {
//    }

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