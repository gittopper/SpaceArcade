//
//  collider.h
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#ifndef __SpaceArcade__collider__
#define __SpaceArcade__collider__

#include "math/gamemath.h"
#include "regressvisitor.h"

using namespace Math;

namespace Game {
class Collider : public RegressVisitor {
   public:
    Collider(Scene* s) : scene(s) {}
    void visit(IObject& gameobject);

   protected:
    Scene* scene;
};
}  // namespace Game

#endif /* defined(__SpaceArcade__collider__) */
