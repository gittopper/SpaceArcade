//
//  vector.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#include "vector.h"
#include <cmath>

namespace Math
{
    Vector::Vector(float x, float y, float z)
    {
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }

    Vector Vector::operator-(const Vector& v) const
    {
        return Vector(vec[0] - v[0], vec[1] - v[1], vec[2] - v[2]);
    }
    bool Vector::operator==(const Vector& v) const
    {
        return fabs(dot(*this, v)) < FLOAT_EPS;
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
        float d = 1/len();
        Vector res = *this;
        return res * d;
    }
    
    Vector Vector::ortogonal(const Vector& v) const
    {
        return *this - v * (dot(*this, v) / v.len());
    }
    
    float Vector::len() const
    {
        return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
    }


    inline Vector cross(const Vector& v1, const Vector& v2)
    {
        Vector r;
        r[0] = v1[1] * v2[2] - v1[2] * v2[1];
        r[1] = v1[2] * v2[0] - v1[0] * v2[2];
        r[2] = v1[0] * v2[1] - v1[1] * v2[0];
        return r;
    }
    
    inline float dot(const Vector& v1, const Vector& v2)
    {
        return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
    }
    Vector centerMass(const VArray& p)
    {
        Vector cm;
        for(VArray::const_iterator it = p.begin(); it != p.end(); it++)
        {
            cm += *it;
        }
        cm = cm *(1./p.size());
        return cm;
    }
    void centralize(VArray& p)
    {
        Vector cm = centerMass(p);
        for(VArray::iterator it = p.begin(); it != p.end(); it++)
        {
            *it = *it - cm;
        }
    }
    void scale(VArray& p, float scale)
    {
        for(VArray::iterator it = p.begin(); it != p.end(); it++)
        {
            *it = scale * (*it);
        }
    }
    float maxRadius(VArray& p)
    {
        float r = 0;
        for(VArray::iterator it = p.begin(); it != p.end(); it++)
        {
            float len = it->len();
            if (len > r) r = len;
        }
        return r;
    }
}
