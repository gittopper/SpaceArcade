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
    	GameConfig():
            dt(1. /60),
            scale(10),
            shipSize(1.),
            asteroidsAvgPerSec(3.),
            asteroidsSigmaPerSec(1.),
            asteroidAvgSize(0.5),
            asteroidAvgPartsNumber(4),
            asteroidSigmaParts(0),
            asteroidUnevennessSigma(0.2),
            collideWithAsteroidParts(true),
            markExploded(true),
            asteroidsAvgSpeed(4.),
            asteroidsSigmaSpeed(1.),
            asteroidsSpeedAngleSigma(10.),
            bulletSpeed(4),
            maxSpaceShipSpeed(4)
    	{}
        //animation step
        float dt;
        
        //screen width length in relative points
        float scale;
        
        float shipSize;
        
        float asteroidsAvgPerSec;
        float asteroidsSigmaPerSec;
        float asteroidAvgSize;
        
        int asteroidAvgPartsNumber;
        int asteroidSigmaParts;

        float asteroidUnevennessSigma;
        
        bool collideWithAsteroidParts;
        bool markExploded;
        
        float asteroidsAvgSpeed;
        float asteroidsSigmaSpeed;
        
        //in degreees
        float asteroidsSpeedAngleSigma;
        
        float bulletSpeed;
        float maxSpaceShipSpeed;
    };
}
#endif
