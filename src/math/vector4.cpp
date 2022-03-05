//
//  vector4.cpp
//  SpaceArcade
//
//  Created by Admin on 21/10/14.
//
//

#include "vector4.h"

namespace Math
{
    V4Array generateArray(const Vector4& p, int size)
    {
        V4Array a;
        for (int i =0; i<size;i++)
        {
            a.push_back(p);
        }
        return a;
    }
}