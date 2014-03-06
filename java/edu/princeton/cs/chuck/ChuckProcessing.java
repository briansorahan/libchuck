package edu.princeton.cs.chuck;

public class ChuckProcessing {
    private static ChuckProcessing INSTANCE = null;

    private ChuckProcessing() {}

    public static ChuckProcessing getInstance() {
        if (INSTANCE == null) {
            INSTANCE = new ChuckProcessing();
        }
        return INSTANCE;
    }
}