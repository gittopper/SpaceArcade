#pragma once

#include <game/camera.h>
#include <game/gameconfig.h>
#include <game/isoundplayer.h>
#include <game/resourceloader.h>
#include <game/timer.h>

#include <memory>
#include <random>

namespace Game {

class IGame {
  public:
    struct GameStateData {
        Camera camera_;
        GameConfig config_;
        Timer time_;
        int num_lives_ = 0;
        int num_level_ = 1;
        std::shared_ptr<ISoundPlayer> player_;
        std::shared_ptr<ResourceLoader> resource_loader_;
        int num_exploded_asteroids = 0;
        int num_shoots = 0;
        int num_asteroids = 0;
        std::default_random_engine generator_;

        bool gameLost() const {
            return num_lives_ == 0;
        }
    };
    virtual void gameOver() = 0;

    virtual class LevelConfig* getLevelConfig() = 0;

    virtual ~IGame() {}
    GameStateData game_state_;
};

}  // namespace Game
