/*********************************************
 
 Jennifer Presto
 AVSys Homework for April 2, 2013
 Adapted from in-class example for FFT
 
 *********************************************/

#include "testApp.h"
		
//--------------------------------------------------------------
void testApp::setup(){	 
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// BUFFER_SIZE samples per buffer
	// 4 num buffers (latency)
	
	ofSoundStreamSetup(0,2,this, 44100, BUFFER_SIZE, 4);	
	
	//left = new float[BUFFER_SIZE];
	//right = new float[BUFFER_SIZE];

	
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
	
	FFTanalyzer.peakHoldTime = 15; // hold longer
	FFTanalyzer.peakDecayRate = 0.95f; // decay slower
	FFTanalyzer.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = 0.01f; // increasing gain at higher frequencies
	
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    bgColor.setHsb(0, 0, 0);
    ofBackground(bgColor);
    ofSetBackgroundAuto(false);
    
    xPos = 0;
    counter = 0;
}


//--------------------------------------------------------------
void testApp::update(){
    float avg_power = 0.0f;
    
	/* do the FFT	*/
	myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
    
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		freq[i] = magnitude[i];
        cout << freq[i] << endl;
	}
	
	FFTanalyzer.calculate(freq);
    
//    cout << FFTanalyzer.nAverages << endl; // JP note: this does not work in draw function
    
    counter++;
    xPos = counter%ofGetWidth();
    
//    cout << xPos;

}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(0, 0, 0);
    ofRect(xPos+1, 0, 2, ofGetHeight());
    for(int i = 0; i < FFTanalyzer.nAverages; i++){
        float yPos = i * ofGetWidth()/FFTanalyzer.nAverages;
        float hue = 0;
        // note that clamping below seems to have very little effect
        if(freq[i]<1){
            hue = ofMap(freq[i], 0, 1, 0, 90, true);
        }
        if(freq[i]>=1){
            hue = ofMap(freq[i],1, 10, 90, 360, true);
        }
        rectColor.setHsb(hue, 100, 100);
        ofSetColor(rectColor);
        ofRect(xPos, yPos, 2, ofGetHeight()/FFTanalyzer.nAverages+4);
    }
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	
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
void testApp::mouseReleased(){

}

//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
}

