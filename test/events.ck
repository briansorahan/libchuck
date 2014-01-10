IntEvent ie;
FloatEvent fe;
StringEvent se;
// time to wait between events
10::ms => dur t;
// broadcast one after the other
function void and_beans() {
    t => now;
    4 => ie.val;
    ie.broadcast();

    t => now;
    3.14 => fe.val;
    fe.broadcast();

    t => now;
    "foo" => se.val;
    se.broadcast();
}
spork ~ and_beans();
ie => now;
fe => now;
se => now;

Events.receiveIntFrom("foo") @=> IntEvent intev;
Events.receiveFloatFrom("foo") @=> FloatEvent floatev;
Events.receiveStringFrom("foo") @=> StringEvent stringev;

function void tenderloin() {
    t => now;
    2 => intev.val;
    intev.broadcast();

    t => now;
    3.14 => floatev.val;
    floatev.broadcast();

    t => now;
    "bar" => stringev.val;
    stringev.broadcast();
}

spork ~ tenderloin();
intev => now;
floatev => now;
stringev => now;
