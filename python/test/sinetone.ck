SinOsc s => dac;
0.5 => s.gain;
440.0 => s.freq;
500::ms => now;
