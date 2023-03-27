#pragma once

#include "base.h"
#include "vector.h"

namespace Geometry
{
class BBox
{
public:
    BBox():
        minV(1000, 1000, 1000),
        maxV(-1000, -1000, -1000) {}
    void merge(const Vector& v)
    {
        minV[0] = minV[0] > v[0] ? v[0] : minV[0];
        minV[1] = minV[1] > v[1] ? v[1] : minV[1];
        minV[2] = minV[2] > v[2] ? v[2] : minV[2];

        maxV[0] = maxV[0] < v[0] ? v[0] : maxV[0];
        maxV[1] = maxV[1] < v[1] ? v[1] : maxV[1];
        maxV[2] = maxV[2] < v[2] ? v[2] : maxV[2];
    }
    void grow()
    {
        minV = minV - Vector(1, 1, 1);
        maxV = maxV + Vector(1, 1, 1);
    }

    int getXSize() const { return maxV[0] - minV[0];}
    int getYSize() const { return maxV[1] - minV[1];}
    int getZSize() const { return maxV[2] - minV[2];}

    Vector minV, maxV;
};
}
