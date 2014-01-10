// time to wait between events
10::ms => dur t;

IntEvent ie;
FloatEvent fe;
StringEvent se;

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
