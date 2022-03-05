//
//  spaceship.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#include "spaceship.h"
#include "gameobjects.h"
#include "game/collisionrules.h"

using namespace Math;

namespace Game
{
    SpaceShip::SpaceShip(float bulSpeed)

    {
        bulletSpeed = bulSpeed;
        
        points.push_back(Vector(0., -1.));
        points.push_back(Vector(-1.5, 0.));
        points.push_back(Vector(-3.5, 0.));
        points.push_back(Vector(-1.5, 2.));
        points.push_back(Vector(-1.5, 3.));
        points.push_back(Vector(-1., 3.));
        points.push_back(Vector(-0.7, 4.));
        
        points.push_back(Vector(0, 6.));

        points.push_back(Vector(-points[6][0], points[6][1]));
        points.push_back(Vector(-points[5][0], points[5][1]));
        points.push_back(Vector(-points[4][0], points[4][1]));
        points.push_back(Vector(-points[3][0], points[3][1]));
        points.push_back(Vector(-points[2][0], points[2][1]));
        points.push_back(Vector(-points[1][0], points[1][1]));
        points.push_back(Vector(-points[0][0], points[0][1]));
        
        /*
        points.push_back(Vector(0., 0.));
        points.push_back(Vector(0, 1.));
        points.push_back(Vector(1, 1.));
        points.push_back(Vector(1,0.));
        points.push_back(Vector(0., 0.));
         
         */
        
        color = Vector(1,0,0);
        normalize();
        
        box = BoundingBox2D(points);
    }
    

    void SpaceShip::shoot()
    {
        Vector v(0.2,0,0);
        
        IObject* bullet = new Bullet(getShift()+v,Vector(0,bulletSpeed));
        getParent()->addChild(bullet);
        
        bullet = new Bullet(getShift()-v,Vector(0,bulletSpeed));
        getParent()->addChild(bullet);
    }
}
