//
//  imageGrains.h
//  03-12-13-visual_grains
//
//  Created by Jennifer Presto on 3/10/13.
//
//

#ifndef ___3_12_13_visual_grains__imageGrains__
#define ___3_12_13_visual_grains__imageGrains__

#include <iostream>
#include "ofMain.h"

class imageGrain {

public:
    
    imageGrain();
    void generate();
    
    int scale;
    
    int numCols;
    int numRows;
    int redTarget;
    int blueTarget;
    int spread;
};

#endif /* defined(___3_12_13_visual_grains__imageGrains__) */
