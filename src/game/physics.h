//
//  physics.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#ifndef __SpaceArcade__physics__
#define __SpaceArcade__physics__

#include "math/gamemath.h"
#include "regressvisitor.h"

using namespace Math;

namespace Game {
class Physics : public RegressVisitor {
   public:
    void visit(IObject&);
    void visit(Scene&) {}

   protected:
};
}  // namespace Game
#endif /* defined(__SpaceArcade__physics__) */
