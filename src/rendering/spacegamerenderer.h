//
//  spacegamerenderer.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef __SpaceArcade__spacegamerenderer__
#define __SpaceArcade__spacegamerenderer__

#include "game/regressvisitor.h"
#include "game/visitor.h"
#include "rendering/renderer.h"

namespace Game {
class SpaceGameRenderer : virtual public Renderer, public RegressVisitor {
    void visit(IObject&) = 0;
};
}  // namespace Game
#endif /* defined(__SpaceArcade__spacegamerenderer__) */
