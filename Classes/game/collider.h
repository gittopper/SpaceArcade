//
//  collider.h
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#ifndef __SpaceArcade__collider__
#define __SpaceArcade__collider__

#include "regressvisitor.h"
#include "gamemath.h"

using namespace Math;


namespace Game
{
    class Collider:virtual public RegressVisitor
    {
    public:
        Collider(Scene* s):scene(s){}
        void visit(IObject&);
    protected:
        Scene* scene;
    };
}

#endif /* defined(__SpaceArcade__collider__) */
