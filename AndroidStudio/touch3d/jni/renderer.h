#pragma once

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/log.h>
#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#include "camera.h"

class Renderer {
public:
    void setup();
    void setSize(int width, int height);
    void startFrame();
    Camera& camera() { return camera_;}
    void render(GLfloat* vertices, GLfloat*normals, GLfloat* colors, GLushort* indices, int size);
private:
    GLuint loadShader(GLenum shaderType, const char* shaderSource);
    GLuint createProgram(const char* vertexSource, const char * fragmentSource);

    GLuint simpleCubeProgram;
    GLuint vertexLocation;
    GLuint vertexColourLocation;
    GLuint projectionLocation;
    GLuint vertexNormalLocation;
    GLuint modelViewLocation;
    Camera camera_;
};