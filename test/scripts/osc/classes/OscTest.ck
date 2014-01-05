public class OscTest {
    Event done;
    Event serverReady;
    23145 => int port;

    //@spork
    fun void server(OscTestRunner runner) {
        // set up receiver
        OscRecv receiver;
        port => receiver.port;
        receiver.listen();
        receiver.event(runner.receivePattern + "," + runner.typetag) @=> OscEvent oscev;
        // fire the server "ready" event
        serverReady.signal();
        // wait for an OSC event
        oscev => now;
        // delegate to the runner
        runner.runServer(oscev);
        done.signal();
    }

    //@spork
    fun void client(OscTestRunner runner) {
        // wait for the server "ready" event
        serverReady => now;
        // let the runner send the server a message
        OscSend sender;
        sender.setHost("localhost", port);
        sender.startMsg(runner.sendPattern, runner.typetag);
        runner.runClient(sender);
    }

    // TODO: figure out why this never exits
    fun static void run(OscTest test, OscTestRunner runner) {
        spork ~ test.client(runner);
        spork ~ test.server(runner);
        test.done => now;
        chout <= "ok - " + runner.message <= IO.newline();
    }
}

