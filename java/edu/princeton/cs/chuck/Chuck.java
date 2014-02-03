package edu.princeton.cs.chuck;

public class Chuck {
    static {
        System.loadLibrary("jchuck");
        initialize();
    }

    private native static void initialize();

    /**
     * Spork some chuck files.
     */
    public native boolean spork(String[] files);

    /**
     * Run the chuck vm in a separate thread.
     */
    public native boolean run();
}