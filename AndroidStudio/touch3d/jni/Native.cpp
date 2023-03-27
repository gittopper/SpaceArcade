/* Copyright (c) 2013-2017, ARM Limited and Contributors
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge,
 * to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "Matrix.h"

#define LOG_TAG "libNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

/* [vertexShader] */
static const char  glVertexShader[] = R"(
    attribute vec4 vertexPosition;
    attribute vec3 vertexColour;
    varying vec3 fragColour;
    uniform mat4 projection;
    uniform mat4 modelView;
    void main()
    {
        gl_Position = projection * modelView * vertexPosition;
        fragColour = vertexColour;
    }
)";
/* [vertexShader] */

/* [fragmentShader] */
static const char  glFragmentShader[] = R"(
    precision mediump float;
    varying vec3 fragColour;
    void main()
    {
        gl_FragColor = vec4(fragColour, 1.0);
    }
)";
/* [fragmentShader] */

GLuint loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (compiled != GL_TRUE)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen > 0)
            {
                char * logBuffer = (char*) malloc(infoLen);

                if (logBuffer != NULL)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, logBuffer);
                    LOGE("Could not Compile Shader %d:\n%s, shaderType, logBuffer\n");
                    free(logBuffer);
                    logBuffer = NULL;
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint createProgram(const char* vertexSource, const char * fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (vertexShader == 0)
    {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (fragmentShader == 0)
    {
        return 0;
    }

    GLuint program = glCreateProgram();

    if (program != 0)
    {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if(linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength > 0)
            {
                char* logBuffer = (char*) malloc(bufLength);

                if (logBuffer != NULL)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, logBuffer);
                    LOGE("Could not link program:\n%s, logBuffer\n");
                    free(logBuffer);
                    logBuffer = NULL;
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint simpleCubeProgram;
GLuint vertexLocation;
GLuint vertexColourLocation;
GLuint projectionLocation;
GLuint modelViewLocation;

void initByMatrix(float* m1, float* m2)
{
    for(int i = 0; i < 16; i++)
    {
        m1[i] = m2[i];
    }
}

float projectionMatrix[16];
float modelViewMatrix[16];
float modelViewMatrixLast[16];
float angleX = 0;
float angleY = 0;
float zLast = -10;
float z = zLast;
float shift_x = 0;
float shift_y = 0;

/* [setupGraphics] */
bool setupGraphics(int width, int height)
{
    simpleCubeProgram = createProgram(glVertexShader, glFragmentShader);

    if (simpleCubeProgram == 0)
    {
        LOGE ("Could not create program");
        return false;
    }

    vertexLocation = glGetAttribLocation(simpleCubeProgram, "vertexPosition");
    vertexColourLocation = glGetAttribLocation(simpleCubeProgram, "vertexColour");
    projectionLocation = glGetUniformLocation(simpleCubeProgram, "projection");
    modelViewLocation = glGetUniformLocation(simpleCubeProgram, "modelView");

    /* Setup the perspective */
    matrixPerspective(projectionMatrix, 45, (float)width / (float)height, 0.1f, 100);
    matrixIdentityFunction(modelViewMatrixLast);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width, height);

    return true;
}
/* [setupGraphics] */

/* [cubeVertices] */
GLfloat cubeVertices[] = {-1.0f,  1.0f, -1.0f, /* Back. */
                           1.0f,  1.0f, -1.0f,
                          -1.0f, -1.0f, -1.0f,
                           1.0f, -1.0f, -1.0f,
                          -1.0f,  1.0f,  1.0f, /* Front. */
                           1.0f,  1.0f,  1.0f,
                          -1.0f, -1.0f,  1.0f,
                           1.0f, -1.0f,  1.0f,
                          -1.0f,  1.0f, -1.0f, /* Left. */
                          -1.0f, -1.0f, -1.0f,
                          -1.0f, -1.0f,  1.0f,
                          -1.0f,  1.0f,  1.0f,
                           1.0f,  1.0f, -1.0f, /* Right. */
                           1.0f, -1.0f, -1.0f,
                           1.0f, -1.0f,  1.0f,
                           1.0f,  1.0f,  1.0f,
                          -1.0f, -1.0f, -1.0f, /* Top. */
                          -1.0f, -1.0f,  1.0f,
                           1.0f, -1.0f,  1.0f,
                           1.0f, -1.0f, -1.0f,
                          -1.0f,  1.0f, -1.0f, /* Bottom. */
                          -1.0f,  1.0f,  1.0f,
                           1.0f,  1.0f,  1.0f,
                           1.0f,  1.0f, -1.0f
                         };
/* [cubeVertices] */
/* [colourComponents] */
GLfloat colour[] = {1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    1.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    0.0f, 0.0f, 1.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    1.0f, 1.0f, 0.0f,
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    0.0f, 1.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f,
                    1.0f, 0.0f, 1.0f
                   };
/* [colourComponents] */

/* [indices] */
GLushort indices[] = {0, 2, 3, 0, 1, 3, 4, 6, 7, 4, 5, 7, 8, 9, 10, 11, 8, 10, 12, 13, 14, 15, 12, 14, 16, 17, 18, 16, 19, 18, 20, 21, 22, 20, 23, 22};
/* [indices] */

/* [renderFrame] */
void renderFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    initByMatrix(modelViewMatrix, modelViewMatrixLast);
    //matrixIdentityFunction(modelViewMatrix);

    matrixRotateX(modelViewMatrix, angleX);
    matrixRotateY(modelViewMatrix, angleY);

    matrixTranslate(modelViewMatrix, shift_x, shift_y, z);

    glUseProgram(simpleCubeProgram);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices);
    glEnableVertexAttribArray(vertexLocation);
    glVertexAttribPointer(vertexColourLocation, 3, GL_FLOAT, GL_FALSE, 0, colour);
    glEnableVertexAttribArray(vertexColourLocation);

    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projectionMatrix);
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, modelViewMatrix);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, indices);
}
/* [renderFrame] */
extern "C"
{
    JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_init(
            JNIEnv * env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_dragStart(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2);
    JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_drag(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2);
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_dragStop(
        JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_step(
            JNIEnv * env, jobject obj);
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_moveStart(
        JNIEnv * env, jobject obj, jint x, jint y);
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_move(
        JNIEnv * env, jobject obj, jint x, jint y);
};

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_init(
        JNIEnv * env, jobject obj, jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_step(
        JNIEnv * env, jobject obj)
{
    renderFrame();
}

float lstart;

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_dragStart(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2)
{
    lstart = std::sqrt((x2 - x1) * (x2 - x1)+ (y2 - y1) * (y2 - y1));
}

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_dragStop(
        JNIEnv * env, jobject obj)
{
    zLast = z;
    angleX = 0;
    angleY = 0;
    initByMatrix(modelViewMatrixLast, modelViewMatrix);
    modelViewMatrixLast[12] = 0;
    modelViewMatrixLast[13] = 0;
    modelViewMatrixLast[14] = 0;
}
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_drag(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2)
{
    auto l = std::sqrt((x2 - x1) * (x2 - x1)+ (y2 - y1) * (y2 - y1));
    z = zLast + (l - lstart) / 100;
}

int move_start_x;
int move_start_y;

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_moveStart(
        JNIEnv * env, jobject obj, jint x, jint y) {
    move_start_x = x;
    move_start_y = y;
}
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_move(
        JNIEnv * env, jobject obj, jint x, jint y) {
    angleX = (y - move_start_y) / 10;
    angleY = (x - move_start_x) / 10;
}
