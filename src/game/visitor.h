//
//  visitor.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef Shader_visitor_h
#define Shader_visitor_h

namespace Game {
class Visitor {
   public:
    virtual void visit(class Asteroid&) = 0;
    virtual void visit(class Bullet&) = 0;
    virtual void visit(class SpaceShip&) = 0;
    virtual void visit(class Scene&) = 0;
    virtual ~Visitor() {}
};
}  // namespace Game

#endif
