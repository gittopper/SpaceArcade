#pragma once

#include <game/iobject.h>

namespace Game {

class Scene : public IObject {
  public:
    GAME_OBJECT(Scene)

    void setupScene(float w, float h);

    virtual void visit(class IObject&);

    virtual void accept(Visitor& visitor) {
        visitor.visit(*this);
    }
};
}  // namespace Game
