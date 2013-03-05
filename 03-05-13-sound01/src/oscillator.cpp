
#include "oscillator.h"


    
void oscillator::setup (int rate){
    sampleRate = rate;
}

void oscillator::setFrequency (float freq){
    frequency = freq;
    phaseAdder = (float)(frequency * PI) / (float)sampleRate;
}

void oscillator::setVolume (float vol){
    volume = vol;
}

float oscillator::getSample(){
    phase += phaseAdder;
    while (phase > PI) phase -= PI;
    return sin(phase) * volume;
}

