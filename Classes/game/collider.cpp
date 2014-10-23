//
//  collider.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "collider.h"

#include "gamemath.h"
#include "gameobjects.h"
#include "spacegame.h"

using namespace Math;

namespace Game
{
    void Collider::visit(IObject& gameobject)
    {
        const char* objName = gameobject.name();
        scene->visitAll(gameobject);
    }
}