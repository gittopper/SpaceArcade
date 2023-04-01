//
//  boundingbox.h
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#ifndef __SpaceArcade__boundingbox__
#define __SpaceArcade__boundingbox__

#include "vector.h"

namespace Math {

class BoundingBox2D {
   public:
    void merge(const Vector& v);
    BoundingBox2D(const VArray& v);
    BoundingBox2D(float size)
        : vMin_(-size / 2., -size / 2.), vMax_(size / 2, size / 2) {}
    BoundingBox2D(float width, float height)
        : vMin_(-width / 2., -height / 2.), vMax_(width / 2., height / 2.) {}

    float getXDim() const { return vMax_[0] - vMin_[0]; }
    float getYDim() const { return vMax_[1] - vMin_[1]; }
    float getZDim() const { return vMax_[2] - vMin_[2]; }
    float getMaxDim() const { return max(getXDim(), getYDim()); }

    void scale(float s);
    void move(Vector v);

    const Vector& getMin() const { return vMin_; }
    const Vector& getMax() const { return vMax_; }

    BoundingBox2D operator+(const Vector& v) const {
        return BoundingBox2D(vMin_ + v, vMax_ + v);
    }

    bool isInside(const Vector& v) const {
        return vMin_[0] <= v[0] && vMin_[1] <= v[1] && vMax_[0] >= v[0] &&
               vMax_[1] >= v[1];
    }
    bool isInside(const BoundingBox2D& v) const {
        return isInside(v.vMin_) && isInside(v.vMax_);
    }

    bool intersects(const BoundingBox2D& v) const {
        return isInside(v.vMin_) || isInside(v.vMax_);
    }

    static BoundingBox2D getCube(float s) {
        Vector v(s, s, s);

        return BoundingBox2D(-v, v);
    }

   private:
    BoundingBox2D(Vector a, Vector b) : vMin_(a), vMax_(b) {}
    Vector vMin_, vMax_;
};

}  // namespace Math
#endif /* defined(__SpaceArcade__boundingbox__) */
