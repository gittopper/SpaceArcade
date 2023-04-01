//
//  collisionrules.h
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#ifndef __SpaceArcade__collisionrules__
#define __SpaceArcade__collisionrules__

#include "game/objects/gameobjects.h"

namespace Game {
bool isInside(const VArray& points, Vector p);
bool advancedInsideCheck(const VArray& p1, const VArray& p2);
}  // namespace Game

#endif /* defined(__SpaceArcade__collisionrules__) */
