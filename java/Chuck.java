// package edu.princeton.cs.chuck;

public class Chuck {
    static {
        System.loadLibrary("chuck");
    }

    public native int JNIVersion();

    public static void main(String[] args) {
        Chuck chuck = new Chuck();
        System.out.println("JNI Version = " + chuck.JNIVersion());
    }
}