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
#include <string>

#include <SFML/Graphics/Font.hpp>

namespace Game {

class SpaceGame : public IGame {
  public:
    struct LevelState {
        LevelState(GameStateData& game_data) : game_data_(&game_data) {}

        void setupLevel(const LevelConfig& level_config) {
            clearScene();
            config_ = level_config;
            asteroids_next_time_ = game_data_->time_.time();
            level_pass_timer_.start();
            game_data_->time_.start();
            scene_.setupScene(game_data_->camera_.internalWidth(),
                              game_data_->camera_.internalHeight());
            spaceship_ = new SpaceShip(config_.bullet_speed_);
            scene_.addChild(spaceship_);

            spaceship_->scale(config_.ship_size_);
            spaceship_->getV() = {};
            spaceship_->move(
                Vector(0, scene_.getBBox().getMin()[1] +
                              (spaceship_->getShift() -
                               spaceship_->getBBox().getMin())[1]));
            asteroids_delay_ =
                normal_distribution<float>(1 / config_.asteroids_avg_per_sec_,
                                           config_.asteroids_sigma_per_sec_ /
                                               config_.asteroids_avg_per_sec_);

            asteroids_speed_ = normal_distribution<float>(
                config_.asteroids_avg_speed_, config_.asteroids_sigma_speed_);

            asteroid_place_ = uniform_real_distribution<float>(
                game_data_->camera_.xLeft(), game_data_->camera_.xRight());

            asteroids_speed_angle_ = normal_distribution<float>(
                0, config_.asteroids_speed_angle_sigma_ / 180 * (atan(1) * 4));

            asteroids_size_ = normal_distribution<float>(
                config_.asteroid_avg_size_, config_.asteroid_avg_size_ / 5);

            Asteroid::parts_distrib =
                normal_distribution<float>(config_.asteroid_avg_parts_number_,
                                           config_.asteroid_sigma_parts_);
            Asteroid::uneven_distrib = normal_distribution<float>(
                1, config_.asteroid_unevenness_sigma_);
        }

        ~LevelState() {
            clearScene();
        }
        void clearScene() {
            scene_.removeChildren();
            spaceship_ = nullptr;
        }
        void pause() {
            level_pass_timer_.pause();
            game_data_->time_.pause();
        }
        void resume() {
            level_pass_timer_.resume();
            game_data_->time_.resume();
        }
        void drag(int x, int y) {
            Vector impact =
                Vector(x, -y) * (game_data_->camera_.internalWidth() /
                                 game_data_->camera_.width());
            if (impact.len() > config_.max_space_ship_speed_) {
                impact = impact.normalized() * config_.max_space_ship_speed_;
            }
            spaceship_->getV() = impact;
        }
        void step() {
            if (!game_data_->time_.isRunning()) {
                return;
            }
            if (asteroids_next_time_ < game_data_->time_.time()) {
                createAsteroid();

                asteroids_next_time_ = game_data_->time_.time() +
                                       asteroids_delay_(game_data_->generator_);
            }
            Collider collider(&scene_);
            scene_.visitAll(collider);
            removePostponed(&scene_, spaceship_);

            auto cur_time = game_data_->time_.time();
            auto dt = cur_time - last_update_time_;
            last_update_time_ = cur_time;
            Physics physics;
            physics.setDt(dt > 1 ? 0 : dt);
            scene_.visitAll(physics);
        }
        void resize() {
            scene_.setupScene(game_data_->camera_.internalWidth(),
                              game_data_->camera_.internalHeight());
            if (spaceship_) {
                spaceship_->getShift() =
                    spaceship_->getShift() +
                    spaceship_->getBBox().clamp(scene_.getBBox());
            }
        }
        void createAsteroid() {
            IObject* asteroid = new Asteroid;
            float size = asteroids_size_(game_data_->generator_);
            size = size < 0.1 ? 0.1 : size;
            asteroid->scale(size);
            asteroid->move(Vector(asteroid_place_(game_data_->generator_),
                                  game_data_->camera_.internalHeight(), 0));
            float angle = asteroids_speed_angle_(game_data_->generator_);
            asteroid->getV() = Vector(
                (asteroids_speed_(game_data_->generator_) -
                 config_.asteroids_avg_speed_) *
                    sin(angle),
                -asteroids_speed_(game_data_->generator_) * cos(angle), 0);

            scene_.addChild(asteroid);
        }
        bool isFinished() const {
            return level_pass_timer_.time() > config_.level_pass_time_;
        }
        GameStateData* game_data_;
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

    class Overlay {
      public:
        enum State { NewLevel, Stats, LiveLost };
        State state = Stats;
        Rect2D game_lost_rect_;
        std::shared_ptr<Sprite> overlay_;
        Overlay(GameStateData& game_data) : game_data_(&game_data) {}
        void setup() {
            auto font_mem_file =
                game_data_->resource_loader_->readFile("XI20.ttf");
            font_ = std::make_shared<Font>(font_mem_file);
            resize();
        }
        void resize() {
            int w = game_data_->camera_.width();
            int h = game_data_->camera_.height();
            if (nullptr != overlay_ && overlay_->width() == w &&
                overlay_->height() == h) {
            }
            overlay_transparent_ =
                std::make_shared<Sprite>(w, h, Color(0, 0, 0, 0));
            overlay_dark_ = std::make_shared<Sprite>(w, h, Color(0, 0, 0, 150));
            overlay_ = std::make_shared<Sprite>(w, h, Color(0, 0, 0, 0));
        }

        void renderOverlay() {
            overlay_->copy(state == NewLevel || state == LiveLost
                               ? *overlay_dark_
                               : *overlay_transparent_);
            if (state == NewLevel || state == LiveLost) {
                std::string str =
                    game_data_->num_lives_ > 0 ? "TRY AGAIN" : "GAME LOST";
                if (state == NewLevel) {
                    str = "LEVEL " + std::to_string(game_data_->num_level_);
                }
                auto text = Font::convertToUtf32(str);
                font_->setFontSize(100);
                Color green{0, 255, 0, 255};
                Color red{255, 0, 0, 255};
                font_->setColor(game_data_->num_lives_ > 0 || state == NewLevel
                                    ? green
                                    : red);
                auto rect = font_->getTextRect(text);
                rect.x = game_data_->camera_.width() / 2 - rect.width / 2;
                rect.y = game_data_->camera_.height() / 2 - rect.height / 2;
                font_->renderText(*overlay_, rect.x, rect.y, text);
                game_lost_rect_ = rect;
            }
            font_->setFontSize(40);
            font_->setColor(Color{0, 0, 0, 255});
            auto text_y = 10;
            auto num_lives = Font::convertToUtf32(
                "num lives: " + std::to_string(game_data_->num_lives_));
            font_->renderText(*overlay_, 10, text_y, num_lives);
            auto font_shift = font_->getTextRect(num_lives).height + 10;
            text_y += font_shift;
            auto elapsed_time = Font::convertToUtf32(
                "elapsed time: " + game_data_->time_.elapsedAsString(false));
            font_->renderText(*overlay_, 10, text_y, elapsed_time);
            text_y += font_shift;
            auto num_exploded_asteroids = Font::convertToUtf32(
                "num shooted asteroids: " +
                std::to_string(game_data_->num_exploded_asteroids));
            font_->renderText(*overlay_, 10, text_y, num_exploded_asteroids);
            text_y += font_shift;
            auto num_shoots = Font::convertToUtf32(
                "num shoots: " + std::to_string(game_data_->num_shoots));
            font_->renderText(*overlay_, 10, text_y, num_shoots);
            text_y += font_shift;
            auto num_asteroids = Font::convertToUtf32(
                "num asteroids: " + std::to_string(game_data_->num_asteroids));
            font_->renderText(*overlay_, 10, text_y, num_asteroids);
        }

      private:
        std::shared_ptr<Sprite> overlay_transparent_;
        std::shared_ptr<Sprite> overlay_dark_;

        std::shared_ptr<Font> font_;
        GameStateData* game_data_;
    };

    SpaceGame();

    void setupGame(int w, int h);

    void resize(int w, int h);

    void drag(int x, int y);

    void tap(int x, int y);

    LevelConfig* getLevelConfig() override {
        return &level_state_.config_;
    }
    void renderStep();
    void showFrame();
    void setRenderer(SpaceGameRenderer* r) {
        renderer_ = r;
    }
    Renderer* getRenderer() {
        return renderer_;
    }

    void gameOver() override;

    void pause();

    void resume();

    void step();

  private:
    void renderOverlay();
    void initLevel();

    LevelState level_state_;
    Overlay overlay_;

    SpaceGameRenderer* renderer_ = nullptr;
    Timer level_presentation_timer_;
    Timer level_pass_timer_;
};
}  // namespace Game
