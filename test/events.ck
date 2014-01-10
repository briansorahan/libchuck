10::ms => dur t;

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
