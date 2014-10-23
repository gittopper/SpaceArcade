//
//  scene.h
//  SpaceArcade
//
//  Created by Admin on 21/10/14.
//
//

#ifndef SpaceArcade_scene_h
#define SpaceArcade_scene_h


#include "iobject.h"


namespace Game
{
    
    class Scene: public IObject
    {
    public:
        GAME_OBJECT(Scene)
        
        void setupScene(float w, float h);
        
        virtual void visit(class IObject&);

        virtual void accept(Visitor& visitor){ visitor.visit(*this);}
    };
}

#endif
