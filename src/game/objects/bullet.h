#pragma once

#include "game/iobject.h"

namespace Game {

class Bullet : public IObject {
  public:
    GAME_OBJECT(Bullet)
    Bullet(Vector startPoint, Vector speed);

    void visit(Asteroid&);

    virtual void accept(Visitor& visitor) {
        visitor.visit(*this);
    }
};
}  // namespace Game
