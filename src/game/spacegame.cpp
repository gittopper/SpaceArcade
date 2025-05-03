#include <game/pngreader.h>
#include <game/spacegame.h>

#include <math.h>

namespace Game {

SpaceGame::SpaceGame() :
    paused_(false),
    collider_(&scene_),
    time_(0),
    asteroids_next_time_(-1),
    renderer_(nullptr),
    game_lost_(false),
    num_lives_(5) {}

void SpaceGame::pause() {
    paused_ = true;
}

void SpaceGame::resume() {
    if (!game_lost_) {
        paused_ = false;
    }
}

void SpaceGame::setupGame(GameConfig conf) {
    config_ = conf;

    renderer_->setScale(config_.scale_);
    renderer_->getScreeenSize(width_, height_);
    aspect_ = static_cast<float>(height_) / width_;
    scene_.setupScene(config_.scale_, aspect_ * config_.scale_);

    auto png_image = getResourceLoader()->readFile("daco.png");
    overlay_ = std::make_shared<Sprite>(PngReader::read(png_image, false));
    auto font_mem_file = getResourceLoader()->readFile("XI20.ttf");
    font_ = std::make_shared<Font>(font_mem_file);

    spaceship_ = new SpaceShip(config_.bulletSpeed_ * config_.dt_);
    scene_.addChild(spaceship_);

    spaceship_->scale(config_.shipSize_);
    spaceship_->move(Vector(
        0, -aspect_ * config_.scale_ / 2. +
               (spaceship_->getShift() - spaceship_->getBBox().getMin())[1]));

    asteroids_delay_ = normal_distribution<float>(
        1 / config_.asteroidsAvgPerSec_,
        config_.asteroidsSigmaPerSec_ / config_.asteroidsAvgPerSec_);

    asteroids_speed_ = normal_distribution<float>(config_.asteroidsAvgSpeed_,
                                                  config_.asteroidsSigmaSpeed_);

    asteroid_place_ =
        uniform_real_distribution<float>(-config_.scale_, config_.scale_);

    asteroids_speed_angle_ = normal_distribution<float>(
        0, config_.asteroidsSpeedAngleSigma_ / 180 * (atan(1) * 4));

    asteroids_size_ = normal_distribution<float>(config_.asteroidAvgSize_,
                                                 config_.asteroidAvgSize_ / 5);

    Asteroid::partsDistrib = normal_distribution<float>(
        config_.asteroidAvgPartsNumber_, config_.asteroidSigmaParts_);
    Asteroid::unevenDistrib =
        normal_distribution<float>(1, config_.asteroidUnevennessSigma_);

    IObject::game = this;
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
    overlay_->copy(game_lost_ ? *overlay_dark_ : *overlay_transparent_);
    if (game_lost_) {
        auto text =
            Font::convertToUtf32(num_lives_ > 0 ? "TRY AGAIN" : "GAME LOST");
        font_->setFontSize(100);
        font_->setColor(num_lives_ > 0 ? Color{0, 255, 0, 155}
                                       : Color{255, 0, 0, 155});
        auto rect = font_->getTextRect(text);
        auto text_y = height_ / 2 - rect.height / 2;
        auto text_x = width_ / 2 - rect.width / 2;
        font_->renderText(*overlay_, text_x, text_y, text);
    }
    auto text =
        Font::convertToUtf32("num lives: " + std::to_string(num_lives_));
    font_->setFontSize(40);
    font_->setColor(Color{0, 0, 0, 255});
    font_->renderText(*overlay_, 10, 10, text);
}

void SpaceGame::drag(int x, int y) {
    Vector impact =
        Vector(x * config_.scale_ / width_, -y * config_.scale_ / width_) *
        config_.dt_;
    if (impact.len() > config_.maxSpaceShipSpeed_ * config_.dt_) {
        impact = impact.normalized() * config_.maxSpaceShipSpeed_ * config_.dt_;
    }
    spaceship_->getV() = impact;
}

void SpaceGame::tap(int x, int y) {
    spaceship_->shoot();
    if (game_lost_) {
        game_lost_ = false;
        if (num_lives_ == 0) {
            num_lives_ = 5;
        }
        setupGame(config_);
        resume();
    }
}

void SpaceGame::gameOver() {
    pause();
    player()->play("ship_crash.ogg");
    game_lost_ = true;
    num_lives_ = num_lives_ > 0 ? num_lives_ - 1 : 0;
}

void SpaceGame::renderStep() {
    renderer_->prepareFrame();

    if (!paused_) {
        if (asteroids_next_time_ < time_) {
            createAsteroid();

            asteroids_next_time_ = time_ + asteroids_delay_(generator_);
        }

        scene_.visitAll(collider_);
        removePostponed(&scene_);

        for (ObjectsSet::const_iterator it = objects_to_add_.begin();
             it != objects_to_add_.end(); it++) {
            scene_.addChild(*it);
        }
        objects_to_add_.clear();

        scene_.visitAll(physics_);

        time_ += config_.dt_;
    }
    scene_.visitAll(*renderer_);

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

    asteroid->move(
        Vector(asteroid_place_(generator_), config_.scale_ * aspect_ * 1.7, 0));
    float angle = asteroids_speed_angle_(generator_);
    asteroid->getV() =
        Vector((asteroids_speed_(generator_) - config_.asteroidsAvgSpeed_) *
                   config_.dt_ * sin(angle),
               -asteroids_speed_(generator_) * config_.dt_ * cos(angle), 0);

    scene_.addChild(asteroid);
}
}  // namespace Game
