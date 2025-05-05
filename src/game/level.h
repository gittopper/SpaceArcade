#pragma once

#include <game/gameconfig.h>
#include <game/igame.h>
#include <game/objects/gameobjects.h>

namespace Game {

class Level {
  public:
    Level(IGame::GameStateData& game_data) : game_data_(game_data) {}

    void setupLevel(const LevelConfig& level_config);
    ~Level();
    void clearScene();
    void pause();
    void resume();
    void drag(int x, int y);
    void step();
    void resize();
    void createAsteroid();
    bool isFinished() const;
    IGame::GameStateData& game_data_;
    Scene scene_;
    SpaceShip* spaceship_ = nullptr;

    double last_update_time_ = 0;

    normal_distribution<float> asteroids_delay_;
    normal_distribution<float> asteroids_speed_;
    normal_distribution<float> asteroids_size_;
    normal_distribution<float> asteroids_speed_angle_;
    uniform_real_distribution<float> asteroid_place_;

    Timer level_pass_timer_;
    LevelConfig config_;
    float asteroids_next_time_ = 0;
};

}  // namespace Game
