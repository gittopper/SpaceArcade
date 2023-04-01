//
//  sceneboundary.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "scene.h"

#include "game/collisionrules.h"

namespace Game {
void Scene::setupScene(float w, float h) {
    box_ = BoundingBox2D(w, h);
    removeChildren();
}

}  // namespace Game
