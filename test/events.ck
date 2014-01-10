10::ms => dur t;

// ---------------------------------------------------
// sending and receiving int, float, and string events
// ---------------------------------------------------

666 => int intval;
3.14 => float floatval;
"libchuck" => string stringval;

function void tenderloin() {
    t => now;
    Events.sendIntTo("foo", intval);

    t => now;
    Events.sendFloatTo("foo", floatval);

    t => now;
    Events.sendStringTo("foo", stringval);
}

spork ~ tenderloin();

Events.receiveIntFrom("foo") @=> IntEvent intev;
intev => now;
if (intev.val() != intval) {
    cherr <= "Failed to send int." <= IO.newline();
    Machine.crash();
}

Events.receiveFloatFrom("foo") @=> FloatEvent floatev;
floatev => now;
if (floatev.val() != floatval) {
    cherr <= "Failed to send float." <= IO.newline();
    Machine.crash();
}

Events.receiveStringFrom("foo") @=> StringEvent stringev;
stringev => now;
if (stringev.val() != stringval) {
    cherr <= "Failed to send string." <= IO.newline();
    Machine.crash();
}

// ----------------------------
// make sure channels are typed
// ----------------------------

function void broadcastNowhere() {
    t => now;
    Events.sendStringTo("nowhere", "sville");
}

function void neverFinish() {
    Events.receiveIntFrom("nowhere") @=> IntEvent forever;
    forever => now;
    cherr <= "Never should make it here!" <= IO.newline();
}

spork ~ broadcastNowhere() @=> Shred @ sender;
spork ~ neverFinish() @=> Shred @ receiver;

2 * t => now;
if (receiver.done()) {
    cherr <= "Houston, we have a problem." <= IO.newline();
    Machine.crash();
}
