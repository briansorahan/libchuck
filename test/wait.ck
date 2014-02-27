int msecs;
if (me.args() > 0) {
    me.arg(0) => Std.atoi => msecs;
} else {
    100 => msecs;
}
msecs::ms => now;
