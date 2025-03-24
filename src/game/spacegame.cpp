//
//  spacegame.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 19/10/14.
//
//

#include "spacegame.h"

#include <math.h>

using namespace Game;

using namespace std;

SpaceGame::SpaceGame() :
    paused_(false),
    collider_(&scene_),
    time_(0),
    asteroidsNextTime_(-1),
    renderer_(nullptr) {}

void SpaceGame::pause() {
    paused_ = true;
}

void SpaceGame::resume() {
    if (!gameLost_) {
        paused_ = false;
    }
}

void SpaceGame::setupGame(GameConfig conf) {
    config_ = conf;

    renderer_->setScale(config_.scale_);
    renderer_->getScreeenSize(w_, h_);
    aspect_ = static_cast<float>(h_) / w_;
    scene_.setupScene(config_.scale_, aspect_ * config_.scale_);

    spaceship_ = new SpaceShip(config_.bulletSpeed_ * config_.dt_);
    scene_.addChild(spaceship_);

    spaceship_->scale(config_.shipSize_);
    spaceship_->move(Vector(
        0, -aspect_ * config_.scale_ / 2. +
               (spaceship_->getShift() - spaceship_->getBBox().getMin())[1]));

    asteroidsDelay_ = normal_distribution<float>(
        1 / config_.asteroidsAvgPerSec_,
        config_.asteroidsSigmaPerSec_ / config_.asteroidsAvgPerSec_);

    asteroidsSpeed_ = normal_distribution<float>(config_.asteroidsAvgSpeed_,
                                                 config_.asteroidsSigmaSpeed_);

    asteroidPlace_ =
        uniform_real_distribution<float>(-config_.scale_, config_.scale_);

    asteroidsSpeedAngle_ = normal_distribution<float>(
        0, config_.asteroidsSpeedAngleSigma_ / 180 * (atan(1) * 4));

    asteroidsSize_ = normal_distribution<float>(config_.asteroidAvgSize_,
                                                config_.asteroidAvgSize_ / 5);

    Asteroid::partsDistrib = normal_distribution<float>(
        config_.asteroidAvgPartsNumber_, config_.asteroidSigmaParts_);
    Asteroid::unevenDistrib =
        normal_distribution<float>(1, config_.asteroidUnevennessSigma_);

    RGBAPixel gre{0, 255, 0, 100};
    RGBAPixel yel{255, 255, 0, 100};
    RGBAPixel red{255, 0, 0, 100};
    RGBAPixel tra{0, 0, 0, 0};
    std::vector<RGBAPixel> mario{
            tra, tra, tra, red, red, red, red, red, tra, tra, tra, tra,
            tra, tra, red, red, red, red, red, red, red, red, red, tra,
            tra, tra, gre, gre, gre, yel, yel, gre, yel, tra, tra, tra,
            tra, gre, yel, gre, yel, yel, yel, gre, yel, yel, yel, tra,
            tra, gre, yel, gre, gre, yel, yel, gre, gre, yel, yel, yel,
            tra, gre, gre, yel, yel, yel, yel, gre, gre, gre, gre, tra,
            tra, tra, tra, yel, yel, yel, yel, yel, yel, yel, tra, tra,
            tra, tra, gre, gre, red, gre, gre, red, tra, tra, tra, tra,
            tra, gre, gre, gre, red, gre, gre, red, gre, gre, gre, tra,
            gre, gre, gre, gre, red, red, red, red, gre, gre, gre, gre,
            yel, yel, gre, red, yel, red, red, yel, red, gre, yel, yel,
            yel, yel, yel, red, red, red, red, red, red, yel, yel, yel,
            yel, yel, red, red, red, red, red, red, red, red, yel, yel,
            tra, tra, red, red, red, tra, tra, red, red, red, tra, tra,
            tra, gre, gre, gre, tra, tra, tra, tra, gre, gre, gre, tra,
            gre, gre, gre, gre, tra, tra, tra, tra, gre, gre, gre, gre,
    };

    test_sprite_ = mario;

    IObject::game = this;
}

void SpaceGame::drag(int x, int y) {
    Vector impact =
        Vector(x * config_.scale_ / w_, -y * config_.scale_ / w_) * config_.dt_;
    if (impact.len() > config_.maxSpaceShipSpeed_ * config_.dt_) {
        impact = impact.normalized() * config_.maxSpaceShipSpeed_ * config_.dt_;
    }
    spaceship_->getV() = impact;
}

void SpaceGame::tap(int x, int y) {
    spaceship_->shoot();
    if (gameLost_) {
        gameLost_ = false;
        setupGame(config_);
        resume();
    }
}

void SpaceGame::gameOver() {
    pause();
    gameLost_ = true;
}

void SpaceGame::renderStep() {
    renderer_->prepareFrame();

    if (!paused_) {
        if (asteroidsNextTime_ < time_) {
            createAsteroid();

            asteroidsNextTime_ = time_ + asteroidsDelay_(generator_);
        }

        scene_.visitAll(collider_);
        removePostponed(&scene_);

        for (ObjectsSet::const_iterator it = objectsToAdd_.begin();
             it != objectsToAdd_.end(); it++) {
            scene_.addChild(*it);
        }
        objectsToAdd_.clear();

        scene_.visitAll(physics_);

        time_ += config_.dt_;
    }
    scene_.visitAll(*renderer_);

    renderer_->drawSprite(0, 0, 12, 16, 1, test_sprite_.data());
    renderer_->showFrame();
}

void SpaceGame::showFrame()  {
    renderer_->showFrame();
}
void SpaceGame::addGameObject(class IObject* o) {
    objectsToAdd_.insert(o);
}

void SpaceGame::createAsteroid() {
    IObject* asteroid = new Asteroid;
    float size = asteroidsSize_(generator_);
    size = size < 0.1 ? 0.1 : size;
    asteroid->scale(size);

    asteroid->move(
        Vector(asteroidPlace_(generator_), config_.scale_ * aspect_ * 1.7, 0));
    float angle = asteroidsSpeedAngle_(generator_);
    asteroid->getV() =
        Vector((asteroidsSpeed_(generator_) - config_.asteroidsAvgSpeed_) *
                   config_.dt_ * sin(angle),
               -asteroidsSpeed_(generator_) * config_.dt_ * cos(angle), 0);

    scene_.addChild(asteroid);
}
