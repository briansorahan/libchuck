import edu.princeton.cs.chuck.Jchuck;
import edu.princeton.cs.chuck.IntReceiver;
import edu.princeton.cs.chuck.FloatReceiver;
import edu.princeton.cs.chuck.StringReceiver;
import org.junit.Test;
import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;
import java.util.concurrent.atomic.AtomicBoolean;

interface Chucky {
    void go(Jchuck ck);
}

@RunWith(JUnit4.class)
public class JchuckTest {
    private final Chucky noop = new Chucky() {
        public void go(Jchuck ck) {
        }
    };

    private void run(String[] files, Chucky chucky) {
        run(files, chucky, 0);
    }

    // the Chucky parameter allows clients to run some code that uses the newly created
    // Jchuck instance.
    private void run(String[] files, Chucky chucky, long mindur) {
        long start = System.currentTimeMillis();
        Jchuck ck = Jchuck.start();

        boolean sporked = ck.spork(files);
        org.junit.Assert.assertTrue("failed to spork files", sporked);

        chucky.go(ck);

        boolean finished = ck.run();
        org.junit.Assert.assertTrue(finished);

        long finish = System.currentTimeMillis();
        if (mindur > 0) {
            org.junit.Assert.assertTrue(mindur < finish - start);
        }
    }

    @Test
    public void JavaWaitsForChuck() {
        /*
         * THis test passes if I change the Chucky instance to noop.
         *
         * Something happens when I try to set up receivers from java
         * where the test thread does not wait for the chuck thread
         * when I call run().
         *
         * The symptom of this behavior is that chuck does not shut down
         * properly for this test and causes Chuck_Env::startup to fail
         * when it asserts that its singleton instance is NULL before it
         * instantiates a new one.
         */
        String[] files = { "../../test/waitThreeSeconds.ck" };
        SimpleReceive sr = new SimpleReceive();
        run(files, sr, 2700);
    }

    @Test
    public void BeepDefaultFrequency() {
        String[] files = { "../../test/sinetone.ck" };
        run(files, noop);
    }

    @Test
    public void Beep220() {
        String[] files = { "../../test/sinetone.ck:220" };
        run(files, noop);
    }

    @Test
    public void BeepBeats() {
        String[] files = {
            "../../test/sinetone.ck:440:0.48",
            "../../test/sinetone.ck:442:0.48"
        };
        run(files, noop);
    }

    //
    // Events API
    //

    @Test
    public void SendEventsFromJava() {
        String[] files = {
            "../../test/c2chuck.ck"
        };

        final Chucky sendEvents = new Chucky() {
            // FIXME: maybe change to a ping pong
            public void go(Jchuck ck) {
                ck.sendTo("foo", 4L);
                try {
                    Thread.currentThread().sleep(20);
                } catch (InterruptedException interrupt) {
                }
                ck.sendTo("bar", 3.14);
                try {
                    Thread.currentThread().sleep(20);
                } catch (InterruptedException interrupt) {
                }
                ck.sendTo("bar", "haha");
            }
        };

        run(files, sendEvents);
    }

    @Test
    public void ReceiveEventsFromChuck() {
        String[] files = {
            "../../test/chuck2c.ck"
        };

        SimpleReceive sr = new SimpleReceive();

        run(files, sr);
    }
}

/**
 * Provide a way to assert that we receive values from chuck
 */
class SimpleReceive implements Chucky {
    private final AtomicBoolean receivedInt;
    private final AtomicBoolean receivedFloat;
    private final AtomicBoolean receivedString;

    private final IntReceiver intrec;
    private final FloatReceiver floatrec;
    private final StringReceiver stringrec;

    SimpleReceive() {
        receivedInt = new AtomicBoolean(false);
        receivedFloat = new AtomicBoolean(false);
        receivedString = new AtomicBoolean(false);

        intrec = new IntReceiver() {
            public void receive(long val) {
                receivedInt.getAndSet(true);
            }
        };

        floatrec = new FloatReceiver() {
            public void receive(double val) {
                receivedFloat.getAndSet(true);
            }
        };

        stringrec = new StringReceiver() {
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
        org.junit.Assert.assertTrue(receivedInt.get());
    }

    public void assertReceivedFloat(double val) {
        org.junit.Assert.assertTrue(receivedFloat.get());
    }

    public void assertReceivedString(String val) {
        org.junit.Assert.assertTrue(receivedString.get());
    }
}
