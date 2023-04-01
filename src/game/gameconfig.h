//
//  gameconfig.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#ifndef Shader_gameconfig_h
#define Shader_gameconfig_h

namespace Game {
struct GameConfig {
    GameConfig()
        : dt_(1. / 60),
          scale_(10),
          shipSize_(1.),
          asteroidsAvgPerSec_(3.),
          asteroidsSigmaPerSec_(1.),
          asteroidAvgSize_(0.5),
          asteroidAvgPartsNumber_(4),
          asteroidSigmaParts_(0),
          asteroidUnevennessSigma_(0.2),
          collideWithAsteroidParts_(true),
          markExploded_(true),
          asteroidsAvgSpeed_(4.),
          asteroidsSigmaSpeed_(1.),
          asteroidsSpeedAngleSigma_(10.),
          bulletSpeed_(4),
          maxSpaceShipSpeed_(4) {}
    // animation step
    float dt_;

    // screen width length in relative points
    float scale_;

    float shipSize_;

    float asteroidsAvgPerSec_;
    float asteroidsSigmaPerSec_;
    float asteroidAvgSize_;

    int asteroidAvgPartsNumber_;
    int asteroidSigmaParts_;

    float asteroidUnevennessSigma_;

    bool collideWithAsteroidParts_;
    bool markExploded_;

    float asteroidsAvgSpeed_;
    float asteroidsSigmaSpeed_;

    // in degreees
    float asteroidsSpeedAngleSigma_;

    float bulletSpeed_;
    float maxSpaceShipSpeed_;
};
}  // namespace Game
#endif
