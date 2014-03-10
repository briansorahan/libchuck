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

// infinite loop
while (1) {
	trig => now;
	spork ~ playTone(Math.random2f(300.0, 500.0), 0.2);
}