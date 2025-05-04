
#include <math/boundingbox.h>

using namespace Math;

void BoundingBox2D::merge(const Vector& v) {
    v_min_[0] = min(v_min_[0], v[0]);
    v_min_[1] = min(v_min_[1], v[1]);
    v_min_[2] = min(v_min_[2], v[2]);

    v_max_[0] = max(v_max_[0], v[0]);
    v_max_[1] = max(v_max_[1], v[1]);
    v_max_[2] = max(v_max_[2], v[2]);
}

BoundingBox2D::BoundingBox2D(const VArray& v) {
    for (VArray::const_iterator it = v.begin(); it != v.end(); it++) {
        merge(*it);
    }
}

void BoundingBox2D::scale(float s) {
    v_max_ = v_max_ * s;
    v_min_ = v_min_ * s;
}

void BoundingBox2D::move(Vector v) {
    v_max_ += v;
    v_min_ += v;
}
