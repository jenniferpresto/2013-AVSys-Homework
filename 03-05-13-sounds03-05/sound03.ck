SinOsc carrier => dac;
SinOsc modulator => blackhole;

float lowFreq;
float highFreq;

200 => lowFreq;
300 => highFreq;

800 => modulator.freq;

while (5::ms => now){
    lowFreq + ( modulator.last() * 0.5 + 0.5  ) * (highFreq - Std.rand2f(30, 1000))  => carrier.freq;
}
