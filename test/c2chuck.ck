//
// Sending events from C to Chuck using the Events API
//
Events.receiveIntFrom("foo") @=> IntEvent ev;
ev => now;
if (ev.val() != 4) {
    cherr <= "Expected 4 but received " <= ev.val() <= " instead" <= IO.newline();
}
