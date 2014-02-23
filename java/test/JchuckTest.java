import edu.princeton.cs.chuck.Jchuck;
import org.junit.Test;
// import org.junit.Ignore;
import org.junit.runner.RunWith;
import org.junit.runners.JUnit4;

// import static org.junit.Assert.assertTrue;

interface Chucky {
    void go(Jchuck ck);
}

@RunWith(JUnit4.class)
public class JchuckTest {
    // the Chucky parameter allows clients to run some code that uses the newly created
    // Jchuck instance.
    private void run(String[] files, Chucky chucky) {
        Jchuck ck = new Jchuck();
        org.junit.Assert.assertTrue("failed to spork files", ck.spork(files));
        chucky.go(ck);
        ck.run();
    }

    @Test
    public void BeepDefaultFrequency() {
        // spork a file that makes a sine wave
        String[] files = { "../../test/sinetone.ck" };
        final Chucky chucky = new Chucky() {
            public void go(Jchuck ck) {
            }
        };
        run(files, chucky);
    }

    @Test
    public void Beep220() {
        // spork a file that makes a sine wave
        String[] files = { "../../test/sinetone.ck:220" };
        final Chucky chucky = new Chucky() {
            public void go(Jchuck ck) {
            }
        };
        run(files, chucky);
    }

    @Test
    public void BeepBeats() {
        // spork a file that makes a sine wave
        String[] files = {
            "../../test/sinetone.ck:440:0.48",
            "../../test/sinetone.ck:442:0.48"
        };
        final Chucky chucky = new Chucky() {
            public void go(Jchuck ck) {
            }
        };
        run(files, chucky);
    }
}
