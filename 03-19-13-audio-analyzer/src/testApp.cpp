#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0);
    ofSetColor(255);
    soundStream.setup(this, 0, 1, 44100, 256, 4);
    ofSetVerticalSync(true);
    ofSetCircleResolution(100);
    
    volume = 0;
    hertz = 0;
    
    rectangleTopY = ofGetHeight()/2-50;
    rectangleRightX = ofGetWidth()/2+50;
    rectangleBottomY = ofGetHeight()/2+50;
    rectangleLeftX = ofGetWidth()/2-50;
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //rectangle is basic shape;
    ofBeginShape();
    //top of rectangle
    ofVertex(rectangleLeftX, rectangleTopY);
    ofVertex(rectangleLeftX+25, rectangleTopY);
    ofVertex(rectangleLeftX+50, rectangleTopY);
    ofVertex(rectangleRightX-25, rectangleTopY);
    ofVertex(rectangleRightX, rectangleTopY);
    //right side of rectangle
    ofVertex(rectangleRightX, rectangleTopY+25);
    ofVertex(rectangleRightX, rectangleTopY+50);
    ofVertex(rectangleRightX, rectangleBottomY-25);
    ofVertex(rectangleRightX, rectangleBottomY);
    //bottom of rectangle
    ofVertex(rectangleRightX-25, rectangleBottomY);
    ofVertex(rectangleRightX-50, rectangleBottomY);
    ofVertex(rectangleLeftX+25, rectangleBottomY);
    ofVertex(rectangleLeftX, rectangleBottomY);
    //left side of rectangle
    ofVertex(rectangleLeftX, rectangleBottomY-25);
    ofVertex(rectangleLeftX, rectangleBottomY-50);
    ofVertex(rectangleLeftX, rectangleTopY + 25);
    ofEndShape();
    
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
    float squareRoot = 0;
    float zeroCrossings = 0; //note: changing from int to float improved accuracy significantly
    
    // calculate RMS value (i.e., volume)--------------
    for (int i = 0; i < bufferSize; i++){
        //cout << input[i] << endl;
        // first calcuation RMS of values
        squareTotal += (input[i]*input[i]);
        // or squareTotal += powf(intput[i], 2);
    }
    
    // calculate final RMS value
    squareRoot = sqrt(squareTotal/bufferSize);
    
    // calculate zero crossings (i.e., pitch)-----------
    for (int i = 0; i < bufferSize-1; i++){
        if((input[i] > 0 && input[i+1] < 0) || (input[i] < 0 && input[i+1] > 0)){
            zeroCrossings++;
        }
    }

    // calculate hertz
    hertz = (float)(zeroCrossings/2) * (float)(44100/bufferSize); // casting here makes little difference

    
    // print values to console
    cout << "RMS Value: " << squareRoot << "  Zero Crossings: " << zeroCrossings << endl;
    cout << "Hertz: " << hertz << endl;
    
    
    // assign value to volume
    volume = squareRoot;
    
}
