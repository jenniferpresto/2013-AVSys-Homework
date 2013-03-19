#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    ofSetColor(255);
    soundStream.setup(this, 0, 1, 44100, 256, 4);
    ofSetVerticalSync(true);
    
    volumeSmooth = 0;
    pitchSmooth = 0;
    hertz = 0;
    
    rectangleTopY = ofGetHeight()/2-50;
    rectangleRightX = ofGetWidth()/2+50;
    rectangleBottomY = ofGetHeight()/2+50;
    rectangleLeftX = ofGetWidth()/2-50;
    
    face.loadImage("face_only.png");
    face.setAnchorPercent(0.5, 0.5);
    
}

//--------------------------------------------------------------
void testApp::update(){
    float hue = ofMap(pitchSmooth, 1000, 2000, 180, 360, true);
    float sat = 360;
    float bri = ofMap(volumeSmooth, .002, .01, 0, 100, true);
    
    bgColor.setHsb(hue, sat, bri);
    ofBackground(bgColor);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //100 px by 100 px square is basic shape;
    ofBeginShape();
    //top of square
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX, 256, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY, 128, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX+25, 448, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY, 256, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX+50, 512, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY, 64, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX-25, 576, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY, 256, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX, 768, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY, 128, true));
    //right side of square
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX, 640, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY+25, 320, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX, 832, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY+50, 384, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX, 640, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY-25, 448, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX, 768, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY, 640, true));
    //bottom of square
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX-25, 576, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY, 512, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleRightX-50, 512, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY, 704, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX+25, 448, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY, 512, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX, 256, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY, 640, true));
    //left side of square
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX, 384, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY-25, 448, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX, 192, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleBottomY-50, 384, true));
    ofVertex(ofMap(volumeSmooth, 0.002, 0.2, rectangleLeftX, 384, true), ofMap(volumeSmooth, 0.002, 0.2, rectangleTopY+25, 320, true));
    ofEndShape();
    
    if (volumeSmooth > 0.2) {
        face.draw(ofGetWidth()/2, ofGetHeight()/2 + 30);
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

void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
    float squareTotal = 0;
    float rms = 0;
    float zeroCrossings = 0; //note: changing from int to float improved accuracy significantly
    
    // calculate RMS value (i.e., volume)--------------
    for (int i = 0; i < bufferSize; i++){
        //cout << input[i] << endl;
        // first calcuation RMS of values
        squareTotal += input[i]*input[i];
        // or squareTotal += powf(intput[i], 2);
    }
    
    // calculate final RMS value
    rms = sqrt(squareTotal/bufferSize);
    
    // assign value to volume (with smoothing)
    volumeSmooth = 0.9f * volumeSmooth + 0.1f * rms;

    
    // calculate zero crossings (i.e., pitch)-----------
    for (int i = 0; i < bufferSize-1; i++){
        if((input[i] > 0 && input[i+1] < 0) || (input[i] < 0 && input[i+1] > 0)){
            zeroCrossings++;
        }
    }

    // calculate hertz, smooth pitch
    // does not include low-pass filtering from example
    hertz = (float)(zeroCrossings * 0.5) * (float)(44100.0/bufferSize); // casting here makes little difference
    pitchSmooth = 0.95f * pitchSmooth + 0.05 * hertz;

    
    // print values to console
    cout << "RMS Value: " << rms << "  Zero Crossings: " << zeroCrossings << endl;
    cout << "Hertz: " << hertz << endl;
    cout << "Volume (smooth): " << volumeSmooth << endl;
    
    
}
