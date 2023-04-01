//
//  regressvisitor.h
//  SpaceArcade
//
//  Created by Admin on 21/10/14.
//
//

#ifndef __SpaceArcade__regressvisitor__
#define __SpaceArcade__regressvisitor__

#include "math/gamemath.h"
#include "visitor.h"

namespace Game {
// this derived visitor provides ability to not obligate definition of all
// interactions
class RegressVisitor : public Visitor {
   public:
    virtual void visit(class IObject&) {}

    void visit(Asteroid&);
    void visit(SpaceShip&);
    void visit(Bullet&);
    void visit(Scene&);
};
}  // namespace Game
#endif /* defined(__SpaceArcade__regressvisitor__) */
