class TwoArgsTestRunner extends OscTestRunner {
    fun void runServer(OscEvent ev) {
        while (ev.nextMsg() != 0) {
            ev.getInt();
            ev.getFloat();
        }
    }
    fun void runClient(OscSend sender) {
        1 => sender.addInt;
        3.14 => sender.addFloat;
    }
}

OscTest test;
TwoArgsTestRunner runner;
"Two args can be sent and received." => runner.message;
"/two/args" => runner.receivePattern;
runner.receivePattern => runner.sendPattern;
"if" => runner.typetag;
OscTest.run(test, runner);
