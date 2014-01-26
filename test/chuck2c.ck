1::ms => dur d;

d => now;
Events.sendIntTo("foo", 4);

d => now;
Events.sendFloatTo("bar", 2.71);

d => now;
Events.sendStringTo("baz", "libchuck");

