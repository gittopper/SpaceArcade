#include "volpart.h"

namespace Geometry {
bool VolPart::operator==(const VolPart& vol) const {
    return xyz == vol.xyz && fillInfo == vol.fillInfo &&
           (fillInfo != VolType::Angle || dir == vol.dir);
}

bool VolPart::hasSide(int dim, int val) const {
    if (fillInfo == VolType::Empty) return false;
    if (fillInfo == VolType::Full) return true;
    BREAK_ON_LINE(!dir[dim] || dir[dim] * dir[dim] == 1);
    return dir[dim] * (1 - 2 * val) >= 0;
}

VolPart& VolPart::shift(const Vector& shift) {
    xyz += shift;
    return *this;
}

VolPart& VolPart::operator+=(const VolPart& v) {
    BREAK_ON_LINE(xyz == v.xyz);
    if (fillInfo == VolType::Empty) {
        fillInfo = v.fillInfo;
        dir = v.dir;
        return *this;
    }
    if (fillInfo == VolType::Angle && v.fillInfo == VolType::Angle &&
        dir == -v.dir) {
        fillInfo = VolType::Full;
        return *this;
    }
    BREAK_ON_LINE(false);
    return *this;
}

VolPart& VolPart::rotate(RotType rot) {
    BREAK_ON_LINE(fillInfo != VolType::Empty);
    xyz.rotate(rot);
    if (fillInfo == VolType::Angle) dir.rotate(rot);
    return *this;
}

VolPart& VolPart::rotate(const Mat& m) {
    xyz = m * xyz;
    if (fillInfo == VolType::Angle) dir = m * dir;
    return *this;
}

VolPart& VolPart::operator-=(const VolPart& another) {
    if (fillInfo == VolType::Full) {
        if (another.fillInfo == VolType::Full) {
            fillInfo = VolType::Empty;
            return *this;
        } else if (another.fillInfo == VolType::Angle) {
            fillInfo = VolType::Angle;
            dir = -another.dir;
            return *this;
        } else {
            BREAK_ON_LINE(false);
        }
    }
    if (fillInfo == VolType::Angle) {
        if (another.fillInfo == VolType::Angle && dir == another.dir) {
            fillInfo = VolType::Empty;
            return *this;
        } else {
            BREAK_ON_LINE(false);
        }
    }
    return *this;
}
bool VolPart::couldPlace(const VolPart& another) const {
    BREAK_ON_LINE(xyz == another.xyz);
    BREAK_ON_LINE(another.fillInfo != VolType::Empty);
    return fillInfo == VolType::Empty ||
           fillInfo == VolType::Angle && another.fillInfo == VolType::Angle &&
               dir == -another.dir ||
           fillInfo == VolType::Full && another.fillInfo == VolType::Empty;
}
bool VolPart::shareOneOfSides(const VolPart& another) const {
    BREAK_ON_LINE(dot(xyz - another.xyz, xyz - another.xyz) <= 1);

    if (fillInfo == VolType::Empty || another.fillInfo == VolType::Empty) {
        return false;
    }
    if (fillInfo == VolType::Full && another.fillInfo == VolType::Full) {
        return true;
    }
    if (fillInfo == VolType::Angle && another.fillInfo == VolType::Full) {
        return dot(dir, another.xyz - xyz) < 0;
    }
    if (fillInfo == VolType::Full && another.fillInfo == VolType::Angle) {
        return dot(another.dir, xyz - another.xyz) < 0;
    }
    if (fillInfo == VolType::Angle && another.fillInfo == VolType::Angle) {
        // return true;
        if (xyz == another.xyz) {
            if (dir == -another.dir) {
                return true;
            }
            BREAK_ON_LINE(false);
        } else {
            return dot(dir, another.xyz - xyz) < 0 &&
                   dot(another.dir, xyz - another.xyz) < 0;
        }
    }
    BREAK_ON_LINE(false);
    return false;
}
}  // namespace Geometry
