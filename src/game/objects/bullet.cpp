//
//  bullet.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "bullet.h"

#include "game/gameconfig.h"
#include "gameobjects.h"

namespace Game {
Bullet::Bullet(Vector startPoint, Vector dir) {
    points_.push_back(Vector(0, 0));
    points_.push_back(Vector(0, 20));
    points_.push_back(Vector(1, 20));
    points_.push_back(Vector(1, 0));
    points_.push_back(Vector(0, 0));

    normalize();

    getV() = dir;
    scale(0.6);
    move(startPoint);
    // move(Vector(0,0,1.));
}

}  // namespace Game
