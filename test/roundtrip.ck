//
// Test sending events from chuck that trigger
// a c event handler which then triggers another
// chuck event.
//
// Brian Sorahan
// bsorahan@gmail.com
//
Events.sendIntTo("foo", 1);
// signal string event on channel 'bar'
Events.receiveStringFrom("bar") @=> StringEvent barStrings;
// wait for string from 'bar'
// barStrings => now;
