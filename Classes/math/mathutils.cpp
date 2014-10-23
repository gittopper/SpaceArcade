//
//  mathutils.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "mathutils.h"

void applyTransformsToPoints(VArray& out, const VArray& in, const Mat& m, const Vector& v)
{
    out.clear();
    for(VArray::const_iterator it = in.begin(); it != in.end(); it ++)
    {
        out.push_back(m * (*it) + v);
    }
}
