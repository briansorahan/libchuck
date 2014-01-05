23145 => int port;

// Server code
function void server(Event done, Event ready) {
    OscRecv receiver;
    port => receiver.port;
    receiver.listen();
    receiver.event("/path/to/abc,s") @=> OscEvent oscev;
    ready.signal();
    oscev => now;
    while (oscev.nextMsg() != 0) {
        // <<< oscev.getString() >>>;
    }
    done.signal();
}

// Client code
function void client(Event serverReady) {
    serverReady => now;
    OscSend sender;
    sender.setHost("localhost", port);
    sender.startMsg("/path/to/{abc,def,ghi}", "s");
    "hello" => sender.addString;
}

Event done;
Event serverReady;
spork ~ server(done, serverReady);
spork ~ client(serverReady);
done => now;
