#pragma once

#include "math/gamemath.h"
#include "regressvisitor.h"

using namespace Math;

namespace Game {
class Collider : public RegressVisitor {
  public:
    Collider(Scene* s) : scene(s) {}
    void visit(IObject& gameobject);

  protected:
    Scene* scene;
};
}  // namespace Game
