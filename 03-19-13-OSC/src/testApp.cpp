#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    sender.setup("localhost", 5001);
    ofSetVerticalSync(true);
    quadrants.loadImage("quadrants.png");
    
}

//--------------------------------------------------------------
void testApp::update(){
    
}

//--------------------------------------------------------------
void testApp::draw(){

    quadrants.draw(0,0);
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
    //one
    if(x > 0 && x < 512 && y > 0 && y < 384){
        cout << "one" << endl;
        ofxOscMessage message;
        message.setAddress("/voicetrigger");
        message.addIntArg(1);
        sender.sendMessage(message);
    }
    //two
    if(x >= 512 && x < 1024 && y > 0 && y < 384){
        cout << "two" << endl;
        ofxOscMessage message;
        message.setAddress("/voicetrigger");
        message.addIntArg(2);
        sender.sendMessage(message);
    }
    //three
    if(x > 0 && x < 512 && y >= 384 && y < 768){
        cout << "three" << endl;
        ofxOscMessage message;
        message.setAddress("/voicetrigger");
        message.addIntArg(3);
        sender.sendMessage(message);
    }
    //four
    if(x >= 512 && x < 1024 && y >= 384 && y < 768){
        cout << "four" << endl;
        ofxOscMessage message;
        message.setAddress("/voicetrigger");
        message.addIntArg(4);
        sender.sendMessage(message);
    }
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