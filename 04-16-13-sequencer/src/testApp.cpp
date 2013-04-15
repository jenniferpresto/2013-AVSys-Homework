#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSoundStreamSetup(2,0,this, 44100, 512, 4);
    ofSetCircleResolution(100);
    ofSetVerticalSync(TRUE);
    ofSetFrameRate(30);
    ofEnableAlphaBlending( );
    ofEnableSmoothing();
    
    playerBallX = 20;
    playerBallY = 20;
    playerBallXSpeed = 2;
    playerBallYSpeed = 3;
    playerBallRadius = 20;

    currentSize = 2;
}

//--------------------------------------------------------------
void testApp::update(){
    if (playerBallX > ofGetWidth() - playerBallRadius){
        playerBallX = ofGetWidth() - playerBallRadius;
        playerBallXSpeed *= -1;
    }
    if (playerBallX < playerBallRadius){
        playerBallX = playerBallRadius;
        playerBallXSpeed *= -1;
    }
    if (playerBallY > ofGetHeight()-playerBallRadius){
        playerBallY = ofGetHeight()-playerBallRadius;
        playerBallYSpeed *= -1;
    }
    if (playerBallY < playerBallRadius){
        playerBallY = playerBallRadius;
        playerBallYSpeed *= -1;
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    for(int i=0; i<spots.size(); i++){
        spots[i].display();
    }
    ofSetColor(195, 197, 53);
    ofCircle(playerBallX, playerBallY, 20);

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
    // every time mouse is pressed,
    // add new circle and corresponding note
    spots.push_back(soundCircle(mouseX, mouseY, currentSize));
    notes.push_back(sinOscillator());

    // set up latest note separately
    notes[notes.size()-1].setup();
    notes[notes.size()-1].setVolume(1.0);
    notes[notes.size()-1].setFrequency(ofRandom(200, 500));

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

//--------------------------------------------------------------
void testApp::audioRequested(float * output, int bufferSize, int nChannels){
    int notesPlayed = 0; // count how many notes have been played for the averaging
    
    for (int i = 0; i < bufferSize; i++){ //clear the buffers
		output[i*nChannels    ] = 0;
		output[i*nChannels + 1] = 0;
	}
    
    for(int i = 0; i<spots.size(); i++){
        if (ofDist(mouseX, mouseY, spots[i].xPos, spots[i].yPos) < spots[i].radius) {
            notes[i].addToSoundBuffer(output, bufferSize);
            notesPlayed++;
        }
    }

    notesPlayed = MAX(notesPlayed, 4);
    for (int i = 0; i < bufferSize; i++){ // avgerage all the inputs so the sound never goes over 1.0
		output[i*nChannels    ] /= notesPlayed;
		output[i*nChannels + 1] /= notesPlayed;
	}

}