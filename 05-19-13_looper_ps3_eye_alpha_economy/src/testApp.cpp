/*
 Jennifer Presto
 AVSys Final
 May 19, 2013
 
 Looping images plus layered soundtracks
 
 */

#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
    ofEnableAlphaBlending();
    
	camWidth = CAMWIDTH;
	camHeight = CAMHEIGHT;
	
    // ps3eye-specific settings
	ps3eye.listDevices(); // goes to console
	
	ps3eye.setDesiredFrameRate(60);
	ps3eye.initGrabber(camWidth,camHeight);
	
	ps3eye.setAutoGainAndShutter(false); // otherwise we can't set gain or shutter
	ps3eye.setGain(0.2);  // if use 640x480 image, make 0.4
	ps3eye.setShutter(1.0);
	ps3eye.setGamma(0.4);
	ps3eye.setBrightness(0.4); // if use 640x480 image, make 0.5
	ps3eye.setContrast(0.7);
    //	ps3eye.setHue(0.0); // this made things really yellow
	
	ps3eye.setFlicker(0);
    
    // allocate background
    background.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    grayImageForAlpha.allocate(camWidth, camHeight, OF_IMAGE_GRAYSCALE);
    
    
    // images to be used (set 1)
    displayImage.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    
    // images to be used (set 2)
    displayImage2.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut2.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    
    // images to be used (set 3)
    displayImage3.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut3.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    
    // images to be used (set 4)
    displayImage4.allocate(camWidth, camHeight, OF_IMAGE_COLOR);
    displayCutOut4.allocate(camWidth, camHeight, OF_IMAGE_COLOR_ALPHA);
    
    // temp (and awesome) background
    tulips.loadImage("holland_tulips.jpg");
    
    // threshold for background subtractions
    threshold = 400;
}


//--------------------------------------------------------------
void testApp::update(){
	
    // when press spacebar, capture the background
    if(ofGetKeyPressed(' ')){
        if(ps3eye.isFrameNew()){
            background.setFromPixels(ps3eye.getPixelsRef());
            backgroundPixels = background.getPixels();          // pixels from bg image
            
            // fill array of bgPixel vectors with the RGB values of each background pixel
            for(int i=0; i < camWidth; i++){
                for(int j=0; j < camHeight; j++){
                    bgPixels[j*camWidth + i].set(backgroundPixels[(j*camWidth + i)*3], backgroundPixels[(j*camWidth + i)*3 + 1], backgroundPixels[(j*camWidth + i)*3 + 2]);
                }
            }
        }
    }
    
    // when press a, record from camera (each frame adds an image to vector)
    if(ofGetKeyPressed('a')){
        if(ps3eye.isFrameNew()){
            unsigned char * grayPixels = grayImageForAlpha.getPixels();     // will be alpha channel
            unsigned char * colorPixels = ps3eye.getPixels();               // pixels from camera
            unsigned char * colorAlphaPixels = displayCutOut.getPixels();   // camera plus alpha
            
            // compare against the background to determine the alpha for the image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    // convert RGB values of each pixel into a vector
                    // background pixels already converted when spacebar pressed
                    // now do it for image being recorded
                    rgbPixels[j*camWidth+i].set(colorPixels[(j*camWidth + i) * 3], colorPixels[(j*camWidth + i) * 3 + 1], colorPixels[(j*camWidth + i) * 3 + 2]);
                    
                    // compare bgPixels to rgbPixels to create a black-and-white alpha mask
                    grayPixels[j*camWidth + i] = bgPixels[j*camWidth + i].squareDistance(rgbPixels[j*camWidth + i]) > threshold ? 255 : 0;
                    
                }
            }
            
            // apply the alpha mask when creating new cut-out color image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    colorAlphaPixels[(j*camWidth + i) * 4] = colorPixels[(j*camWidth + i) * 3];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 1] = colorPixels[(j*camWidth + i) * 3 + 1];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 2] = colorPixels[(j*camWidth + i) * 3 + 2];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 3] = grayPixels[j*camWidth + i];
                }
            }
            
            displayCutOut.update();
            
            ofImage temp;
            temp.setUseTexture(false); // none have texture; stores only in RAM
            temp.setFromPixels(displayCutOut.getPixelsRef());
            images.push_back(temp);
        }
    }
    
    // when press b, record a different loop from the camera (each frame adds an image to a different vector)
    if(ofGetKeyPressed('b')){
        if(ps3eye.isFrameNew()){
            unsigned char * grayPixels = grayImageForAlpha.getPixels();     // will be alpha channel
            unsigned char * colorPixels = ps3eye.getPixels();               // pixels from camera
            unsigned char * colorAlphaPixels = displayCutOut2.getPixels();   // camera plus alpha
            
            // compare against the background to determine the alpha for the image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    // convert RGB values of each pixel into a vector
                    // background pixels already converted when spacebar pressed
                    // now do it for image being recorded
                    rgbPixels[j*camWidth+i].set(colorPixels[(j*camWidth + i) * 3], colorPixels[(j*camWidth + i) * 3 + 1], colorPixels[(j*camWidth + i) * 3 + 2]);
                    
                    // compare bgPixels to rgbPixels to create a black-and-white alpha mask
                    grayPixels[j*camWidth + i] = bgPixels[j*camWidth + i].squareDistance(rgbPixels[j*camWidth + i]) > threshold ? 255 : 0;
                    
                }
            }
            
            // apply the alpha mask when creating new cut-out color image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    colorAlphaPixels[(j*camWidth + i) * 4] = colorPixels[(j*camWidth + i) * 3];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 1] = colorPixels[(j*camWidth + i) * 3 + 1];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 2] = colorPixels[(j*camWidth + i) * 3 + 2];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 3] = grayPixels[j*camWidth + i];
                }
            }
            
            displayCutOut2.update();

            ofImage temp;
            temp.setUseTexture(false); // store only in RAM
            temp.setFromPixels(displayCutOut2.getPixelsRef());
            images2.push_back(temp);
        }
    }
    
    // when press c, record a different loop from the camera (each frame adds an image to a different vector)
    if(ofGetKeyPressed('c')){
        if(ps3eye.isFrameNew()){
            unsigned char * grayPixels = grayImageForAlpha.getPixels();     // will be alpha channel
            unsigned char * colorPixels = ps3eye.getPixels();               // pixels from camera
            unsigned char * colorAlphaPixels = displayCutOut3.getPixels();   // camera plus alpha
            
            // compare against the background to determine the alpha for the image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    // convert RGB values of each pixel into a vector
                    // background pixels already converted when spacebar pressed
                    // now do it for image being recorded
                    rgbPixels[j*camWidth+i].set(colorPixels[(j*camWidth + i) * 3], colorPixels[(j*camWidth + i) * 3 + 1], colorPixels[(j*camWidth + i) * 3 + 2]);
                    
                    // compare bgPixels to rgbPixels to create a black-and-white alpha mask
                    grayPixels[j*camWidth + i] = bgPixels[j*camWidth + i].squareDistance(rgbPixels[j*camWidth + i]) > threshold ? 255 : 0;
                    
                }
            }
            
            // apply the alpha mask when creating new cut-out color image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    colorAlphaPixels[(j*camWidth + i) * 4] = colorPixels[(j*camWidth + i) * 3];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 1] = colorPixels[(j*camWidth + i) * 3 + 1];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 2] = colorPixels[(j*camWidth + i) * 3 + 2];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 3] = grayPixels[j*camWidth + i];
                }
            }
            
            displayCutOut3.update();
            
            ofImage temp;
            temp.setUseTexture(false); // store only in RAM
            temp.setFromPixels(displayCutOut3.getPixelsRef());
            images3.push_back(temp);
        }
    }
    
    // when press d, record a different loop from the camera (each frame adds an image to a different vector)
    if(ofGetKeyPressed('d')){
        if(ps3eye.isFrameNew()){
            unsigned char * grayPixels = grayImageForAlpha.getPixels();     // will be alpha channel
            unsigned char * colorPixels = ps3eye.getPixels();               // pixels from camera
            unsigned char * colorAlphaPixels = displayCutOut4.getPixels();   // camera plus alpha
            
            // compare against the background to determine the alpha for the image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    // convert RGB values of each pixel into a vector
                    // background pixels already converted when spacebar pressed
                    // now do it for image being recorded
                    rgbPixels[j*camWidth+i].set(colorPixels[(j*camWidth + i) * 3], colorPixels[(j*camWidth + i) * 3 + 1], colorPixels[(j*camWidth + i) * 3 + 2]);
                    
                    // compare bgPixels to rgbPixels to create a black-and-white alpha mask
                    grayPixels[j*camWidth + i] = bgPixels[j*camWidth + i].squareDistance(rgbPixels[j*camWidth + i]) > threshold ? 255 : 0;
                    
                }
            }
            
            // apply the alpha mask when creating new cut-out color image
            for (int i = 0; i < camWidth; i++){
                for (int j = 0; j < camHeight; j++){
                    colorAlphaPixels[(j*camWidth + i) * 4] = colorPixels[(j*camWidth + i) * 3];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 1] = colorPixels[(j*camWidth + i) * 3 + 1];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 2] = colorPixels[(j*camWidth + i) * 3 + 2];
                    colorAlphaPixels[(j*camWidth + i) * 4 + 3] = grayPixels[j*camWidth + i];
                }
            }
            
            displayCutOut4.update();

            ofImage temp;
            temp.setUseTexture(false); // store only in RAM
            temp.setFromPixels(displayCutOut4.getPixelsRef());
            images4.push_back(temp);
        }
    }
    
	ps3eye.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    ps3eye.draw(0,0);
    
    background.draw(640, 0, 320, 240);
    tulips.draw(640, 240, 320, 240);
    
    if (images.size() > 0){
        int whichImage = ofGetFrameNum() % images.size();
        displayImage.setFromPixels(images[whichImage].getPixelsRef());
        displayImage.draw(0,240);
        displayImage.draw(640, 240);
    }
    
    if(images2.size() > 0){
        int whichImage = ofGetFrameNum() % images2.size();
        displayImage2.setFromPixels(images2[whichImage].getPixelsRef());
        displayImage2.draw(320, 240);
        displayImage2.draw(640, 240);
    }
    
    if(images3.size() > 0){
        int whichImage = ofGetFrameNum() % images3.size();
        displayImage3.setFromPixels(images3[whichImage].getPixelsRef());
        displayImage3.draw(0, 480);
        displayImage3.draw(640, 240);
    }
    
    if(images4.size() > 0){
        int whichImage = ofGetFrameNum() % images4.size();
        displayImage4.setFromPixels(images4[whichImage].getPixelsRef());
        displayImage4.draw(320, 480);
        displayImage4.draw(640, 240);
    }
    
    
    ofDrawBitmapString("Press spacebar to set background", 10, 10);
	ofDrawBitmapString("Ps3Eye FPS: "+ ofToString(ps3eye.getRealFrameRate()), 10, 20);
}






//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key == ' '){
        images.clear();
        images2.clear();
        images3.clear();
        images4.clear();
    }
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
