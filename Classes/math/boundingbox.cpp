//
//  boundingbox.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "boundingbox.h"

using namespace Math;

void BoundingBox2D::merge(const Vector& v)
{
    vMin[0] = min(vMin[0], v[0]);
    vMin[1] = min(vMin[1], v[1]);
    vMin[2] = min(vMin[2], v[2]);

    vMax[0] = max(vMax[0], v[0]);
    vMax[1] = max(vMax[1], v[1]);
    vMax[2] = max(vMax[2], v[2]);
}

BoundingBox2D::BoundingBox2D(const VArray& v)
{
    
    
    for(VArray::const_iterator it = v.begin(); it != v.end(); it++)
    {
        merge(*it);
    }
}

void BoundingBox2D::scale(float s)
{
    vMax = vMax*s;
    vMin = vMin*s;
}

void BoundingBox2D::move(Vector v)
{
    vMax += v;
    vMin += v;
}

