import edu.princeton.cs.chuck.Jchuck;

class BeepTest {
    public static void main(String[] args) {
        System.out.println(System.getProperty("java.library.path"));
        Jchuck ck = new Jchuck();
        String[] files = {
            "beep.ck"
        };
        ck.spork(files);
        ck.run();
    }
}