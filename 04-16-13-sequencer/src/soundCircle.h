//
//  soundCircle.h
//  04-16-13-sequencer
//
//  Created by Jennifer Presto on 4/14/13.
//
//

#ifndef ___4_16_13_sequencer__soundCircle__
#define ___4_16_13_sequencer__soundCircle__

#include <iostream>
#include "ofMain.h"

class soundCircle{
    
public:
    
    float xPos;
    float yPos;
    float radius;
    float freq;
    
    void display(bool activated);
    bool active;
    
    soundCircle(int x, int y, int size); // constructor
    
};

#endif /* defined(___4_16_13_sequencer__soundCircle__) */
