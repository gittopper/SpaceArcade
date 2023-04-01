//
//  spaceship.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#include "spaceship.h"

#include "game/collisionrules.h"
#include "gameobjects.h"

using namespace Math;

namespace Game {
SpaceShip::SpaceShip(float bulSpeed)

{
    bulletSpeed_ = bulSpeed;

    points_.push_back(Vector(0., -1.));
    points_.push_back(Vector(-1.5, 0.));
    points_.push_back(Vector(-3.5, 0.));
    points_.push_back(Vector(-1.5, 2.));
    points_.push_back(Vector(-1.5, 3.));
    points_.push_back(Vector(-1., 3.));
    points_.push_back(Vector(-0.7, 4.));

    points_.push_back(Vector(0, 6.));

    points_.push_back(Vector(-points_[6][0], points_[6][1]));
    points_.push_back(Vector(-points_[5][0], points_[5][1]));
    points_.push_back(Vector(-points_[4][0], points_[4][1]));
    points_.push_back(Vector(-points_[3][0], points_[3][1]));
    points_.push_back(Vector(-points_[2][0], points_[2][1]));
    points_.push_back(Vector(-points_[1][0], points_[1][1]));
    points_.push_back(Vector(-points_[0][0], points_[0][1]));

    /*
    points.push_back(Vector(0., 0.));
    points.push_back(Vector(0, 1.));
    points.push_back(Vector(1, 1.));
    points.push_back(Vector(1,0.));
    points.push_back(Vector(0., 0.));

     */

    color_ = Vector(1, 0, 0);
    normalize();

    box_ = BoundingBox2D(points_);
}

void SpaceShip::shoot() {
    Vector v(0.3, 0, 0);

    IObject* bullet = new Bullet(getShift() + v, Vector(0, bulletSpeed_));
    getParent()->addChild(bullet);

    bullet = new Bullet(getShift() - v, Vector(0, bulletSpeed_));
    getParent()->addChild(bullet);
}
}  // namespace Game
