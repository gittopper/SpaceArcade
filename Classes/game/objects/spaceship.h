//
//  spaceship.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef Shader_spaceship_h
#define Shader_spaceship_h

#include "iobject.h"


namespace Game
{
    
    class SpaceShip: public IObject
    {
    public:
        SpaceShip(float bulSpeed);
        
        GAME_OBJECT(SpaceShip)
        
        virtual void visit(class Scene&);

        void shoot();
        
        virtual void accept(Visitor& visitor){ visitor.visit(*this);}
        
    protected:
        float bulletSpeed;
    };
}

#endif
