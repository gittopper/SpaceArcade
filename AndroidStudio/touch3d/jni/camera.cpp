#include <camera.h>

Camera::Camera(){
    matrixIdentityFunction(modelViewMatrixLast);
}

void Camera::setup(int width, int height)
{
    matrixPerspective(projectionMatrix, 45,
                      (float)width / (float)height, 0.1f, 100);
}

void Camera::setAngles(float ax, float ay)
{
    angleX = ax;
    angleY = ay;
}

void Camera::setShift(float sx, float sy)
{
    shift_x = shift_x_last + sx;
    shift_y = shift_y_last + sy;
}

void Camera::zoom(int shift)
{
    z = zLast + shift;
}

void Camera::store()
{
    zLast = z;
    angleX = 0;
    angleY = 0;
    shift_x_last = shift_x;
    shift_y_last = shift_y;
    initByMatrix(modelViewMatrixLast, modelViewMatrix);
    modelViewMatrixLast[12] = 0;
    modelViewMatrixLast[13] = 0;
    modelViewMatrixLast[14] = 0;
}

void Camera::render()
{
    initByMatrix(modelViewMatrix, modelViewMatrixLast);
    //matrixIdentityFunction(modelViewMatrix);
    matrixRotateX(modelViewMatrix, angleX);
    matrixRotateY(modelViewMatrix, angleY);
    matrixTranslate(modelViewMatrix, shift_x, shift_y, z);
}
