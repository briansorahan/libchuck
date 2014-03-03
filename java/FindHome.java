import java.io.File;

public class FindHome {
    public static void main(String[] args) {
        File home = new File(System.getProperty("java.home"));
        System.out.println(home.getParent());
    }
}