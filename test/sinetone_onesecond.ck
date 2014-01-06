float freq;

if (me.args() > 0) {
    Std.atof(me.arg(0)) => freq;
} else {
    440.0 => freq;
}

SinOsc s => dac;
0.5 => s.gain;
freq => s.freq;
2::second => now;