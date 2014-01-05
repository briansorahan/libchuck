class SingleCharMatchTestRunner extends OscTestRunner {
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

OscTest test;
SingleCharMatchTestRunner runner;

"Single char matching." => runner.message;
"/path/to/string" => runner.receivePattern;
"/path/to/strin?" => runner.sendPattern;
"s" => runner.typetag;
OscTest.run(test, runner);
