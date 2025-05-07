#pragma once

namespace Game {
class Visitor {
  public:
    virtual void visit(class Asteroid&) = 0;
    virtual void visit(class Bullet&) = 0;
    virtual void visit(class SpaceShip&) = 0;
    virtual void visit(class Scene&) = 0;
    virtual void visit(class Perk&) = 0;
    virtual ~Visitor() {}
};
}  // namespace Game
