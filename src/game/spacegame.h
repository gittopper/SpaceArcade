#pragma once

#include <game/collider.h>
#include <game/font.h>
#include <game/gameconfig.h>
#include <game/igame.h>
#include <game/objects/gameobjects.h>
#include <game/physics.h>
#include <game/resourceloader.h>
#include <game/sprite.h>
#include <game/timer.h>
#include <math/gamemath.h>
#include <rendering/spacegamerenderer.h>

#include <memory>
#include <random>
#include <string>

#include <SFML/Graphics/Font.hpp>

namespace Game {

class SpaceGame : public IGame {
  public:
    struct GameState {};

    SpaceGame();

    void setupGame(int w, int h);

    void resize(int w, int h);
    GameConfig* getGameConfig() override {
        return &config_;
    }

    void drag(int x, int y);

    void tap(int x, int y);

    void renderStep();
    void showFrame();
    void setRenderer(SpaceGameRenderer* r) {
        renderer_ = r;
    }
    Renderer* getRenderer() {
        return renderer_;
    }
    void setPlayer(std::shared_ptr<ISoundPlayer> player) {
        player_ = player;
    }
    ResourceLoader* getResourceLoader() {
        return resource_loader_.get();
    }
    void setResourceLoader(std::shared_ptr<ResourceLoader> resource_loader) {
        resource_loader_ = resource_loader;
    }
    ISoundPlayer* player() override {
        return player_.get();
    }

    void gameOver() override;

    void addGameObject(class IObject*) override;

    void pause();

    void resume();

    void step();

    GameConfig& getConfig() {
        return config_;
    }

  private:
    void createAsteroid();
    void renderOverlay();
    void initLevel();
    float aspect() const;
    void clearScene();

    int width_, height_;

    Scene scene_;
    SpaceShip* spaceship_ = nullptr;

    ObjectsSet objects_to_add_;

    Timer time_;
    double last_update_time_ = 0;
    bool game_lost_;
    bool paused_;
    int num_lives_;
    float asteroids_next_time_;
    GameConfig config_;
    Timer game_timer_;
    Timer level_timer_;
    Timer level_presentation_timer_;
    Timer level_pass_timer_;
    int num_level_ = 1;
    Rect2D game_lost_rect_;

    default_random_engine generator_;
    normal_distribution<float> asteroids_delay_;
    normal_distribution<float> asteroids_speed_;
    normal_distribution<float> asteroids_size_;
    normal_distribution<float> asteroids_speed_angle_;
    uniform_real_distribution<float> asteroid_place_;

    SpaceGameRenderer* renderer_;
    std::shared_ptr<ISoundPlayer> player_;
    Physics physics_;
    Collider collider_;
    std::shared_ptr<ResourceLoader> resource_loader_;
    std::shared_ptr<Sprite> overlay_transparent_;
    std::shared_ptr<Sprite> overlay_dark_;
    std::shared_ptr<Sprite> overlay_;
    std::shared_ptr<Font> font_;
};
}  // namespace Game
