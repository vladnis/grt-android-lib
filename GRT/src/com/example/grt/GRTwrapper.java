package com.example.grt;

public class GRTwrapper {
	static {
		System.loadLibrary("grt");
		System.loadLibrary("GRTwrapper");
	}
	
	/**
	 * Ruleaza nativ teste pentru GRT.
	 */
	public native static void test();
	
}
