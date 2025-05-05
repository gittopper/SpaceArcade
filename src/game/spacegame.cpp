#include <game/pngreader.h>
#include <game/spacegame.h>

#include <math.h>

namespace Game {

SpaceGame::SpaceGame() : level_state_(game_state_), overlay_(game_state_) {}

void SpaceGame::pause() {
    level_state_.pause();
    level_presentation_timer_.pause();
    level_pass_timer_.pause();
}

void SpaceGame::resume() {
    level_state_.resume();
    level_presentation_timer_.resume();
    level_pass_timer_.resume();
}

void SpaceGame::initLevel() {
    if (game_state_.num_lives_ == 0) {
        game_state_.num_lives_ = game_state_.config_.num_lives_;
        game_state_.num_level_ = 1;
        game_state_.num_exploded_asteroids = 0;
        game_state_.num_shoots = 0;
        game_state_.num_asteroids = 0;
        game_state_.time_.reset();
        level_state_.setupLevel(LevelConfig{});
        level_state_.pause();
        overlay_.state = Overlay::NewLevel;
        level_pass_timer_.reset();
        level_presentation_timer_.reset();
        level_presentation_timer_.start();
        return;
    }

    level_state_.setupLevel(level_state_.config_);
    overlay_.state = Overlay::Stats;
}

void SpaceGame::setupGame(int w, int h) {
    game_state_.camera_.setViewport(w, h);
    game_state_.camera_.setInternalWidth(game_state_.config_.internal_width_);
    getRenderer()->setCamera(&game_state_.camera_);
    overlay_.setup();
    IObject::game = this;
    initLevel();
    level_state_.pause();
    overlay_.state = Overlay::NewLevel;
    level_presentation_timer_.start();
}

void SpaceGame::drag(int x, int y) {
    level_state_.drag(x, y);
}

void SpaceGame::tap(int x, int y) {
    if (overlay_.state == Overlay::LiveLost) {
        if (overlay_.game_lost_rect_.isInside(x, y)) {
            level_pass_timer_.resume();
            initLevel();
        }
    } else {
        if (overlay_.state == Overlay::Stats) {
            level_state_.spaceship_->shoot();
        }
    }
}

void SpaceGame::gameOver() {
    game_state_.player_->play("ship_crash.ogg");
    level_state_.pause();
    level_pass_timer_.pause();
    overlay_.state = Overlay::LiveLost;
    if (game_state_.num_lives_ != 0) {
        --game_state_.num_lives_;
    }
}

void SpaceGame::resize(int w, int h) {
    game_state_.camera_.setViewport(w, h);
    level_state_.resize();
    overlay_.resize();
}
void SpaceGame::step() {
    if (level_pass_timer_.isRunning() &&
        level_pass_timer_.time() > level_state_.config_.level_pass_time_) {
        level_pass_timer_.stop();
        level_state_.pause();
        ++game_state_.num_level_;
        LevelConfig config = level_state_.config_;
        ++config.asteroid_avg_parts_number_;
        ++config.asteroids_avg_per_sec_;
        ++config.asteroids_avg_speed_;
        ++config.max_space_ship_speed_;
        ++config.bullet_speed_;
        level_state_.setupLevel(config);
        level_state_.pause();
        level_presentation_timer_.reset();
        level_presentation_timer_.start();
        overlay_.state = Overlay::NewLevel;
    }
    if (level_presentation_timer_.isRunning() &&
        level_presentation_timer_.time() >
            level_state_.config_.level_presentation_time_) {
        level_presentation_timer_.stop();
        overlay_.state = Overlay::Stats;
        level_state_.resume();
        level_pass_timer_.reset();
        level_pass_timer_.start();
    }
    level_state_.step();
}

void SpaceGame::renderStep() {
    renderer_->prepareFrame();
    step();
    level_state_.scene_.visitAll(*renderer_);
    overlay_.renderOverlay();
    if (nullptr != overlay_.overlay_) {
        renderer_->drawOverlay(*overlay_.overlay_);
    }
    renderer_->showFrame();
}

void SpaceGame::showFrame() {
    renderer_->showFrame();
}

}  // namespace Game
