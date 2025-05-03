#pragma once

#include "game/iobject.h"

namespace Game {

class SpaceShip : public IObject {
  public:
    SpaceShip(float bul_speed);

    GAME_OBJECT(SpaceShip)

    virtual void visit(class Scene&);

    void shoot();

    virtual void accept(Visitor& visitor) {
        visitor.visit(*this);
    }

  protected:
    float bullet_speed_;
};
}  // namespace Game
