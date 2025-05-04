#pragma once

#include "vector.h"

namespace Math {

class BoundingBox2D {
  public:
    void merge(const Vector& v);
    BoundingBox2D(const VArray& v);
    BoundingBox2D(float size) :
        v_min_(-size / 2., -size / 2.), v_max_(size / 2, size / 2) {}
    BoundingBox2D(float width, float height) :
        v_min_(-width / 2., -height / 2.), v_max_(width / 2., height / 2.) {}

    float getXDim() const {
        return v_max_[0] - v_min_[0];
    }
    float getYDim() const {
        return v_max_[1] - v_min_[1];
    }
    float getZDim() const {
        return v_max_[2] - v_min_[2];
    }
    float getMaxDim() const {
        return max(getXDim(), getYDim());
    }

    void scale(float s);
    void move(Vector v);

    const Vector& getMin() const {
        return v_min_;
    }
    const Vector& getMax() const {
        return v_max_;
    }

    BoundingBox2D operator+(const Vector& v) const {
        return BoundingBox2D(v_min_ + v, v_max_ + v);
    }

    bool isInside(const Vector& v) const {
        return v_min_[0] <= v[0] && v_min_[1] <= v[1] && v_max_[0] >= v[0] &&
               v_max_[1] >= v[1];
    }
    bool isInside(const BoundingBox2D& v) const {
        return isInside(v.v_min_) && isInside(v.v_max_);
    }

    bool intersects(const BoundingBox2D& v) const {
        return isInside(v.v_min_) || isInside(v.v_max_);
    }

    bool dist(const BoundingBox2D& v) const {
        return (v.v_min_ + v.v_max_).len() / (v_max_ - v_min_).len();
    }

    static BoundingBox2D getCube(float s) {
        Vector v(s, s, s);

        return BoundingBox2D(-v, v);
    }
    Vector clamp(const BoundingBox2D& boundary) {
        auto shift_min = [this, &boundary](int dim) {
            if (v_min_[dim] >= boundary.v_min_[dim]) {
                return 0.f;
            }
            auto shift = boundary.v_min_[dim] - v_min_[dim];
            v_min_[dim] = boundary.v_min_[dim];
            v_max_[dim] += shift;
            return shift;
        };
        Vector shift;
        shift[0] += shift_min(0);
        shift[1] += shift_min(1);
        shift[2] += shift_min(2);
        auto shift_max = [this, &boundary](int dim) {
            if (v_max_[dim] <= boundary.v_max_[dim]) {
                return 0.f;
            }
            auto shift = boundary.v_max_[dim] - v_max_[dim];
            v_max_[dim] = boundary.v_max_[dim];
            v_min_[dim] += shift;
            return shift;
        };
        shift[0] += shift_max(0);
        shift[1] += shift_max(1);
        shift[2] += shift_max(2);
        return shift;
    }

  private:
    BoundingBox2D(Vector a, Vector b) : v_min_(a), v_max_(b) {}
    Vector v_min_, v_max_;
};

}  // namespace Math
