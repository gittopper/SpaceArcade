#include "vector.h"

namespace Geometry
{
float dot(const Vector& v1, const Vector& v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

Vector::Vector(float i, float j, float k)
{
    vec[0] = i;
    vec[1] = j;
    vec[2] = k;
}

Vector Vector::cross(const Vector v)
{
    Vector r;
    r[0] = vec[1] * v.vec[2] - vec[2] * v.vec[1];
    r[1] = vec[2] * v.vec[0] - vec[0] * v.vec[2];
    r[2] = vec[0] * v.vec[1] - vec[1] * v.vec[0];
    return r;
}
Vector& Vector::rotate(RotType rotation)
{
    float x = vec[0];
    float y = vec[1];
    float z = vec[2];

    switch (rotation)
    {
    case RotateX:
        vec[1] = z;
        vec[2] = -y;
        break;
    case RotateY:
        vec[0] = -z;
        vec[2] = x;
        break;
    case RotateZ:
        vec[0] = y;
        vec[1] = -x;
    };
    return *this;
}
Vector Vector::operator-(const Vector& v) const
{
    return Vector(vec[0] - v[0], vec[1] - v[1], vec[2] - v[2]);
}
bool Vector::operator==(const Vector& v) const
{
//    return vec[0] == v[0] && vec[1] == v[1] && vec[2] == v[2];
    return fabs(dot(*this, v) - v.len() * this->len()) < FLOAT_EPS;
}
Vector Vector::operator-() const
{
    return Vector(-vec[0], -vec[1], -vec[2]);
}
Vector Vector::operator+(const Vector& v) const
{
    return Vector(vec[0] + v[0], vec[1] + v[1], vec[2] + v[2]);
}
Vector Vector::operator+=(const Vector& v)
{
    vec[0] += v[0];
    vec[1] += v[1];
    vec[2] += v[2];
    return *this;
}

Vector Vector::operator*(float f) const
{
    Vector res = *this;
    res[0] = vec[0] * f;
    res[1] = vec[1] * f;
    res[2] = vec[2] * f;
    return res;
}

Vector Vector::normalized() const
{
    float d = 1 / len();
    Vector res = *this;
    return res * d;
}

Vector operator*(float f, Vector& v)
{
    return v * f;
}

Vector Vector::ortogonal(Vector v) const
{
    return *this - v * (dot(*this, v) / v.len());
}

float Vector::len() const
{
    return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

const Vector XSHIFT(1, 0, 0), YSHIFT(0, 1, 0), ZSHIFT(0, 0, 1);


}
