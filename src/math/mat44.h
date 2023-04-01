//
//  mat44.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef _Mat44_h_
#define _Mat44_h_

#include "vector.h"
#include "mat.h"

namespace Math
{
    
    struct Mat44
    {
        float m_[16];
    };

    void SetOrtho(Mat44& m, float left, float right, float bottom, float top, float near, float far);
	void SetRotY(Mat44& m, float angle);
	void SetRotZ(Mat44& m, float angle);
	void Mul(Mat44& m, const Mat44& a, const Mat44& b);
    void convertTo44(Mat44& m, const Mat& m33, const Vector& v);
}

#endif
