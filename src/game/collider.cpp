#include <game/collider.h>
#include <game/objects/gameobjects.h>
#include <game/spacegame.h>
#include <math/gamemath.h>

using namespace Math;

namespace Game {
void Collider::visit(IObject& gameobject) {
    const char* objName = gameobject.name();
    scene->visitAll(gameobject);
}
}  // namespace Game
