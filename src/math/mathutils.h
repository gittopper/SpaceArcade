#pragma once

#include <math/gamemath.h>

void applyTransformsToPoints(Math::VArray& out,
                             const Math::VArray& in,
                             const Math::Mat& m,
                             const Math::Vector& v);
