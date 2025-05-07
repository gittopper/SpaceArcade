#pragma once

#include <game/iobject.h>

#include <game/objects/spaceship.h>

namespace Game {

class Perk : public IObject {
  public:
    GAME_OBJECT(Perk)
    enum Type{
        Live,
        Explode
    };
    Perk(Type type);

    virtual void visit(class SpaceShip&);

    virtual void accept(Visitor& visitor) {
        visitor.visit(*this);
    }
};
}  // namespace Game
