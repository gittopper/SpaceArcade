//
//  bullet.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef Shader_bullet_h
#define Shader_bullet_h

#include "game/iobject.h"

namespace Game
{
    
    class Bullet: public IObject
    {
    public:
        GAME_OBJECT(Bullet)
        Bullet(Vector startPoint, Vector dir);
        
       void visit(Asteroid&);
        
       virtual void accept(Visitor& visitor){ visitor.visit(*this);}

    };
}


#endif
