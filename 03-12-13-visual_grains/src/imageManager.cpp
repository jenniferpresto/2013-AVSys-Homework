//
//  imageManager.cpp
//  03-12-13-visual_grains
//
//  Created by Jennifer Presto on 3/10/13.
//
//

#include "imageManager.h"

imageManager::imageManager(){
    imagesPerSecond = 2;
    durationInMillis = (int)1000/imagesPerSecond;
    startTime = ofGetElapsedTimeMillis();
}

void imageManager::update(){
    imagesPerSecond = ofMap(sin(ofGetElapsedTimef()), -1, 1, 2, 30);
    durationInMillis = (int)1000/imagesPerSecond;
    grain.redMax = ofMap(ofGetMouseX(), 0, ofGetWidth(), 255, 10);
    grain.blueMax = ofMap(ofGetMouseX(), 0, ofGetWidth(), 10, 255);
    grain.redMin = ofMap(ofGetMouseY(), 0, ofGetHeight(), 255, 10);
    grain.blueMin = ofMap(ofGetMouseY(), 0, ofGetHeight(), 255, 10);
    
}

void imageManager::display(){
    if(ofGetElapsedTimeMillis() - startTime > durationInMillis){
        grain.generate();
        startTime = ofGetElapsedTimeMillis();
    }
}
