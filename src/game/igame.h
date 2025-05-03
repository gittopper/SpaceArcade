//
//  igame.h
//  SpaceArcade
//
//  Created by Admin on 22/10/14.
//
//

#ifndef __SpaceArcade__gameinstance__
#define __SpaceArcade__gameinstance__

#include "isoundplayer.h"

namespace Game {

class IGame {
  public:
    struct Stats {
        int num_exploded_asteroids = 0;
        int num_shoots = 0;
        int num_asteroids = 0;
    };
    virtual void gameOver() = 0;

    virtual class GameConfig* getGameConfig() = 0;
    virtual void addGameObject(class IObject*) = 0;

    virtual ISoundPlayer* player() = 0;

    virtual ~IGame() {}
    Stats stats;
};

}  // namespace Game
#endif /* defined(__SpaceArcade__gameinstance__) */
