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
    struct GameConfig
    {
        //animation step
        float dt = 1. /60;
        
        //screen width length in relative points
        float scale = 10;
        
        float shipSize = 1.;
        
        float asteroidsAvgPerSec = 3.;
        float asteroidsSigmaPerSec = 1.;
        float asteroidAvgSize = 0.5;
        
        int asteroidAvgPartsNumber = 4;
        int asteroidSigmaParts = 0;

        float asteroidUnevennessSigma = 0.2;
        
        bool collideWithAsteroidParts = true;
        bool markExploded = true;
        
        float asteroidsAvgSpeed = 4.;
        float asteroidsSigmaSpeed = 1.;
        
        //in degreees
        float asteroidsSpeedAngleSigma = 10.;
        
        float bulletSpeed = 4;
        float maxSpaceShipSpeed = 4;
    };
}
#endif
