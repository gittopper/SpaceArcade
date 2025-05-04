#pragma once

#include <game/iobject.h>

#include <cmath>
#include <random>
using namespace std;

namespace Game {

class Asteroid : public IObject {
  public:
    struct AsteroidConfig {
        AsteroidConfig() : asteroid_explosion_sigma(0.2) {}
        double asteroid_explosion_sigma;
    } conf;

    Asteroid();

    GAME_OBJECT(Asteroid)

    void visit(SpaceShip& s);

    void explode();

    virtual void accept(Visitor& visitor) {
        visitor.visit(*this);
    }

    static normal_distribution<float> parts_distrib;
    static normal_distribution<float> uneven_distrib;

    void setParted();
    bool isParted() {
        return piece;
    }

  protected:
    bool piece;

    static default_random_engine generator;
    static normal_distribution<float> color_distrib;
    static uniform_real_distribution<float> explosion_distib;

    float getRandColorComponent();

    void getNormalizedRandArray(vector<float>& vals, int num);
};
}  // namespace Game
