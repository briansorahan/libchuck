class FloatTestRunner extends OscTestRunner {
    fun void runServer(OscEvent ev) {
        while (ev.nextMsg() != 0) {
            ;
        }
    }
    fun void runClient(OscSend sender) {
        1.0 => sender.addFloat;
    }
}

OscTest test;
FloatTestRunner runner;
"Floats can be sent and received." => runner.message;
"/path/to/float" => runner.receivePattern;
runner.receivePattern => runner.sendPattern;
"f" => runner.typetag;
OscTest.run(test, runner);
