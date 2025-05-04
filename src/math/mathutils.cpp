
#include <math/mathutils.h>

void applyTransformsToPoints(Math::VArray& out,
                             const Math::VArray& in,
                             const Math::Mat& m,
                             const Math::Vector& v) {
    out.clear();
    for (auto& vv : in) {
        out.push_back(m * vv + v);
    }
}
