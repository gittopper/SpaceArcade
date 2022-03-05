//
//  spacegamerenderer.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef __SpaceArcade__spacegamerenderer__
#define __SpaceArcade__spacegamerenderer__

#include "rendering/renderer.h"
#include "game/regressvisitor.h"
#include "game/visitor.h"

namespace Game
{
    class SpaceGameRenderer:virtual public Renderer, virtual public RegressVisitor
    {
        void visit(IObject&) = 0;
    };
}
#endif /* defined(__SpaceArcade__spacegamerenderer__) */
