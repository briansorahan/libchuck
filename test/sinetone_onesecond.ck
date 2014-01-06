float freq;
float gain;

if (me.args() > 0) {
    Std.atof(me.arg(0)) => freq;
} else {
    440.0 => freq;
}

if (me.args() > 1) {
    Std.atof(me.arg(1)) => gain;
} else {
    0.5 => gain;
}

SinOsc s => dac;
gain => s.gain;
freq => s.freq;
2::second => now;