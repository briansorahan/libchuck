package edu.princeton.cs.chuck;

public class Chuck {
    public Chuck() {
    }

    static {
        System.loadLibrary("jchuck");
    }

    /**
     * Spork some chuck files.
     */
    public native boolean spork(String[] files);

    /**
     * Run the chuck vm in a separate thread.
     */
    public native boolean run();
}