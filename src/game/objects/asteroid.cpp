//
//  asteroid.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#include "asteroid.h"

#include <algorithm>

#include "spaceship.h"
using namespace Math;
#include "game/gameconfig.h"

namespace Game {
normal_distribution<float> Asteroid::colorDistrib(0.5, 0.25);
uniform_real_distribution<float> Asteroid::explosionDistib(0., 1.);
normal_distribution<float> Asteroid::partsDistrib(0.5, 0.25);

normal_distribution<float> Asteroid::unevenDistrib;

default_random_engine Asteroid::generator;

Asteroid::Asteroid() : piece(false) {
    float PI2 = (atan(1) * 8);

    int n = 7;

    for (int i = 0; i < n; i++) {
        float angle = PI2 / n * i;
        float radius = unevenDistrib(generator);
        radius = radius < 0 ? 0.1 : radius;

        points_.push_back(Vector(radius * cos(angle), radius * sin(angle)));
    }
    /*
            points.push_back(Vector(0., 0.));
            points.push_back(Vector(0, 1.));
            points.push_back(Vector(1, 1.));
            points.push_back(Vector(1,0.));
    */

    points_.push_back(points_[0]);

    normalize();

    for (int i = 0; i < colors_.size(); i++) {
        float grey = getRandColorComponent();
        colors_[i] = Vector4(grey, grey, grey, 1);
    }
}

float Asteroid::getRandColorComponent() {
    float r = colorDistrib(generator);
    r = fmax(r, 0.);
    r = fmin(r, 1.);
    return r;
}

void Asteroid::explode() {
    shouldBeRemoved = true;
    if (piece) {
        return;
    }

    int n = partsDistrib(generator);

    vector<float> masses, angles, energy;

    getNormalizedRandArray(masses, n);
    getNormalizedRandArray(angles, n);
    getNormalizedRandArray(energy, n);

    float sum = 0;
    for (int i = 0; i < n; i++) {
        energy[i] *= masses[i];
        sum += energy[i];
    }

    float velNorm = velocity_.len();
    float PI2 = (atan(1) * 8);
    float angle = 0;
    for (int i = 0; i < n; i++) {
        energy[i] /= sum;

        float vecNorm = sqrtf(energy[i]);
        angle += angles[i] * PI2;

        Asteroid* asteroid = new Asteroid;
        asteroid->getV() =
            Vector(sin(angle), cos(angle)) * vecNorm * velNorm + velocity_;
        asteroid->scale(pow(masses[i], 1 / 3.) * radius_);
        asteroid->move(shift_);
        asteroid->setParted();

        game->addGameObject(asteroid);
    }
}

void Asteroid::getNormalizedRandArray(vector<float>& vals, int num) {
    vals.clear();
    float sum = 0;
    for (int i = 0; i < num; i++) {
        float cur = explosionDistib(generator);
        vals.push_back(cur);
        sum += cur;
    }
    for (int i = 0; i < num; i++) {
        vals[i] /= sum;
    }
}

void Asteroid::setParted() {
    piece = true;
    for (int i = 0; i < colors_.size(); i++) {
        colors_[i][2] = 0;
    }
}

}  // namespace Game
