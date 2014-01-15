//
// Sending events from C to Chuck using the Events API
//

Events.receiveIntFrom("glorp") @=> IntEvent ev;
ev => now;
if (ev.val() != 4) {
    cherr <= "Expected 4 but received " <= ev.val() <= " instead" <= IO.newline();
} else {
    // chout <= "Got expected value of " <= ev.val() <= IO.newline();
}
