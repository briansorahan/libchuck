class IntTestRunner extends OscTestRunner {
    fun void runServer(OscEvent ev) {
        while (ev.nextMsg() != 0) {
            ;
        }
    }

    fun void runClient(OscSend sender) {
        1 => sender.addInt;
    }
}

OscTest test;
IntTestRunner runner;
"Ints can be sent and received." => runner.message;
"/path/to/int" => runner.receivePattern;
runner.receivePattern => runner.sendPattern;
"i" => runner.typetag;
OscTest.run(test, runner);
