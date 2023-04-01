//
//  igame.h
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#ifndef __SpaceArcade__gameinstance__
#define __SpaceArcade__gameinstance__

namespace Game {

class IGame {
   public:
    virtual void gameOver() = 0;

    virtual class GameConfig* getGameConfig() = 0;
    virtual void addGameObject(class IObject*) = 0;

    virtual ~IGame() {}
};

}  // namespace Game
#endif /* defined(__SpaceArcade__gameinstance__) */
