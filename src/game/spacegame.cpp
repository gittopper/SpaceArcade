#include <game/pngreader.h>
#include <game/spacegame.h>

#include <math.h>

namespace Game {

SpaceGame::SpaceGame() :
    paused_(false),
    collider_(&scene_),
    asteroids_next_time_(-1),
    renderer_(nullptr),
    game_lost_(false),
    num_lives_(0) {
    time_.start();
}

void SpaceGame::pause() {
    paused_ = true;
}

void SpaceGame::resume() {
    if (!game_lost_) {
        paused_ = false;
    }
}

void SpaceGame::clearScene() {
    scene_.removeChildren();
    spaceship_ = nullptr;
}

void SpaceGame::initLevel() {
    game_lost_ = false;
    clearScene();
    if (num_lives_ == 0) {
        num_lives_ = config_.num_lives_;
        num_level_ = 1;
        game_timer_.reset();
        stats = {};
        config_ = GameConfig();
        level_presentation_timer_.reset();
        level_presentation_timer_.start();
        level_pass_timer_.reset();
        return;
    }
    level_pass_timer_.start();
    game_timer_.start();
    paused_ = false;
    spaceship_ = new SpaceShip(config_.bullet_speed_);
    scene_.addChild(spaceship_);

    spaceship_->scale(config_.ship_size_);
    spaceship_->move(Vector(
        0, -aspect() * config_.scale_ / 2. +
               (spaceship_->getShift() - spaceship_->getBBox().getMin())[1]));

    asteroids_delay_ = normal_distribution<float>(
        1 / config_.asteroids_avg_per_sec_,
        config_.asteroids_sigma_per_sec_ / config_.asteroids_avg_per_sec_);

    asteroids_speed_ = normal_distribution<float>(
        config_.asteroids_avg_speed_, config_.asteroids_sigma_speed_);

    asteroid_place_ =
        uniform_real_distribution<float>(-config_.scale_, config_.scale_);

    asteroids_speed_angle_ = normal_distribution<float>(
        0, config_.asteroids_speed_angle_sigma_ / 180 * (atan(1) * 4));

    asteroids_size_ = normal_distribution<float>(
        config_.asteroid_avg_size_, config_.asteroid_avg_size_ / 5);

    Asteroid::parts_distrib = normal_distribution<float>(
        config_.asteroid_avg_parts_number_, config_.asteroid_sigma_parts_);
    Asteroid::uneven_distrib =
        normal_distribution<float>(1, config_.asteroid_unevenness_sigma_);
}

float SpaceGame::aspect() const {
    return static_cast<float>(height_) / width_;
}

void SpaceGame::setupGame(int w, int h) {
    config_ = GameConfig();
    getRenderer()->setScreeenSize(w, h);
    renderer_->setScale(config_.scale_);
    width_ = w;
    height_ = h;
    scene_.setupScene(config_.scale_, aspect() * config_.scale_);

    auto font_mem_file = getResourceLoader()->readFile("XI20.ttf");
    font_ = std::make_shared<Font>(font_mem_file);

    IObject::game = this;
    level_presentation_timer_.start();
}

void SpaceGame::renderOverlay() {
    if (nullptr == overlay_ || overlay_->width() != width_ ||
        overlay_->height() != height_) {
        overlay_transparent_ =
            std::make_shared<Sprite>(width_, height_, Color(0, 0, 0, 0));
        overlay_dark_ =
            std::make_shared<Sprite>(width_, height_, Color(0, 0, 0, 150));
        overlay_ = std::make_shared<Sprite>(width_, height_, Color(0, 0, 0, 0));
    }
    overlay_->copy(game_lost_ || level_presentation_timer_.isRunning()
                       ? *overlay_dark_
                       : *overlay_transparent_);
    if (game_lost_ || level_presentation_timer_.isRunning()) {
        std::string str = num_lives_ > 0 ? "TRY AGAIN" : "GAME LOST";
        if (level_presentation_timer_.isRunning()) {
            str = "LEVEL " + std::to_string(num_level_);
        }
        auto text = Font::convertToUtf32(str);
        font_->setFontSize(100);
        Color green{0, 255, 0, 255};
        Color red{255, 0, 0, 255};
        font_->setColor(num_lives_ > 0 || level_presentation_timer_.isRunning()
                            ? green
                            : red);
        auto rect = font_->getTextRect(text);
        rect.x = width_ / 2 - rect.width / 2;
        rect.y = height_ / 2 - rect.height / 2;
        font_->renderText(*overlay_, rect.x, rect.y, text);
        game_lost_rect_ = rect;
    }
    if (!level_presentation_timer_.isRunning()) {
        font_->setFontSize(40);
        font_->setColor(Color{0, 0, 0, 255});
        auto text_y = 10;
        auto num_lives =
            Font::convertToUtf32("num lives: " + std::to_string(num_lives_));
        font_->renderText(*overlay_, 10, text_y, num_lives);
        auto font_shift = font_->getTextRect(num_lives).height + 10;
        text_y += font_shift;
        auto elapsed_time = Font::convertToUtf32(
            "elapsed time: " + game_timer_.elapsedAsString(false));
        font_->renderText(*overlay_, 10, text_y, elapsed_time);
        text_y += font_shift;
        auto num_exploded_asteroids =
            Font::convertToUtf32("num shooted asteroids: " +
                                 std::to_string(stats.num_exploded_asteroids));
        font_->renderText(*overlay_, 10, text_y, num_exploded_asteroids);
        text_y += font_shift;
        auto num_shoots = Font::convertToUtf32(
            "num shoots: " + std::to_string(stats.num_shoots));
        font_->renderText(*overlay_, 10, text_y, num_shoots);
        text_y += font_shift;
        auto num_asteroids = Font::convertToUtf32(
            "num asteroids: " + std::to_string(stats.num_asteroids));
        font_->renderText(*overlay_, 10, text_y, num_asteroids);
    }
}

void SpaceGame::drag(int x, int y) {
    if (nullptr == spaceship_) {
        return;
    }
    Vector impact =
        Vector(x * config_.scale_ / width_, -y * config_.scale_ / width_);
    if (impact.len() > config_.max_space_ship_speed_) {
        impact = impact.normalized() * config_.max_space_ship_speed_;
    }
    spaceship_->getV() = impact;
}

void SpaceGame::tap(int x, int y) {
    if (game_lost_) {
        if (game_lost_rect_.isInside(x, y)) {
            initLevel();
        }
    } else {
        if (nullptr != spaceship_) {
            spaceship_->shoot();
        }
    }
}

void SpaceGame::gameOver() {
    pause();
    player()->play("ship_crash.ogg");
    game_lost_ = true;
    game_timer_.stop();
    level_pass_timer_.stop();
    if (num_lives_ != 0) {
        --num_lives_;
    }
}

void SpaceGame::resize(int w, int h) {
    width_ = w;
    height_ = h;
    getRenderer()->setScreeenSize(width_, height_);
    scene_.setupScene(config_.scale_, aspect() * config_.scale_);
    if (spaceship_) {
        spaceship_->getShift() = spaceship_->getShift() +
                                 spaceship_->getBBox().clamp(scene_.getBBox());
    }
}
void SpaceGame::step() {
    if (level_pass_timer_.isRunning() &&
        level_pass_timer_.time() > config_.level_pass_time_) {
        level_pass_timer_.stop();
        game_timer_.stop();
        ++num_level_;
        ++config_.asteroid_avg_parts_number_;
        ++config_.asteroids_avg_per_sec_;
        ++config_.asteroids_avg_speed_;
        ++config_.max_space_ship_speed_;
        ++config_.bullet_speed_;
        level_presentation_timer_.reset();
        level_presentation_timer_.start();
        paused_ = true;
        level_pass_timer_.reset();
    }
    if (level_presentation_timer_.isRunning() &&
        level_presentation_timer_.time() > config_.level_presentation_time_) {
        level_presentation_timer_.stop();
        initLevel();
        paused_ = false;
    }
    if (!paused_) {
        if (asteroids_next_time_ < time_.time()) {
            createAsteroid();

            asteroids_next_time_ = time_.time() + asteroids_delay_(generator_);
        }

        scene_.visitAll(collider_);
        removePostponed(&scene_);

        for (auto& object_to_add : objects_to_add_) {
            scene_.addChild(object_to_add);
        }
        objects_to_add_.clear();
        auto cur_time = time_.time();
        auto dt = cur_time - last_update_time_;
        last_update_time_ = cur_time;
        physics_.setDt(dt > 1 ? 0 : dt);
        scene_.visitAll(physics_);
    }
    scene_.visitAll(*renderer_);
}

void SpaceGame::renderStep() {
    renderer_->prepareFrame();
    step();
    renderOverlay();
    if (overlay_) {
        renderer_->drawOverlay(*overlay_);
    }
    renderer_->showFrame();
}

void SpaceGame::showFrame() {
    renderer_->showFrame();
}
void SpaceGame::addGameObject(class IObject* o) {
    objects_to_add_.insert(o);
}

void SpaceGame::createAsteroid() {
    IObject* asteroid = new Asteroid;
    float size = asteroids_size_(generator_);
    size = size < 0.1 ? 0.1 : size;
    asteroid->scale(size);
    asteroid->move(Vector(asteroid_place_(generator_),
                          config_.scale_ * aspect() * 1.7, 0));
    float angle = asteroids_speed_angle_(generator_);
    asteroid->getV() =
        Vector((asteroids_speed_(generator_) - config_.asteroids_avg_speed_) *
                   sin(angle),
               -asteroids_speed_(generator_) * cos(angle), 0);

    scene_.addChild(asteroid);
}
}  // namespace Game
