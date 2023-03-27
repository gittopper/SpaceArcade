#include "mat.h"

namespace Geometry
{
Mat::Mat(Vector v1, Vector v2, Vector v3)
{
    getVolPart(0, 0) = v1[0];
    getVolPart(1, 0) = v1[1];
    getVolPart(2, 0) = v1[2];

    getVolPart(0, 1) = v2[0];
    getVolPart(1, 1) = v2[1];
    getVolPart(2, 1) = v2[2];

    getVolPart(0, 2) = v3[0];
    getVolPart(1, 2) = v3[1];
    getVolPart(2, 2) = v3[2];
}
Mat::Mat(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22)
{
    getVolPart(0, 0) = a00;
    getVolPart(0, 1) = a01;
    getVolPart(0, 2) = a02;

    getVolPart(1, 0) = a10;
    getVolPart(1, 1) = a11;
    getVolPart(1, 2) = a12;

    getVolPart(2, 0) = a20;
    getVolPart(2, 1) = a21;
    getVolPart(2, 2) = a22;
}
float Mat::det()const
{
    return getVolPart(0, 0) * getVolPart(1, 1) * getVolPart(2, 2) + getVolPart(1, 0) * getVolPart(2, 1) * getVolPart(0, 2) + getVolPart(0, 1) * getVolPart(1, 2) * getVolPart(2, 0) - getVolPart(2, 0) * getVolPart(1, 1) * getVolPart(0, 2) - getVolPart(1, 0) * getVolPart(0, 1) * getVolPart(2, 2) - getVolPart(2, 1) * getVolPart(1, 2) * getVolPart(0, 0);
}
void Mat::scale(float val)
{
    for (int i = 0; i < 9; i++)
    {
        float r = ar[i] * val;
        ar[i] = r;
        //BREAK_ON_LINE(ar[i] == r);
    }
}
Mat Mat::inverse() const
{
    Mat inv;
    inv.getVolPart(0, 0) = (getVolPart(1, 1) * getVolPart(2, 2) - getVolPart(1, 2) * getVolPart(2, 1));
    inv.getVolPart(0, 1) = (getVolPart(0, 2) * getVolPart(2, 1) - getVolPart(0, 1) * getVolPart(2, 2));
    inv.getVolPart(0, 2) = (getVolPart(0, 1) * getVolPart(1, 2) - getVolPart(0, 2) * getVolPart(1, 1));

    inv.getVolPart(1, 0) = (getVolPart(1, 2) * getVolPart(2, 0) - getVolPart(1, 0) * getVolPart(2, 2));
    inv.getVolPart(1, 1) = (getVolPart(0, 0) * getVolPart(2, 2) - getVolPart(0, 2) * getVolPart(2, 0));
    inv.getVolPart(1, 2) = (getVolPart(0, 2) * getVolPart(1, 0) - getVolPart(0, 0) * getVolPart(1, 2));

    inv.getVolPart(2, 0) = (getVolPart(1, 0) * getVolPart(2, 1) - getVolPart(1, 1) * getVolPart(2, 0));
    inv.getVolPart(2, 1) = (getVolPart(0, 1) * getVolPart(2, 0) - getVolPart(0, 0) * getVolPart(2, 1));
    inv.getVolPart(2, 2) = (getVolPart(0, 0) * getVolPart(1, 1) - getVolPart(0, 1) * getVolPart(1, 0));
    inv.scale(1. / det());
    return inv;
}
bool Mat::operator == (const Mat& m) const
{
    for (int i = 0; i < 9; i++)
    {
        if (ar[i] != m.ar[i]) return false;
    }
    return true;
}
Mat Mat::operator * (const Mat& m) const
{
    Mat n;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            n.getVolPart(i, j) = getVolPart(i, 0) * m.getVolPart(0, j) + getVolPart(i, 1) * m.getVolPart(1, j) + getVolPart(i, 2) * m.getVolPart(2, j);
        }
    }
    return n;
}

Mat Mat::operator + (const Mat& m) const
{
    Mat n;
    for (int i = 0; i < 9; i++)
    {
        n.ar[i] = ar[i] + m.ar[i];
    }
    return n;
}

Vector Mat::operator * (const Vector& v) const
{
    Vector o;
    o[0] = getVolPart(0, 0) * v[0] + getVolPart(0, 1) * v[1] + getVolPart(0, 2) * v[2];
    o[1] = getVolPart(1, 0) * v[0] + getVolPart(1, 1) * v[1] + getVolPart(1, 2) * v[2];
    o[2] = getVolPart(2, 0) * v[0] + getVolPart(2, 1) * v[1] + getVolPart(2, 2) * v[2];
    return o;
}

Mat Mat::operator * (float f) const
{
    Mat res(*this);
    for (int i = 0; i < 9; i++)
    {
        res.ar[i] = res.ar[i] * f;
    }
    return res;
}
Mat Mat::getRotated(Vector v, float angle)
{
    Vector norm = v.normalized();
    Mat w(0, -norm[2], norm[1],         norm[2], 0, -norm[0],                    -norm[1], norm[0], 0);
    //Rodrigues' Rotation Formula
    Mat res = Mat() + w * sin(angle) + w * w * 2 * sin(angle / 2);
    return res;
}
}
