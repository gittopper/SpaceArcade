#pragma once

#include <Matrix.h>

class Camera{
public:
    Camera();
    void setup(int width, int height);

    void setAngles(float ax, float ay);

    void setShift(float sx, float sy);

    void zoom(int shift);

    void store();

    void render();

    float projectionMatrix[16];
    float modelViewMatrix[16];
private:
    float modelViewMatrixLast[16];
    float angleX = 0;
    float angleY = 0;
    float zLast = -10;
    float z = zLast;
    float shift_x_last = 0;
    float shift_y_last = 0;
    float shift_x = 0;
    float shift_y = 0;
};
