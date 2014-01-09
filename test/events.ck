IntEvent ie;
FloatEvent fe;
StringEvent se;
// time to wait between events
20::ms => dur t;
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
<<< ie.val() >>>;
fe => now;
<<< fe.val() >>>;
se => now;
<<< se.val() >>>;
