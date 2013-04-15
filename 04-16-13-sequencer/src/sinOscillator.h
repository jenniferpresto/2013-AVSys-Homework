//
//  sinOscillator.h
//  04-16-13-sequencer
//
//  Created by Jennifer Presto on 4/14/13.
//
//

#ifndef ___4_16_13_sequencer__sinOscillator__
#define ___4_16_13_sequencer__sinOscillator__

#include <iostream>
#include "ofMain.h"

class sinOscillator{
public:
    
	void	setup();
	void	setFrequency(float newFrequency);
	void	setVolume(float newVolume);
	void	addToSoundBuffer(float * buffer, int bufferSize);
	
	float 	pan;
	int		sampleRate;
	float 	volume;
	float	frequency;
    
	float	angle;
	float	angleAdder;
    
	
};

#endif /* defined(___4_16_13_sequencer__sinOscillator__) */
