class CharClassRangeTestRunner extends OscTestRunner {
    //@override
    fun void runServer(OscEvent ev) {
        while (ev.nextMsg() != 0) {
            ;
        }
    }
    //@override
    fun void runClient(OscSend sender) {
        "hello" => sender.addString;
    }
}

OscTest test;
CharClassRangeTestRunner runner;
"Char class range matching." => runner.message;
"/path/to/string" => runner.receivePattern;
"/path/to/strin[e-h]" => runner.sendPattern;
"s" => runner.typetag;
OscTest.run(test, runner);