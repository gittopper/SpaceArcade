//
//  vector4.h
//  SpaceArcade
//
//  Created by Admin on 21/10/14.
//
//

#ifndef SpaceArcade_vector4_h
#define SpaceArcade_vector4_h


#include "common.h"
#include <vector>
using namespace std;

namespace Math
{
    class Vector4
    {
    public:
        Vector4(float x = 0, float y = 0, float z = 0, float w = 0)
        {
            vec[0] = x;
            vec[1] = y;
            vec[2] = z;
            vec[3] = w;
        }
        
        Vector4& operator=(const Vector4& v)
        {
            vec[0] = v.vec[0];
            vec[1] = v.vec[1];
            vec[2] = v.vec[2];
            vec[3] = v.vec[3];
            return *this;
        }
        
        const float& operator[](int i) const
        {
            return vec[i];
        }

        float& operator[](int i)
        {
            return vec[i];
        }
        
    private:
        float vec[4];
    };
    typedef vector<Vector4> V4Array;
    
    V4Array generateArray(const Vector4& p, int size);
    inline float* getFloatPointer(V4Array& a) { return &a[0][0];}
}
#endif
