package com.example.arcadegame;

import android.content.res.AssetManager;

public class GameEngine {

	static{
		System.loadLibrary("GameEngine");
	}
	public static native void init(int width, int height, AssetManager assetManager);
	public static native void step();
	
	public static native void tap(float x, float y);
	public static native void actionUp(float x, float y);
	public static native void actionDown(float x, float y);
	public static native void actionMove(float x, float y);
	public static native boolean stop();
	
	public static native void free();
}
