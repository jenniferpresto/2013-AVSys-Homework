/*
 Jennifer Presto
 AVSys Homework
 04-09-13
 
 Assignment:
 Load an image and create a drawing
 based on it.
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    mtn_flora.allocate(500, 335, OF_IMAGE_COLOR);
    sc_flora.allocate(500, 335, OF_IMAGE_COLOR);
    mtn_flora.loadImage("mtn_flora.png");
    sc_flora.loadImage("sc_flora.png");
    
    ofBackground(0, 0, 0);
    ofEnableAlphaBlending();
    
    pixels = mtn_flora.getPixels();
    
    redChange = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    if (mouseY>ofGetHeight()-ofGetHeight()*0.25){
        redChange = ofMap(mouseX, 0, ofGetWidth(), -127, 127, true);
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    // draw SC picture just normally
    ofSetColor(255, 255, 255);
    sc_flora.draw(ofGetWidth()*0.5 - sc_flora.width*0.5, 30);
    
    ofLine(0, ofGetHeight()-ofGetHeight()*0.25, ofGetWidth(), ofGetHeight()-ofGetHeight()*0.25);
    
    // draw mtn picture on top with alpha based on mouse's Y position
    for (int i=0; i<mtn_flora.width; i++){
        for (int j=0; j<mtn_flora.height; j++){
            red = pixels[(j*mtn_flora.width + i)*3];
            green = pixels[(j*mtn_flora.width + i)*3 + 1];
            blue = pixels[(j*mtn_flora.width + i)*3 + 2];
            alpha = ofMap(mouseY, 30, ofGetHeight()-ofGetHeight()*0.25, 0, 255, true);
            ofSetColor(red+redChange, green-redChange, blue, alpha);
            ofRect(i + ofGetWidth()*0.5 - mtn_flora.width*0.5, j + 30, 1, 1);
            
        }
    }
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