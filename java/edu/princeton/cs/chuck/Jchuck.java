package edu.princeton.cs.chuck;

public class Jchuck {
    private long nativeHandle;

    private Jchuck(long handle) {
        nativeHandle = handle;
    }

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