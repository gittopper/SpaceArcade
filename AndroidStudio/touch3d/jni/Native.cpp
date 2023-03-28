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

#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "renderer.h"
#include <utils.h>
#include <solver.h>
#include <pieceshower.h>
#include <thread>

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
GLfloat normals[] = { 1.0f,  1.0f, -1.0f, /* Back. */
                      -1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f, -1.0f,
                      0.0f,  0.0f, -1.0f,
                      -1.0f,  1.0f,  1.0f, /* Front. */
                      1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f,  1.0f,
                      0.0f,  0.0f,  1.0f,
                      -1.0f,  1.0f, -1.0f, /* Left. */
                      -1.0f,  1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      -1.0f, -1.0f,  1.0f,
                      -1.0f,  0.0f,  0.0f,
                      1.0f,  1.0f,  1.0f, /* Right. */
                      1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f,  0.0f,  0.0f,
                      -1.0f, -1.0f,  1.0f, /* Bottom. */
                      1.0f, -1.0f,  1.0f,
                      -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      0.0f, -1.0f,  0.0f,
                      -1.0f,  1.0f, -1.0f, /* Top. */
                      1.0f,  1.0f, -1.0f,
                      -1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      0.0f,  1.0f,  0.0f
};
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

Renderer renderer;
namespace
{
    void solve(Geometry::VolumePuzzle* puzzle)
    {
        Geometry::Solver solver(*puzzle);
        solver.solve();
    }
}
Geometry::VolumePuzzle puzzle(3, 4, 2, generateWoodPuzzles());
std::thread st(solve, &puzzle);
std::vector<Geometry::Vector> colors;
int found_solutions = 0;

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_init(
        JNIEnv * env, jobject obj, jint width, jint height)
{

    renderer.setup();
    renderer.setSize(width, height);
}

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_step(
        JNIEnv * env, jobject obj)
{
    renderer.startFrame();
    //renderer.render(cubeVertices, normals, colour, indices, 36);

    Geometry::PiecesSet sol;
    int ns = puzzle.numFoundSolutions();
    if (ns > found_solutions)
    {
        __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "found solution %d", ns);
        found_solutions = ns;
    }
    puzzle.getSolution(sol, ns);
    sol.shift(Geometry::Vector(-5 / 2., -6 / 2., -4 / 2.));

    Geometry::Vector cm;
    for (int i = 0; i < sol.pieces.size(); i++)
    {
        cm += sol.pieces[i].getZero();
    }
    cm = cm * (1.f / sol.pieces.size());
    Visualization::PieceDrawer partDrawer;
    for (int i = 0; i < sol.pieces.size(); i++)
    {
        Geometry::Piece p = sol.pieces[i];
        if (colors.size() <= i)
        {
            colors.push_back(Geometry::Vector((rand() % 256) / 256.f, (rand() % 256) / 256.f, (rand() % 256) / 256.f));
        }

        //glColor3f(colors[i][0], colors[i][1], colors[i][2]);
        p.shift(-cm + (sol.pieces[i].getZero() - cm) * 0.2f);
        partDrawer.draw(renderer, p, colors[i]);
    }


}

float lstart;

float move_start_x;
float move_start_y;

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_dragStart(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2)
{
    lstart = std::sqrt((x2 - x1) * (x2 - x1)+ (y2 - y1) * (y2 - y1));
    move_start_x = (x1 + x2) * 0.5;
    move_start_y = (y1 + y2) * 0.5;
}

JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_dragStop(
        JNIEnv * env, jobject obj)
{
    renderer.camera().store();
}
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_drag(
        JNIEnv * env, jobject obj, jint x1, jint y1, jint x2, jint y2)
{
    float l = std::sqrt((x2 - x1) * (x2 - x1)+ (y2 - y1) * (y2 - y1));
    renderer.camera().zoom((l - lstart) / 100);
    float x = (x1 + x2) * 0.5;
    float y = (y1 + y2) * 0.5;
    renderer.camera().setShift((x - move_start_x) / 100, (move_start_y - y) / 100);
}


JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_moveStart(
        JNIEnv * env, jobject obj, jint x, jint y) {
    move_start_x = x;
    move_start_y = y;
}
JNIEXPORT void JNICALL Java_com_arm_malideveloper_openglessdk_simplecube_NativeLibrary_move(
        JNIEnv * env, jobject obj, jint x, jint y) {
    renderer.camera().setAngles((y - move_start_y) / 10,(x - move_start_x) / 10);
}
