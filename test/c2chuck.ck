//
// Sending events from C to Chuck using the Events API
//

Events.receiveIntFrom("foo") @=> IntEvent ev;
ev => now;
if (ev.val() != 4) {
    cherr <= "Expected 4 but received " <= ev.val() <= IO.newline();
} else {
    // chout <= "Got expected value of " <= ev.val() <= IO.newline();
}

Events.receiveFloatFrom("bar") @=> FloatEvent fev;
fev => now;
if (fev.val() != 3.14) {
    cherr <= "Expected 3.14 but received " <= fev.val() <= IO.newline();
}

Events.receiveStringFrom("bar") @=> StringEvent sev;
sev => now;
if (sev.val() != "haha") {
    cherr <= "Expected 'haha' but received " <= sev.val() <= IO.newline();
}