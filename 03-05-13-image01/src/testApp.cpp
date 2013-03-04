#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    
    img.allocate(640, 480, OF_IMAGE_COLOR);
    
    
}

//--------------------------------------------------------------
void testApp::update(){

    
    unsigned char * pixels = img.getPixels();
    
    
    // (note: the order of these for loops doesn't matter)
    
    for (int i = 0; i < 640; i++){
        for (int j = 0; j < 480; j++){
            
            // for color, took example from here:
            // http://wiki.openframeworks.cc/index.php?title=Iterate_over_pixels
            
            // Note: don't actually use red/green/blue variables
            
            int index = j * 640 * 3 + i * 3;
            int red = pixels[index];
            int green = pixels[index + 1];
            int blue = pixels[index + 2];
            
            pixels[index] = (sin(i)/20 + 1) * 127, 255;              // red values
            pixels[index + 1] = (sin(i)/20 + 1) * 127* j;       // green values
            pixels[index + 2] = (cos(j)/20 + 1) * 127 * mouseX; // blue values
            
            
        }
    }
    
    img.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){

    
    img.draw(0,0);
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