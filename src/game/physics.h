//
//  physics.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#ifndef __SpaceArcade__physics__
#define __SpaceArcade__physics__

#include "regressvisitor.h"
#include "math/gamemath.h"

using namespace Math;


namespace Game
{
    class Physics:virtual public RegressVisitor
    {
    public:

        void visit(IObject&);
        void visit(Scene&){}
    protected:
    };
}
#endif /* defined(__SpaceArcade__physics__) */
