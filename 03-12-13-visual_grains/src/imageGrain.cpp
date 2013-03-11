//
//  imageGrains.cpp
//  03-12-13-visual_grains
//
//  Created by Jennifer Presto on 3/10/13.
//
//

#include "imageGrain.h"

imageGrain::imageGrain(){
    scale = 80;                     // how divided screen will be
    numCols = ofGetWidth()/scale;
    numRows = ofGetHeight()/scale;
}

void imageGrain::generate(){
    for (int i=0; i < numCols; i++) {
        for(int j=0; j<numRows; j++){
            ofSetColor((int)ofRandom(redMin, redMax), 0, (int)ofRandom(blueMin, blueMax));
            ofRect(i*scale, j*scale, scale, scale);
        }
    }
}