#pragma once

#include <game/objects/gameobjects.h>

namespace Game {
bool isInside(const VArray& points, Vector p);
bool advancedInsideCheck(const VArray& p1, const VArray& p2);
}  // namespace Game
