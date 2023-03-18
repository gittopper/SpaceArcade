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

SpaceGame::SpaceGame()
    : paused(false),
      collider(&scene),
      time(0),
      asteroidsNextTime(-1),
      renderer(nullptr) {}

void SpaceGame::pause() { paused = true; }

void SpaceGame::resume() {
  if (!gameLost) {
    paused = false;
  }
}

void SpaceGame::setupGame(GameConfig conf) {
  config = conf;

  renderer->setScale(config.scale);
  renderer->getScreeenSize(w, h);
  aspect = (float)h / w;
  scene.setupScene(config.scale, aspect * config.scale);

  spaceship = new SpaceShip(config.bulletSpeed * config.dt);
  scene.addChild(spaceship);

  spaceship->scale(config.shipSize);
  spaceship->move(Vector(
      0, -aspect * config.scale / 2. +
             (spaceship->getShift() - spaceship->getBBox().getMin())[1]));

  asteroidsDelay = normal_distribution<float>(
      1 / config.asteroidsAvgPerSec,
      config.asteroidsSigmaPerSec / config.asteroidsAvgPerSec);

  asteroidsSpeed = normal_distribution<float>(config.asteroidsAvgSpeed,
                                              config.asteroidsSigmaSpeed);

  asteroidPlace = uniform_real_distribution<float>(-config.scale, config.scale);

  asteroidsSpeedAngle = normal_distribution<float>(
      0, config.asteroidsSpeedAngleSigma / 180 * (atan(1) * 4));

  asteroidsSize = normal_distribution<float>(config.asteroidAvgSize,
                                             config.asteroidAvgSize / 5);

  Asteroid::partsDistrib = normal_distribution<float>(
      config.asteroidAvgPartsNumber, config.asteroidSigmaParts);
  Asteroid::unevenDistrib =
      normal_distribution<float>(1, config.asteroidUnevennessSigma);

  IObject::game = this;
}

void SpaceGame::drag(int x, int y) {
  Vector impact =
      Vector(x * config.scale / w, -y * config.scale / w) * config.dt;
  if (impact.len() > config.maxSpaceShipSpeed * config.dt) {
    impact = impact.normalized() * config.maxSpaceShipSpeed * config.dt;
  }
  spaceship->getV() = impact;
}

void SpaceGame::tap(int x, int y) {
  spaceship->shoot();
  if (gameLost) {
    gameLost = false;
    setupGame(config);
    resume();
  }
}

void SpaceGame::gameOver() {
  pause();
  gameLost = true;
}

void SpaceGame::renderStep() {
  renderer->prepareFrame();

  if (!paused) {
    if (asteroidsNextTime < time) {
      createAsteroid();

      asteroidsNextTime = time + asteroidsDelay(generator);
    }

    scene.visitAll(collider);
    removePostponed(&scene);

    for (ObjectsSet::const_iterator it = objectsToAdd.begin();
         it != objectsToAdd.end(); it++) {
      scene.addChild(*it);
    }
    objectsToAdd.clear();

    scene.visitAll(physics);

    time += config.dt;
  }
  scene.visitAll(*renderer);

  renderer->showFrame();
}

void SpaceGame::addGameObject(class IObject* o) { objectsToAdd.insert(o); }

void SpaceGame::createAsteroid() {
  IObject* asteroid = new Asteroid;
  float size = asteroidsSize(generator);
  size = size < 0.1 ? 0.1 : size;
  asteroid->scale(size);

  asteroid->move(
      Vector(asteroidPlace(generator), config.scale * aspect / 1.7, 0));
  float angle = asteroidsSpeedAngle(generator);
  asteroid->getV() =
      Vector((asteroidsSpeed(generator) - config.asteroidsAvgSpeed) *
                 config.dt * sin(angle),
             -asteroidsSpeed(generator) * config.dt * cos(angle), 0);

  scene.addChild(asteroid);
}
