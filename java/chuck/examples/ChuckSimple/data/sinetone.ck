Events.receiveIntFrom("ChuckSimple") @=> IntEvent trig;

function void playTone(float freq, float gain) {
	SinOsc s => ADSR envelope => dac;
	freq => s.freq;
	gain => s.gain;
	envelope.set(10::ms, 2000::ms, 0.0, 10::ms);
	envelope.keyOn();
	2010::ms => now;
	envelope.keyOff();
	10::ms => now;
}

while (1) {
	trig => now;
	spork ~ playTone(Math.random2f(110.0, 880.0), Math.random2f(0.1, 0.7));
}