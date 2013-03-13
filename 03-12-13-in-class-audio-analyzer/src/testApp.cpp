#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    soundStream.setup(this, 0, 1, 44100, 256, 4);
    
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255);
    ofCircle(200, ofMap(volume, 0, 0.3, ofGetHeight(), 0), 100);
    ofCircle(500, ofMap(hertz, 200, 2500, ofGetHeight(), 0), 100);
    ofSetColor(0);
    ofDrawBitmapString("volume", 200, ofGetHeight()-30);
    ofDrawBitmapString("pitch", 500, ofGetHeight()-30);
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
    
    for (int i = 0; i < bufferSize; i++){
        //cout << input[i] << endl;
        
        // first calcuation RMS of values
        squareTotal += (input[i]*input[i]);
        // or squareTotal += powf(intput[i], 2);
                
    }
    
    // 
    for (int i = 0; i < bufferSize-1; i++){
        if((input[i] > 0 && input[i+1] < 0) || (input[i] < 0 && input[i+1] > 0)){
            zeroCrossings++;
        }
    }
    
    
    
    // calculate final RMS value
    squareRoot = sqrt(squareTotal/bufferSize);
    // print RMS value to console
    cout << "RMS Value: " << squareRoot << "  Zero Crossings: " << zeroCrossings << endl;
    cout << "Hertz: " << hertz << endl;
    
    // calculate hertz
    hertz = (float)(zeroCrossings/2) * (float)(44100/bufferSize); // casting here makes little difference
    
    // assign value to volume
    volume = squareRoot;
    
}
