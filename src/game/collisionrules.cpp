//
//  collisionrules.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "collisionrules.h"

#include "gameconfig.h"

namespace {
void cutShift(BoundingBox2D& box, BoundingBox2D& envelopBox, Vector& shift) {
    if (shift[0] > 0) {
        float mr = envelopBox.getMax()[0] - box.getMax()[0];
        if (mr < shift[0]) {
            shift[0] = mr;
        }
    }
    if (shift[0] < 0) {
        float ml = envelopBox.getMin()[0] - box.getMin()[0];
        if (ml > shift[0]) {
            shift[0] = ml;
        }
    }
    if (shift[1] > 0) {
        float mt = envelopBox.getMax()[1] - box.getMax()[1];
        if (mt < shift[1]) {
            shift[1] = mt;
        }
    }
    if (shift[1] < 0) {
        float mb = envelopBox.getMin()[1] - box.getMin()[1];
        if (mb > shift[1]) {
            shift[1] = mb;
        }
    }
}
}  // namespace
namespace Game {

void SpaceShip::visit(class Scene& s) {
    if (!s.getBBox().isInside(getBBox() + velocity_)) {
        cutShift(getBBox(), s.getBBox(), velocity_);
    }
}

void Scene::visit(class IObject& obj) {
    if (!intersects(&obj) && Math::dot(obj.getShift(), obj.getV()) >=
                                 0  // not in scene and moving away
                                    //&& distance(&obj) > 1.5
    ) {
        obj.shouldBeRemoved = true;
    }
}

void Bullet::visit(Asteroid& a) {
    bool collide = game->getGameConfig()->collideWithAsteroidParts_;
    if (a.intersects(this) && (collide || !a.isParted())) {
        a.explode();
        shouldBeRemoved = true;
    }
}

void Asteroid::visit(SpaceShip& s) {
    bool collide = game->getGameConfig()->collideWithAsteroidParts_;
    if (this->intersects(&s) && (collide || !piece)) {
        VArray apoints, spoints;
        getProcessedPoints(apoints);
        s.getProcessedPoints(spoints);
        /*
                    Asteroid* p = new Asteroid;
                    p->getPoints() = apoints;
                    p->piece = true;
                    p->cacheDrawPoints();
                    game->addGameObject(p);
        */
        if (advancedInsideCheck(apoints, spoints)) game->gameOver();
    }
}
// this is algorithm to determine whether is the point inside the unconvex hull
// or not
bool isInside(const VArray& points, Vector p) {
    float x = p[0];
    float y = p[1];

    int numChanged = 0;

    for (int i = 0; i < points.size() - 1; i++) {
        float x1 = points[i][0] - x;
        float y1 = points[i][1] - y;

        float x2 = points[i + 1][0] - x;
        float y2 = points[i + 1][1] - y;

        if (x1 * x2 > 0 || (y1 < 0 && y2 < 0)) continue;

        if (y1 == 0 || y2 == 0) return true;

        if (x1 == 0 && x2 == 0) {
            if (y1 * y2 < 0) return true;
            continue;
        }

        if (y1 * y2 < 0) {
            float yI = y2 + x2 * (y1 - y2) / (x2 - x1);
            bool check = yI > min(y1, y2) && yI < max(y1, y2);
            if (yI < 0) continue;
        }
        if (x1 <= 0) {
            numChanged--;
        } else {
            numChanged++;
        }
    }
    return numChanged < 0;
}

bool advancedInsideCheck(const VArray& p1, const VArray& p2) {
    for (int i = 0; i < p1.size() - 1; i++) {
        if (isInside(p2, p1[i])) return true;
    }
    for (int i = 0; i < p2.size() - 1; i++) {
        if (isInside(p1, p2[i])) return true;
    }
    return false;
}
}  // namespace Game
