SinOsc osc => dac;
SinOsc osc2 => dac;
SinOsc osc3 => dac;
SinOsc osc4 => dac;
SinOsc osc5 => dac;

300.0 => osc.freq;
301.0 => osc2.freq;
302.0 => osc3.freq;
303.0 => osc4.freq;
1000 => osc5.freq;

0 => osc2.gain;
1000::ms => now;

1 => osc2.gain;
2000::ms => now;

2 => osc3.gain;
3000::ms => now;

3 => osc4.gain;
4000::ms => now;
