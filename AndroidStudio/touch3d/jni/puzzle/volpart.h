#pragma once

#include "base.h"
#include "vector.h"
#include "mat.h"

namespace Geometry
{
class VolPart
{
public:
    enum class VolType
    {
        Empty,
        Full,
        Angle
    };

    VolPart(VolType t, Vector coord, Vector iniDir = Vector(0, 0, 0)):
        fillInfo(t), xyz(coord), dir(iniDir) {}

    bool operator==(const VolPart& vol) const;

    bool hasSide(int dim, int val) const;

    VolPart& operator+=(const VolPart& v);

    VolPart& shift(const Vector& shift);

    VolPart& rotate(RotType rot);

    VolPart& rotate(const Mat& m);

    VolPart& operator-=(const VolPart& another);

    bool couldPlace(const VolPart& another) const;

    bool shareOneOfSides(const VolPart& another) const;

    const Vector& getCoords() const
    {
        return xyz;
    }
    void setCoords(const Vector& coords)
    {
        xyz = coords;
    }

    const Vector& getDir() const
    {
        return dir;
    }
    void setDir(const Vector& d)
    {
        dir = d;
    }

    VolType type() const
    {
        return fillInfo;
    }
    void setType(VolType t)
    {
        fillInfo = t;
    }
private:

    VolType fillInfo;
    Vector xyz, dir;
};
}
