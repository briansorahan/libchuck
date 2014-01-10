// time to wait between events
1000::ms => dur t;

Events.receiveIntFrom("foo") @=> IntEvent intev;
Events.receiveFloatFrom("foo") @=> FloatEvent floatev;
Events.receiveStringFrom("foo") @=> StringEvent stringev;

function void tenderloin() {
    t => now;
    Events.sendIntTo("foo", 2);
    // 2 => intev.val;
    // intev.broadcast();

    t => now;
    Events.sendFloatTo("foo", 3.14);
    // 3.14 => floatev.val;
    // floatev.broadcast();

    t => now;
    Events.sendStringTo("foo", "bar");
    // "bar" => stringev.val;
    // stringev.broadcast();
}

spork ~ tenderloin();
intev => now;
<<< intev.val() >>>;
floatev => now;
<<< floatev.val() >>>;
stringev => now;
<<< stringev.val() >>>;

