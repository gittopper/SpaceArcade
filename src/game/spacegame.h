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
#include <memory>

using namespace Math;
using namespace std;

namespace Game
{
    
    class SpaceGame:public IGame
    {
    public:
    
       SpaceGame();
    
        void setupGame(GameConfig conf = GameConfig());
        GameConfig* getGameConfig() override{ return &config_;}
        
        void drag(int x, int y);
        
        void tap(int x, int y);
        
        void renderStep();
        void showFrame();
        void setRenderer(SpaceGameRenderer* r) { renderer_ = r; }
        Renderer* getRenderer() { return renderer_;}
        void setPlayer(std::shared_ptr<ISoundPlayer> player) { player_ = player; }
        ISoundPlayer* player() override { return player_.get();}

        void gameOver() override;
        
        void addGameObject(class IObject*) override;

        void pause();

        void resume();
        
        GameConfig& getConfig() { return config_;}
        float getAnimationInterval() const { return config_.dt_;}
    private:
        void createAsteroid();
        
        int w_, h_;

        std::vector<RGBAPixel> test_sprite_;
        Scene scene_;
        SpaceShip* spaceship_;
        
        ObjectsSet objectsToAdd_;
        
        float time_;
        float asteroidsNextTime_;
        
        bool gameLost_;
        bool paused_;
        float aspect_;
        
        GameConfig config_;
        
        default_random_engine generator_;
        normal_distribution<float> asteroidsDelay_;
        normal_distribution<float> asteroidsSpeed_;
        normal_distribution<float> asteroidsSize_;
        normal_distribution<float> asteroidsSpeedAngle_;
        uniform_real_distribution<float> asteroidPlace_;
        
        SpaceGameRenderer* renderer_;
        std::shared_ptr<ISoundPlayer> player_;
        Physics physics_;
        Collider collider_;
    };
}
#endif
