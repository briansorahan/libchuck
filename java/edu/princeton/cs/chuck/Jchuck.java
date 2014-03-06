package edu.princeton.cs.chuck;

public class Jchuck {
    private long nativeHandle;

    private Jchuck() {}

    static {
        NativeLoader.loadLibrary("jchuck");
    }

    public static synchronized Jchuck start() {
        Jchuck instance = new Jchuck();
        // initialize the native pointer
        instance.initialize();
        return instance;
    }
    
    /**
     * Initialize and return a pointer to chuck
     */
    private native synchronized void initialize();

    /**
     * Spork some chuck files and run them in a new thread.
     */
    public native synchronized boolean spork(String[] files);

    /**
     * Wait for the chuck vm thread.
     */
    public native synchronized boolean run();

    /**
     * Send a long int to chuck.
     */
    public native synchronized void sendTo(String channel, long val);

    /**
     * Send a double to chuck.
     */
    public native synchronized void sendTo(String channel, double val);

    /**
     * Send a string to chuck.
     */
    public native synchronized void sendTo(String channel, String val);

    /**
     * Receive a long int from chuck.
     */
    public native synchronized void receiveFrom(String channel, IntReceiver rec);

    /**
     * Receive a double from chuck.
     */
    public native synchronized void receiveFrom(String channel, FloatReceiver rec);

    /**
     * Receive a string from chuck.
     */
    public native synchronized void receiveFrom(String channel, StringReceiver rec);
}

