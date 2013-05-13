// This turned into mostly failed mashup of
// whirl and basic FM synthesis

// basic FM synthesis using sinosc



// modulator to carrier
SinOsc m => SinOsc c => dac;

// tried to add echo; didn't work
//c => Gain feedback => DelayL delay => c;

//.75::second => delay.max => delay.delay;
//.75 => delay.gain;
//.5 => feedback.gain;

0.0 => float t;

// carrier frequency
//220 => c.freq;
// index of modulation
200 => m.gain;

// phase modulation is FM synthesis (sync is 2)



// time-loop
while( true ){
    // modulator frequency
    30 + (Math.sin(t) + 1.0) * 300 => m.freq;
    30 + (Math.cos(t) + 1.0) * 100 => c.freq;
//    3 => c.sync;
    t + .004 => t;
    5::ms => now;
 }