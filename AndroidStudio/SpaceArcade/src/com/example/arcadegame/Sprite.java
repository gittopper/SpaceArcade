package com.example.arcadegame;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.opengles.GL10;

import android.graphics.Bitmap;
import android.opengl.GLES20;
import android.opengl.GLUtils;

public class Sprite {
    final private int textureLoc;
    final private int vertexLoc;
    final private int matLoc;
    final private int[] textureIds = new int[1];

    private float[] mProjectionMatrix = new float[16];
    private FloatBuffer vertexBuffer;
    private FloatBuffer textureBuffer;
    int program;

    public Sprite(int prg_id){
        program = prg_id;
        vertexLoc = GLES20.glGetAttribLocation(program, "a_Position");
        textureLoc = GLES20.glGetAttribLocation(program, "a_Texture"); //texture
        matLoc = GLES20.glGetUniformLocation(program, "u_mvpMatrix"); //texture
    }
    void setOrtho(float left, float right, float bottom, float top, float near, float far)
    {
        float tx = - (right + left)/(right - left);
        float ty = - (top + bottom)/(top - bottom);
        float tz = - (far + near)/(far - near);

        mProjectionMatrix[0] = 2.0f/(right-left);
        mProjectionMatrix[1] = 0;
        mProjectionMatrix[2] = 0;
        mProjectionMatrix[3] = tx;

        mProjectionMatrix[4] = 0;
        mProjectionMatrix[5] = 2.0f/(top-bottom);
        mProjectionMatrix[6] = 0;
        mProjectionMatrix[7] = ty;

        mProjectionMatrix[8] = 0;
        mProjectionMatrix[9] = 0;
        mProjectionMatrix[10] = -2.0f/(far-near);
        mProjectionMatrix[11] = tz;

        mProjectionMatrix[12] = 0;
        mProjectionMatrix[13] = 0;
        mProjectionMatrix[14] = 0;
        mProjectionMatrix[15] = 1;
    }
    public void setAspectRatio(float w, float h) {
        float scale = 10;
        float aspect = (float)h / w;
        float hs = scale / 2;
        setOrtho(-hs, hs, -aspect * hs, aspect * hs, -scale, scale);
        float pano_x = scale;
        float pano_y = aspect * scale;
        float vertices[] = {
                -pano_x/2.f, pano_y / 2.f, 0.f,
                -pano_x/2.f, -pano_y / 2.f,0.f,
                pano_x/2.f, pano_y / 2.f,0.f,
                pano_x/2.f, -pano_y / 2.f,0.f,
        };

        float texture[] = {
                0.0f, 0.0f,
                0.0f, 1.0f,
                1.0f, 0.0f,
                1.0f, 1.0f
        };

        ByteBuffer vbb = ByteBuffer.allocateDirect(vertices.length * 4);
        vbb.order(ByteOrder.nativeOrder());
        vertexBuffer = vbb.asFloatBuffer();
        vertexBuffer.put(vertices);
        vertexBuffer.position(0);


        ByteBuffer tbb = ByteBuffer.allocateDirect(texture.length * 4);
        tbb.order(ByteOrder.nativeOrder());
        textureBuffer = tbb.asFloatBuffer();
        textureBuffer.put(texture);
        textureBuffer.position(0);
    }

    public void loadGLTexture(Bitmap bitmap) {

        GLES20.glDeleteTextures(1, textureIds, 0);
        GLES20.glGenTextures(1, textureIds, 0);
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureIds[0]);

        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_REPEAT);

//        byte[] buffer = new byte[bitmap.getWidth() * bitmap.getHeight() * 4];
//        for (int y = 0; y < bitmap.getHeight(); y++){
//            for (int x = 0; x < bitmap.getWidth(); x++) {
//                int pixel = bitmap.getPixel(x, y);
//                buffer[(y * bitmap.getWidth() + x) * 4 + 0] = (byte) ((pixel >> 16) & 0xFF);
//                buffer[(y * bitmap.getWidth() + x) * 4 + 1] = (byte) ((pixel >> 8) & 0xFF);
//                buffer[(y * bitmap.getWidth() + x) * 4 + 2] = (byte) ((pixel >> 0) & 0xFF);
//                buffer[(y * bitmap.getWidth() + x) * 4 + 3] = (byte) ((pixel >> 24) & 0xFF);
//            }
//        }
//        ByteBuffer byteBuffer = ByteBuffer.allocateDirect(bitmap.getWidth() * bitmap.getHeight() * 4);
//        byteBuffer.put(buffer).position(0);
//        GLES20.glTexImage2D ( GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA, bitmap.getWidth(), bitmap.getHeight(), 0,
//                GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, byteBuffer );
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA, bitmap, 0);
        bitmap.recycle();
        GLES20.glBindTexture( GLES20.GL_TEXTURE_2D, 0);

    }

    public void draw() {
// отключаем отсечение невидимых граней

        GLES20.glUseProgram(program);
        GLES20.glVertexAttribPointer(vertexLoc, 3, GLES20.GL_FLOAT, false, 0, vertexBuffer);
        GLES20.glEnableVertexAttribArray(vertexLoc);

        GLES20.glVertexAttribPointer(textureLoc, 2, GLES20.GL_FLOAT, false, 0, textureBuffer);
        GLES20.glEnableVertexAttribArray(textureLoc);

        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureIds[0]);

        GLES20.glEnable(GL10.GL_TEXTURE_2D);
        GLES20.glEnable(GL10.GL_BLEND);
        GLES20.glBlendFunc(GL10.GL_SRC_ALPHA, GL10.GL_ONE_MINUS_SRC_ALPHA);
        GLES20.glUniformMatrix4fv(matLoc, 1, false, mProjectionMatrix, 0);
        GLES20.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);
        GLES20.glDisable(GL10.GL_BLEND);
    }
}