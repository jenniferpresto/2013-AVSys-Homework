//
//  soundCircle.cpp
//  04-16-13-sequencer
//
//  Created by Jennifer Presto on 4/14/13.
//
//

#include "soundCircle.h"

// ----------------------------------
// constructor
soundCircle::soundCircle(int x, int y, int size){
    xPos = x;
    yPos = y;
    radius = size * 40;
    freq = 0;
    active = false;
}


// ----------------------------------
void soundCircle::display(bool activated){
    if(!activated){
        for(int i=radius; i>=1; i-=10){
            ofSetColor(ofColor::black);
            ofCircle(xPos, yPos, i);
        }
    }
    if(activated){
        for(int i=radius; i>=1; i-=10){
            ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
            ofCircle(xPos, yPos, i);
        }
    }
}