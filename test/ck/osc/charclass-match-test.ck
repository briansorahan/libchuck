class CharClassMatchTestRunner extends OscTestRunner {
    //@override
    fun void runServer(OscEvent oscev) {
        while (oscev.nextMsg() != 0) {
            ;
        }
    }
    //@override
    fun void runClient(OscSend sender) {
        "hello" => sender.addString;
    }
}

23145 => int port;

// Server code
function void server(Event done) {
    OscRecv receiver;
    port => receiver.port;
    receiver.listen();
    receiver.event("/path/to/string,s") @=> OscEvent oscev;
    oscev => now;
    while (oscev.nextMsg() != 0) {
        // <<< oscev.getString() >>>;
    }
    done.signal();
}

// Client code
// @param (dur delayStart) How long the client will wait for the server to start
function void client(dur delayStart) {
    delayStart => now;
    OscSend sender;
    sender.setHost("localhost", port);
    sender.startMsg("/path/to/strin[abcdefg]", "s");
    "hello" => sender.addString;
}

OscTest test;
CharClassMatchTestRunner runner;
"Char Class Matching." => runner.message;
"/path/to/strin[efg]" => runner.sendPattern;
"/path/to/string" => runner.receivePattern;
"s" => runner.typetag;
OscTest.run(test, runner);