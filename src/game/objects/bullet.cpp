
#include "bullet.h"

#include "game/gameconfig.h"
#include "gameobjects.h"

namespace Game {
Bullet::Bullet(Vector startPoint, Vector speed) {
    points_.push_back(Vector(0, 0));
    points_.push_back(Vector(0, 20));
    points_.push_back(Vector(1, 20));
    points_.push_back(Vector(1, 0));
    points_.push_back(Vector(0, 0));

    ++game->game_state_.num_shoots;
    normalize();

    getV() = speed;
    scale(0.6);
    move(startPoint);
    // move(Vector(0,0,1.));
}

}  // namespace Game
