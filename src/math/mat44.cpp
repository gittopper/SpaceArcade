//
//  mat44.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#include "mat44.h"
#include <math.h>


namespace Math
{

    // http://www.opengl.org/sdk/docs/man/xhtml/glOrtho.xml
    void SetOrtho(Mat44& m, float left, float right, float bottom, float top, float near, float far)
    {
        const float tx = - (right + left)/(right - left);
        const float ty = - (top + bottom)/(top - bottom);
        const float tz = - (far + near)/(far - near);

        m.m[0] = 2.0f/(right-left);
        m.m[1] = 0;
        m.m[2] = 0;
        m.m[3] = tx;
        
        m.m[4] = 0;
        m.m[5] = 2.0f/(top-bottom);
        m.m[6] = 0;
        m.m[7] = ty;
        
        m.m[8] = 0;
        m.m[9] = 0;
        m.m[10] = -2.0/(far-near);
        m.m[11] = tz;
        
        m.m[12] = 0;
        m.m[13] = 0;
        m.m[14] = 0;
        m.m[15] = 1;
    }


    void SetRotY(Mat44& m, float angle)
    {
        const float c = cosf(angle);
        const float s = sinf(angle);

        m.m[0] = c;
        m.m[1] = 0;
        m.m[2] = -s;
        m.m[3] = 0;

        m.m[4] = 0;
        m.m[5] = 1;
        m.m[6] = 0;
        m.m[7] = 0;

        m.m[8] = s;
        m.m[9] = 0;
        m.m[10] = c;
        m.m[11] = 0;
        
        m.m[12] = 0;
        m.m[13] = 0;
        m.m[14] = 0;
        m.m[15] = 1;	
    }


    void SetRotZ(Mat44& m, float angle)
    {
        const float c = cosf(angle);
        const float s = sinf(angle);

        m.m[0] = c;
        m.m[1] = -s;
        m.m[2] = 0;
        m.m[3] = 0;

        m.m[4] = s;
        m.m[5] = c;
        m.m[6] = 0;
        m.m[7] = 0;

        m.m[8] = 0;
        m.m[9] = 0;
        m.m[10] = 1;
        m.m[11] = 0;
        
        m.m[12] = 0;
        m.m[13] = 0;
        m.m[14] = 0;
        m.m[15] = 1;	
    }


    void Mul(Mat44& m, const Mat44& a, const Mat44& b)
    {
        m.m[0] = a.m[0]*b.m[0] + a.m[1]*b.m[4] + a.m[2]*b.m[8] + a.m[3]*b.m[12];
        m.m[1] = a.m[0]*b.m[1] + a.m[1]*b.m[5] + a.m[2]*b.m[9] + a.m[3]*b.m[13];
        m.m[2] = a.m[0]*b.m[2] + a.m[1]*b.m[6] + a.m[2]*b.m[10] + a.m[3]*b.m[14];
        m.m[3] = a.m[0]*b.m[3] + a.m[1]*b.m[7] + a.m[2]*b.m[11] + a.m[3]*b.m[15];

        m.m[4] = a.m[4]*b.m[0] + a.m[5]*b.m[4] + a.m[6]*b.m[8] + a.m[7]*b.m[12];
        m.m[5] = a.m[4]*b.m[1] + a.m[5]*b.m[5] + a.m[6]*b.m[9] + a.m[7]*b.m[13];
        m.m[6] = a.m[4]*b.m[2] + a.m[5]*b.m[6] + a.m[6]*b.m[10] + a.m[7]*b.m[14];
        m.m[7] = a.m[4]*b.m[3] + a.m[5]*b.m[7] + a.m[6]*b.m[11] + a.m[7]*b.m[15];

        m.m[8] = a.m[8]*b.m[0] + a.m[9]*b.m[4] + a.m[10]*b.m[8] + a.m[11]*b.m[12];
        m.m[9] = a.m[8]*b.m[1] + a.m[9]*b.m[5] + a.m[10]*b.m[9] + a.m[11]*b.m[13];
        m.m[10] = a.m[8]*b.m[2] + a.m[9]*b.m[6] + a.m[10]*b.m[10] + a.m[11]*b.m[14];
        m.m[11] = a.m[8]*b.m[3] + a.m[9]*b.m[7] + a.m[10]*b.m[11] + a.m[11]*b.m[15];

        m.m[12] = a.m[12]*b.m[0] + a.m[13]*b.m[4] + a.m[14]*b.m[8] + a.m[15]*b.m[12];
        m.m[13] = a.m[12]*b.m[1] + a.m[13]*b.m[5] + a.m[14]*b.m[9] + a.m[15]*b.m[13];
        m.m[14] = a.m[12]*b.m[2] + a.m[13]*b.m[6] + a.m[14]*b.m[10] + a.m[15]*b.m[14];
        m.m[15] = a.m[12]*b.m[3] + a.m[13]*b.m[7] + a.m[14]*b.m[11] + a.m[15]*b.m[15];
    }

    void convertTo44(Mat44& m, const Mat& m33, const Vector& v)
    {
        m.m[0] = m33.el(0, 0);
        m.m[4] = m33.el(0, 1);
        m.m[8] = m33.el(0, 2);
        
        m.m[1] = m33.el(1, 0);
        m.m[5] = m33.el(1, 1);
        m.m[9] = m33.el(1, 2);
        
        m.m[2] = m33.el(2, 0);
        m.m[6] = m33.el(2, 1);
        m.m[10] = m33.el(2, 2);
        
        m.m[12] = v[0];
        m.m[13] = v[1];
        m.m[14] = v[2];
        
        m.m[15] = 1;
        
        m.m[3] = 0;
        m.m[7] = 0;
        m.m[11] = 0;
    }

}
