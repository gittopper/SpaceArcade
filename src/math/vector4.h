//
//  vector4.h
//  SpaceArcade
//
//  Created by Admin on 21/10/14.
//
//

#ifndef SpaceArcade_vector4_h
#define SpaceArcade_vector4_h

#include <vector>

#include "common.h"
using namespace std;

namespace Math {
class Vector4 {
   public:
    Vector4(float x = 0, float y = 0, float z = 0, float w = 0) {
        vec_[0] = x;
        vec_[1] = y;
        vec_[2] = z;
        vec_[3] = w;
    }

    Vector4& operator=(const Vector4& v) {
        vec_[0] = v.vec_[0];
        vec_[1] = v.vec_[1];
        vec_[2] = v.vec_[2];
        vec_[3] = v.vec_[3];
        return *this;
    }

    const float& operator[](int i) const { return vec_[i]; }

    float& operator[](int i) { return vec_[i]; }

   private:
    float vec_[4];
};
typedef vector<Vector4> V4Array;

V4Array generateArray(const Vector4& p, int size);
}  // namespace Math
#endif
