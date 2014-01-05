class StringTestRunner extends OscTestRunner {
    fun void runServer(OscEvent ev) {
        while (ev.nextMsg() != 0) {
            ;
        }
    }
    fun void runClient(OscSend sender) {
        "hello" => sender.addString;
    }
}

OscTest test;
StringTestRunner runner;
"Strings can be sent and received." => runner.message;
"/path/to/string" => runner.receivePattern;
runner.receivePattern => runner.sendPattern;
"s" => runner.typetag;
OscTest.run(test, runner);
