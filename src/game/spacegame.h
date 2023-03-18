//
//  spacegame.h
//  SpaceArcade
//
//  Created by Admin on 19/10/14.
//
//

#ifndef _SpaceGame_h_
#define _SpaceGame_h_

#include "math/gamemath.h"
#include <string>
#include "rendering/spacegamerenderer.h"
#include "game/objects/gameobjects.h"
#include "game/gameconfig.h"
#include "game/physics.h"
#include "game/collider.h"
#include <random>
#include "igame.h"

using namespace Math;
using namespace std;

namespace Game
{
    
    class SpaceGame:public IGame
    {
    public:
    
       SpaceGame();
    
        void setupGame(GameConfig conf = GameConfig());
        GameConfig* getGameConfig(){ return &config;}
        
        void drag(int x, int y);
        
        void tap(int x, int y);
        
        void renderStep();
        void setRenderer(SpaceGameRenderer* r) { renderer = r; }
        Renderer* getRenderer() { return renderer;}

        void gameOver();
        
        void addGameObject(class IObject*);

        void pause();

        void resume();
        
        GameConfig& getConfig() { return config;}
        float getAnimationInterval() { return config.dt;}
    private:
        void createAsteroid();
        
        int w, h;
        
        Scene scene;
        SpaceShip* spaceship;
        
        ObjectsSet objectsToAdd;
        
        float time;
        float asteroidsNextTime;
        
        bool gameLost;
        bool paused;
        float aspect;
        
        GameConfig config;
        
        default_random_engine generator;
        normal_distribution<float> asteroidsDelay;
        normal_distribution<float> asteroidsSpeed;
        normal_distribution<float> asteroidsSize;
        normal_distribution<float> asteroidsSpeedAngle;
        uniform_real_distribution<float> asteroidPlace;
        
        SpaceGameRenderer* renderer;
        Physics physics;
        Collider collider;
    };
}
#endif
