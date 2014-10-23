//
//  sceneboundary.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "scene.h"
#include "collisionrules.h"

namespace Game
{
    void Scene::setupScene(float w, float h)
    {
        box = BoundingBox2D(w, h);
        removeChildren();
    }

}