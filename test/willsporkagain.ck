Event done;

function void secondtone() {
    SinOsc s2 => dac;
    0.49 => s2.gain;
    448 => s2.freq;
    2::second => now;
    done.signal();
}

SinOsc s1 => dac;
0.49 => s1.gain;
440 => s1.freq;
spork ~ secondtone();
done => now;
