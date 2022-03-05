//
//  regressvisitor.h
//  SpaceArcade
//
//  Created by Admin on 21/10/14.
//
//

#ifndef __SpaceArcade__regressvisitor__
#define __SpaceArcade__regressvisitor__

#include "visitor.h"
#include "math/gamemath.h"

namespace Game
{
    //this derived visitor provides ability to not obligate definition of all interactions
    class RegressVisitor:virtual public Visitor
    {
    public:
        virtual void visit(class IObject&){}
        
        void visit(Asteroid&);
        void visit(SpaceShip&);
        void visit(Bullet&);
        void visit(Scene&);
    };
}
#endif /* defined(__SpaceArcade__regressvisitor__) */
