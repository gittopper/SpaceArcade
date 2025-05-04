#pragma once

#include <game/regressvisitor.h>
#include <game/visitor.h>
#include <rendering/renderer.h>

namespace Game {
class SpaceGameRenderer : virtual public Renderer, public RegressVisitor {
    void visit(IObject&) = 0;
};
}  // namespace Game
