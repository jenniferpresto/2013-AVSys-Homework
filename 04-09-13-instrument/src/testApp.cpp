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
    
    // general setup
    ofBackground(255, 255, 255);
    helvetica.loadFont("helvetica.otf", 24);
    bgPic.allocate(600, 800, OF_IMAGE_COLOR);
    bgPic.loadImage("bgPic.png");
    
    // music setup
    
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
    
    // computer vision setup
    
    threshold = 52;
    movement = 0;
    averageRed = 0;
    
    cam.initGrabber(320, 240);
    cam.setDesiredFrameRate(30);
    
    width = cam.width;
    height = cam.height;
    
    camColorCv.allocate(width, height);
    camGrayCv.allocate(width, height);
    camPrevGrayCv.allocate(width, height);
    camDiff.allocate(width, height);
    

}

//--------------------------------------------------------------
void testApp::update(){

    cam.update();
    if(cam.isFrameNew()){
        camColorCv.setFromPixels(cam.getPixels(), width, height);
        camGrayCv = camColorCv;
        camDiff.absDiff(camGrayCv, camPrevGrayCv);
        camDiff.threshold(threshold);
        camPrevGrayCv = camGrayCv;
        
        movement = camDiff.countNonZeroInRegion(0, 0, width, height);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    bgPic.draw(0, 0);
    
    // draw the difference picture showing movement
    camDiff.draw(40,40);
    
    // draw the picture showing the redness
    unsigned char * pixels = camColorCv.getPixels();
    averageRed = 0;
    for(int i = 0; i < camColorCv.width; i++){
        for(int j = 0; j < camColorCv.height; j++){
            int red = pixels[(j * camColorCv.width + i) * 3];
            ofSetColor(red, red, red);
            ofRect(i+40, j+320, 1, 1);
            averageRed += red;
        }
    }
    averageRed /= camColorCv.width * camColorCv.height;
    cout << "average red: " << averageRed << "  movement: " << movement << endl;
    

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