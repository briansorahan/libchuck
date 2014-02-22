SinOsc s => dac;
0.5 => s.gain;
220 => s.freq;
500::ms => now;