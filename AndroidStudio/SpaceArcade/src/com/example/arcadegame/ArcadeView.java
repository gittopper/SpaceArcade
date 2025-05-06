package com.example.arcadegame;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.graphics.BitmapFactory;
import android.graphics.BitmapFactory.Options;
import android.graphics.Bitmap;
import android.graphics.PixelFormat;

import android.opengl.GLES10;
import android.opengl.GLES20;
import com.example.arcadegame.GameEngine;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import android.view.View;
import android.content.res.AssetManager;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class ArcadeView extends GLSurfaceView {

	private static AssetManager assetManager;

	public ArcadeView(Context context) {
        super(context);
        assetManager = context.getAssets();
        Sound.loadSounds(assetManager);
        setEGLContextClientVersion(2);
        super.setEGLConfigChooser(8 , 8, 8, 8, 16, 0);
        setRenderer(new Renderer(this));
        getHolder().setFormat(PixelFormat.RGBA_8888);
	};
	
    float mPreviousX;
    float mPreviousY;

    public void step() {
        GameEngine.step();
    }

	public boolean onTouchEvent(final MotionEvent e) {
        if (e.getPointerCount() > 1)
        {
            int itemPointerId0 = e.getPointerId(0);
            int pointerIndex0 = e.findPointerIndex(itemPointerId0);
            MotionEvent.PointerCoords pc0 = new MotionEvent.PointerCoords();
            e.getPointerCoords(pointerIndex0, pc0);

            int itemPointerId1 = e.getPointerId(1);
            int pointerIndex1 = e.findPointerIndex(itemPointerId1);
            MotionEvent.PointerCoords pc1 = new MotionEvent.PointerCoords();
            e.getPointerCoords(pointerIndex1, pc1);
            switch(e.getAction())
            {
                case MotionEvent.ACTION_DOWN:
                case MotionEvent.ACTION_POINTER_2_DOWN:
                    GameEngine.dragStart((int)pc0.x, (int)pc0.y, (int)pc1.x, (int)pc1.y);
                    break;
                case MotionEvent.ACTION_MOVE:
                    GameEngine.drag((int)pc0.x, (int)pc0.y, (int)pc1.x, (int)pc1.y);
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_POINTER_2_UP:
                    GameEngine.dragStop();
                    break;
            }
        }else if (e.getPointerCount() == 1){
            float x = e.getX();
            float y = e.getY();
            switch (e.getAction()) {
                case MotionEvent.ACTION_DOWN:
                    //Sound.play("shoot.ogg");
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
        }
        return true;
    }

    @Override
    public void onPause() {
        super.onPause();
        GameEngine.onPause();
    }


    @Override
    public void onResume() {
        super.onResume();
        GameEngine.onResume();
    }
	private static class Renderer implements GLSurfaceView.Renderer{
        Sprite sprite;

        ArcadeView arcade_view;
        Renderer(ArcadeView aview) {
            arcade_view = aview;
        }
		public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            String sprite_vs = readData("sprite_vs.txt");
            String sprite_fs = readData("sprite_fs.txt");
            Shader shader = new Shader(sprite_vs, sprite_fs);
            int program = shader.getProgram();
            sprite = new Sprite(program);
            try {
                InputStream is = assetManager.open("daco.png");
                BitmapFactory.Options opts = new BitmapFactory.Options();
                opts.inPreferredConfig = Bitmap.Config.ARGB_8888;
                Bitmap bitmap = BitmapFactory.decodeStream(is, null, opts);
                sprite.loadGLTexture(bitmap);
            } catch(IOException e) {
                throw new RuntimeException("cannot load sprite");
            }
	    }
        public String readData(String filename) {
            StringBuffer vs = new StringBuffer();
            try {
                InputStream is = assetManager.open(filename);
                BufferedReader in = new BufferedReader(new InputStreamReader(is));
                String read = in.readLine();
                while (read != null) {
                    vs.append(read + "\n");
                    read = in.readLine();
                }
                vs.deleteCharAt(vs.length() - 1);
            } catch(IOException e) {
            }
            return vs.toString();
        }
	    public void onDrawFrame(GL10 unused) {
            arcade_view.step();
            //sprite.draw();
            GameEngine.showFrame();
	    }

	    public void onSurfaceChanged(GL10 unused, int width, int height) {
            GameEngine.init(width, height, assetManager);
            sprite.setAspectRatio(width, height);
	    }
	}
}
