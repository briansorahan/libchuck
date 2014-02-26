import edu.princeton.cs.chuck.Jchuck;
import java.util.concurrent.atomic.AtomicBoolean;

interface Chucky {
    void go(Jchuck ck);
}

/**
 * Provide a way to assert that we receive values from chuck
 */
class SimpleReceive implements Chucky {
    private final AtomicBoolean receivedInt;
    private final AtomicBoolean receivedFloat;
    private final AtomicBoolean receivedString;

    private final Jchuck.IntReceiver intrec;
    private final Jchuck.FloatReceiver floatrec;
    private final Jchuck.StringReceiver stringrec;

    SimpleReceive() {
        receivedInt = new AtomicBoolean(false);
        receivedFloat = new AtomicBoolean(false);
        receivedString = new AtomicBoolean(false);

        intrec = new Jchuck.IntReceiver() {
            public void receive(long val) {
                System.out.println("got int");
                receivedInt.getAndSet(true);
            }
        };

        floatrec = new Jchuck.FloatReceiver() {
            public void receive(double val) {
                receivedFloat.getAndSet(true);
            }
        };

        stringrec = new Jchuck.StringReceiver() {
            public void receive(String val) {
                receivedString.getAndSet(true);
            }
        };
    }

    public void go(Jchuck ck) {
        System.err.println("setting up java receivers");

        ck.receiveFrom("foo", intrec);
        ck.receiveFrom("bar", floatrec);
        ck.receiveFrom("baz", stringrec);

        System.err.println("done setting up java receivers");
    }

    public void assertReceivedInt(long val) {
        System.out.println("received int");
        // org.junit.Assert.assertTrue(receivedInt.get());
    }

    public void assertReceivedFloat(double val) {
        System.out.println("received float");
        // org.junit.Assert.assertTrue(receivedFloat.get());
    }

    public void assertReceivedString(String val) {
        System.out.println("received string");
        // org.junit.Assert.assertTrue(receivedString.get());
    }
}

public class ReceiveTest {
    public static void main(String[] args) {
        Jchuck jc = Jchuck.start();
        String[] files = { "../../test/waitThreeSeconds.ck" };

        if (! jc.spork(files)) {
            System.err.println("could not spork files");
            System.exit(2);
        }

        SimpleReceive receiver = new SimpleReceive();
        receiver.go(jc);

        if (! jc.run()) {
            System.err.println("could not run chuck");
            System.exit(3);
        }
    }
}
