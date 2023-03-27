#pragma once

#include "base.h"

namespace Geometry
{
enum RotType
{
    None,
    RotateX,
    RotateY,
    RotateZ
};

class Vector
{
public:
    Vector(float i = 0, float j = 0, float k = 0);

    Vector cross(const Vector v);

    Vector& rotate(RotType rotation);

    const float& operator[](int i) const
    {
        return vec[i];
    }

    float& operator[](int i)
    {
        return vec[i];
    }

    Vector operator*(float f) const;

    Vector operator-(const Vector& v) const;

    bool operator==(const Vector& v) const;

    Vector operator-() const;

    Vector operator+(const Vector& v) const;

    Vector operator+=(const Vector& v);

    Vector normalized() const;
    Vector ortogonal(Vector v) const;
    float len() const;
private:
    float vec[3];
};


extern const Vector XSHIFT, YSHIFT, ZSHIFT;

float dot(const Vector& v1, const Vector& v2);

Vector operator*(float f, Vector& v);
}
