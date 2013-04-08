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

    drums.setVolume(0);
    conga.setVolume(0);
    bass.setVolume(0);
    guitar.setVolume(0);
    
    drums.play();
    conga.play();
    bass.play();
    guitar.play();
    
    bDrums = false;
    bConga = false;
    bBass = false;
    bGuitar = false;

    
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
        
        prevMovement = movement;
        movement = camDiff.countNonZeroInRegion(0, 0, width, height);
        buildMovement = 0.96 * prevMovement + 0.04 * movement;
    }
    cout << "average red: " << averageRed << "  movement: " << movement << endl;
    cout << "volume multiplier: " << volumeMultiplier << endl;

    volumeMultiplier = ofMap(averageRed, 60, 110, 0.0f, 1.0f, true);
    
    if(buildMovement < 100){
        bDrums = false;
        bConga = false;
        bBass = false;
        bGuitar = false;
        drums.setVolume(0);
        conga.setVolume(0);
        bass.setVolume(0);
        guitar.setVolume(0);
    }
    if(buildMovement >= 100 && buildMovement < 1500){
        bDrums = true;
        bConga = false;
        bBass = false;
        bGuitar = false;
        drums.setVolume(1*volumeMultiplier);
        conga.setVolume(0);
        bass.setVolume(0);
        guitar.setVolume(0);
    }
    if(buildMovement >= 1500 && buildMovement < 5500){
        bDrums = true;
        bConga = true;
        bBass = false;
        bGuitar = false;
        drums.setVolume(1*volumeMultiplier);
        conga.setVolume(1*volumeMultiplier);
        bass.setVolume(0);
        guitar.setVolume(0);
    }
    if(buildMovement >= 5500 && buildMovement < 10000){
        bDrums = true;
        bConga = true;
        bBass = true;
        bGuitar = false;
        drums.setVolume(1*volumeMultiplier);
        conga.setVolume(1*volumeMultiplier);
        bass.setVolume(1*volumeMultiplier);
        guitar.setVolume(0);
    }
    if(buildMovement >= 10000){
        bDrums = true;
        bConga = true;
        bBass = true;
        bGuitar = true;
        drums.setVolume(1*volumeMultiplier);
        conga.setVolume(1*volumeMultiplier);
        bass.setVolume(1*volumeMultiplier);
        guitar.setVolume(1*volumeMultiplier);
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255, 255, 255);
    bgPic.draw(0, 0);
    
    // draw the difference picture showing movement
    camDiff.draw(40,40);
    
    // draw the picture using only red values
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
    
    // output two variables created
    ofSetColor(255, 255, 255);
    helvetica.drawString("Funkiness level: " + ofToString((int)buildMovement), 400, 80);
    if(bDrums){
        helvetica.drawString("drums", 400, 140);
    }
    if(bConga){
        helvetica.drawString("conga", 400, 180);
    }
    if(bBass){
        helvetica.drawString("bass", 400, 220);
    }
    if(bGuitar){
        helvetica.drawString("guitar", 400, 260);
    }
    helvetica.drawString("The volume is " + ofToString((int)(ofMap(volumeMultiplier, 0.0, 1.0, 1, 11, true))) + ".", 400, 360);
    helvetica.drawString("(This goes to 11).", 400, 400);

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