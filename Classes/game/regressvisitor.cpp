//
//  regressvisitor.cpp
//  SpaceArcade
//
//  Created by Admin on 21/10/14.
//
//

#include "regressvisitor.h"
#include "gameobjects.h"

namespace Game
{
    void RegressVisitor::visit(Asteroid& a)
    {
        this->visit(dynamic_cast<IObject&>(a));
    }
    void RegressVisitor::visit(SpaceShip& s)
    {
        this->visit(dynamic_cast<IObject&>(s));
    }
    void RegressVisitor::visit(Bullet&b)
    {
        this->visit(dynamic_cast<IObject&>(b));
    }
    void RegressVisitor::visit(Scene&b)
    {
        this->visit(dynamic_cast<IObject&>(b));
    }
}
