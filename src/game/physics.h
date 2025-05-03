#pragma once

#include "math/gamemath.h"
#include "regressvisitor.h"

using namespace Math;

namespace Game {
class Physics : public RegressVisitor {
  public:
    void setDt(float dt) {
        dt_ = dt;
    }
    void visit(IObject&);
    void visit(Scene&) {}

  protected:
    float dt_;
};
}  // namespace Game
