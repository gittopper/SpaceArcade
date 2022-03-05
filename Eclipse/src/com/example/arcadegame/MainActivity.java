package com.example.arcadegame;

import android.os.Bundle;
import android.app.Activity;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;

public class MainActivity extends Activity {

	ArcadeView arcadeView;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
       super.onCreate(savedInstanceState);
       arcadeView = new ArcadeView(getApplication());
       setContentView(arcadeView);   
    }

    @Override
    protected void onPause() {
        super.onPause();
    }
    

    @Override
    protected void onResume() {
        super.onResume();
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
