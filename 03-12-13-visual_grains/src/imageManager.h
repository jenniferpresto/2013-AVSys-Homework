//
//  imageManager.h
//  03-12-13-visual_grains
//
//  Created by Jennifer Presto on 3/10/13.
//
//

#ifndef ___3_12_13_visual_grains__imageManager__
#define ___3_12_13_visual_grains__imageManager__

#include <iostream>
#include "ofMain.h"
#include "imageGrain.h"

class imageManager{
public:
    
    imageManager();
    
    void update();
    void display();
    
    imageGrain grain;

    int imagesPerSecond;
    int durationInMillis;
    int startTime;
    int updateTime;
};

#endif /* defined(___3_12_13_visual_grains__imageManager__) */
