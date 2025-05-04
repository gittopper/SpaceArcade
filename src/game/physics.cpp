
#include "physics.h"

#include "game/objects/gameobjects.h"
#include "math/gamemath.h"

using namespace Math;

namespace Game {
void Physics::visit(IObject& a) {
    a.move(a.getV() * dt_);
}
}  // namespace Game
