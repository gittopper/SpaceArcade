package com.example.arcadegame;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.example.arcadegame.GameEngine;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import android.view.View;
import android.content.res.AssetManager;

public class ArcadeView extends GLSurfaceView {

	private static AssetManager assetManager;
	
	public ArcadeView(Context context) {
        super(context);
        assetManager = context.getAssets();
        setEGLContextClientVersion(2);
        super.setEGLConfigChooser(8 , 8, 8, 8, 16, 4);
        setRenderer(new Renderer());
        
	};
	
    float mPreviousX;
    float mPreviousY;
    
	public boolean onTouchEvent(final MotionEvent e) {
	    float x = e.getX();
	    float y = e.getY();
        switch(e.getAction())
        {
            case MotionEvent.ACTION_DOWN:
            	GameEngine.actionDown(x, y);
                mPreviousX = x;
                mPreviousY = y;
            break;
            case MotionEvent.ACTION_MOVE:
                float dx = x - mPreviousX;
                float dy = y - mPreviousY;
            	GameEngine.actionMove(dx, dy);
            break;
            case MotionEvent.ACTION_UP:
            	GameEngine.actionUp(x, y);
            break;
        }
       
        return true;
    }
	private static class Renderer implements GLSurfaceView.Renderer{
		public void onSurfaceCreated(GL10 unused, EGLConfig config) {
	    }

	    public void onDrawFrame(GL10 unused) {
	    	GameEngine.step();
	    }

	    public void onSurfaceChanged(GL10 unused, int width, int height) {
	    	GameEngine.init(width, height, assetManager);
	    }
	}
}
