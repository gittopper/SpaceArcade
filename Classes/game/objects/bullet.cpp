//
//  bullet.cpp
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#include "bullet.h"
#include "gameobjects.h"
#include "gameconfig.h"

namespace Game
{
    Bullet::Bullet(Vector startPoint, Vector dir)
    {
        
        points.push_back(Vector(0,0));
        points.push_back(Vector(0,20));
        points.push_back(Vector(1,20));
        points.push_back(Vector(1,0));
        points.push_back(Vector(0,0));
        
        normalize();
        
        getV() = dir;
        scale(0.6);
        move(startPoint);
        //move(Vector(0,0,1.));
    }
    
}