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
    vMin_[0] = min(vMin_[0], v[0]);
    vMin_[1] = min(vMin_[1], v[1]);
    vMin_[2] = min(vMin_[2], v[2]);

    vMax_[0] = max(vMax_[0], v[0]);
    vMax_[1] = max(vMax_[1], v[1]);
    vMax_[2] = max(vMax_[2], v[2]);
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
    vMax_ = vMax_*s;
    vMin_ = vMin_*s;
}

void BoundingBox2D::move(Vector v)
{
    vMax_ += v;
    vMin_ += v;
}

