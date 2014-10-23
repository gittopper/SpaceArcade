//
//  vector.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//


#ifndef _Vector_h_
#define _Vector_h_

#include "common.h"
#include <vector>
#include <cfloat>

using namespace std;

namespace Math
{
    class Vector{
    public:
        Vector(float x = 0, float y = 0, float z = 0);
        
        const float& operator[](int i) const
        {
            return vec[i];
        }
        
        Vector& operator=(const Vector& v)
        {
            vec[0] = v.vec[0];
            vec[1] = v.vec[1];
            vec[2] = v.vec[2];
            return *this;
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
        
        bool operator<(const Vector& v) const { return vec[0] < v[0] && vec[1] < v[1] && vec[2] < v[2]; }
        
        bool operator>(const Vector& v) const { return vec[0] > v[0] && vec[1] > v[1] && vec[2] > v[2]; }
        
        bool operator<=(const Vector& v) const { return vec[0] <= v[0] && vec[1] <= v[1] && vec[2] <= v[2]; }
        
        bool operator>=(const Vector& v) const { return vec[0] >= v[0] && vec[1] >= v[1] && vec[2] >= v[2]; }
        
        Vector operator+=(const Vector& v);
        
        Vector normalized() const;
        
        //ortogonal part to another vector
        Vector ortogonal(const Vector&) const;
        
        float len() const;
        
    private:
        float vec[3];
    };

    inline Vector operator*(float f, Vector& v)
    {
        return v * f;
    }

    Vector cross(const Vector& v1, const Vector& v2);
    
    float dot(const Vector& v1, const Vector& v2);

    typedef vector<Vector> VArray;
    
    Vector centerMass(const VArray& p);
    void centralize(VArray& p);
    
    inline float* getFloatPointer(VArray& a) { return &a[0][0];}
    
    void scale(VArray& p, float scale);
    float maxRadius(VArray& p);
    
#define MAX_VECTOR Vector(FLT_MAX,FLT_MAX,FLT_MAX)
#define MIN_VECTOR Vector(FLT_MIN,FLT_MIN,FLT_MIN)
}

#endif