//
//  physics.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#include "physics.h"

#include "gamemath.h"
#include "gameobjects.h"

using namespace Math;

namespace Game
{
    void Physics::visit(IObject& a)
    {
        a.move(a.getV());
    }
}