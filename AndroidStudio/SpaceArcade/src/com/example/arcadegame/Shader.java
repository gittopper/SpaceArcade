package com.example.arcadegame;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import android.content.Context;
import android.opengl.GLES20;
import android.util.Log;

public class Shader {

    public static final String TAG = Shader.class.getSimpleName();
    int program;
    int vertexShader;
    int fragmentShader;

    String vShaderSource;
    String fShaderSource;

    public Shader(String vs_source, String fs_source) {
        this.vShaderSource = vs_source;
        this.fShaderSource = fs_source;

        createProgram();
    }

    private void createProgram() {

        program = GLES20.glCreateProgram();
        if (program != 0) {
            vertexShader = createShader(GLES20.GL_VERTEX_SHADER, vShaderSource);
            fragmentShader = createShader(GLES20.GL_FRAGMENT_SHADER, fShaderSource);

            GLES20.glAttachShader(program, vertexShader);
            GLES20.glAttachShader(program, fragmentShader);
            GLES20.glLinkProgram(program);
            final int[] linkStatus = new int[1];
            GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linkStatus, 0);
            if (linkStatus[0] == 0) {
                GLES20.glDeleteProgram(program);
                program= 0;
            }
        } else {
            Log.e(TAG, "Couldn't create program.");
        }


    }

    private int createShader(int type, String source) {
        int shader = GLES20.glCreateShader(type);
        if (shader != 0) {
            GLES20.glShaderSource(shader, source);
            GLES20.glCompileShader(shader);
            final int[] compileStatus = new int[1];
            GLES20.glGetShaderiv(shader, GLES20.GL_COMPILE_STATUS, compileStatus, 0);
            if (compileStatus[0] == 0) {
                GLES20.glDeleteShader(shader);
                shader=0;
            }
        }

        return shader;
    }

    public int getProgram() {
        return program;
    }
}