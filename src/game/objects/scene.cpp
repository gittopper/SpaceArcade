#pragma once
#include <game/collisionrules.h>
#include <game/objects/scene.h>

namespace Game {
void Scene::setupScene(float w, float h) {
    box_ = BoundingBox2D(w, h);
}

}  // namespace Game
