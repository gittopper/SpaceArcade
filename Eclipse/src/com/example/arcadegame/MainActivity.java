package com.example.arcadegame;

import android.app.ActionBar;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.PixelFormat;
import android.os.Bundle;
import android.app.Activity;
import android.view.KeyEvent;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.RelativeLayout;

import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends Activity {

	ArcadeView arcadeView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
       super.onCreate(savedInstanceState);
       arcadeView = new ArcadeView(getApplication());
        //setContentView(arcadeView);
        setContentView(R.layout.activity_main);
        RelativeLayout layout = (RelativeLayout) findViewById(R.id.root);
        RelativeLayout.LayoutParams game_view = new RelativeLayout.LayoutParams(
                RelativeLayout.LayoutParams.MATCH_PARENT,
                RelativeLayout.LayoutParams.MATCH_PARENT);
        layout.addView(arcadeView, 0, game_view);

        ImageView image_view = (ImageView) findViewById(R.id.image_overlay);
        InputStream is = null;
        try {
            is = getAssets().open("daco2.png");
            BitmapFactory.Options opts = new BitmapFactory.Options();
            opts.inPreferredConfig = Bitmap.Config.ARGB_8888;
            Bitmap bitmap = BitmapFactory.decodeStream(is, null, opts);
            image_view.setImageBitmap(bitmap);
            image_view.setAlpha(0.5f);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        arcadeView.onPause();
    }
    

    @Override
    protected void onResume() {
        super.onResume();
        arcadeView.onResume();
    }
    
    @Override
    protected void onStop() {
        super.onStop();
        finish();
    }
    
    @Override
    protected void onDestroy(){	
    	super.onDestroy();
    }

    public boolean onKeyDown(int keyCode, KeyEvent event) {
	        if (keyCode == KeyEvent.KEYCODE_BACK) {
	        		finish();
	                return true;
	        }
	    return super.onKeyDown(keyCode, event);
	}
}
