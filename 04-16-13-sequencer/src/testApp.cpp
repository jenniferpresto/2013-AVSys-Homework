/*
 Jennifer Presto
 AVSys Homework
 04-16-13
 
 Assignment:
 Create a digital sequencer.
 
 Oscillator code adapted from in-class examples.
 Draw circles of varying sizes; ball plays the
 corresponding notes when it hits them.
 */


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
    playerBallXSpeed = 5;
    playerBallYSpeed = 7;
    playerBallRadius = 20;
    
    currentSize = 2;
    
    ofNoFill();
    
    backgroundPic.loadImage("sequencer_background.jpg");
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
    
    playerBallX += playerBallXSpeed;
    playerBallY+= playerBallYSpeed;
    
    for(int i = 0; i<spots.size(); i++){
        if (ofDist(playerBallX, playerBallY, spots[i].xPos, spots[i].yPos) < spots[i].radius+playerBallRadius) {
            spots[i].active = true;
        } else{
            spots[i].active = false;
        }
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    backgroundPic.draw(0,0);
    ofNoFill();
    for(int i=0; i<spots.size(); i++){
        spots[i].display(spots[i].active);
    }
    ofFill();
    ofSetColor(195, 197, 53);
    ofCircle(playerBallX, playerBallY, 20);
    
    ofSetColor(255);
    ofDrawBitmapString("Press 1 through 5 to change the circles sizes.", 10, 30);
    ofDrawBitmapString("Use the arrow keys to change the speed of the PlayerBall.", 10, 60);
    ofDrawBitmapString("Current Circle Size: " + ofToString(currentSize), 10, 90);
    ofDrawBitmapString("PlayerBall X speed: " + ofToString(playerBallXSpeed), 10, 120);
    ofDrawBitmapString("PlayerBall Y speed: " + ofToString(playerBallYSpeed), 10, 150);
    ofDrawBitmapString("Hit 'x' to reset the screen.", 10, 180);
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch(key){
            
        // arrow keys affect PlayerBall's speed
        case OF_KEY_RIGHT:
            playerBallXSpeed++;
            break;
            
        case OF_KEY_LEFT:
            playerBallXSpeed--;
            break;
            
        case OF_KEY_UP:
            playerBallYSpeed--;
            break;
            
        case OF_KEY_DOWN:
            playerBallYSpeed++;
            break;
            
        // number keys determine size of soundCircles
        case '1':
            currentSize = 1;
            break;
            
        case '2':
            currentSize = 2;
            break;
            
        case '3':
            currentSize = 3;
            break;
            
        case '4':
            currentSize = 4;
            break;
            
        case '5':
            currentSize = 5;
            break;
            
        // "x" key clears the screen
        case 'x':
        case 'X':
            spots.erase(spots.begin(), spots.end());
            notes.erase(notes.begin(), notes.end());
            break;
    }
    
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
    notes[notes.size()-1].setVolume(0.0);
    notes[notes.size()-1].setFrequency((int)(ofRandom(200, 500)));
    
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
        if (ofDist(playerBallX, playerBallY, spots[i].xPos, spots[i].yPos) < spots[i].radius+playerBallRadius) {
            notes[i].setVolume(ofMap(ofDist(playerBallX, playerBallY, spots[i].xPos, spots[i].yPos), 0, spots[i].radius + playerBallRadius, 1.0, 0.0));
            notes[i].addToSoundBuffer(output, bufferSize);
            notesPlayed++;
        }
//        else {
//            notes[i].setVolume(0.0);
//        }
    }
        
    notesPlayed = MAX(notesPlayed, 4);
    for (int i = 0; i < bufferSize; i++){ // avgerage all the inputs so the sound never goes over 1.0
		output[i*nChannels    ] /= notesPlayed;
		output[i*nChannels + 1] /= notesPlayed;
	}
    
}