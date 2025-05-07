#include <game/objects/perk.h>

namespace Game {

Perk::Perk(Type type) {
    if (type == Live) {
        points_.push_back(Vector(847, 29));
        points_.push_back(Vector(813, 112));
        points_.push_back(Vector(717, 194));
        points_.push_back(Vector(597, 359));
        points_.push_back(Vector(624, 437));
        points_.push_back(Vector(717, 496));
        points_.push_back(Vector(800, 484));
        points_.push_back(Vector(847, 429));

        points_.push_back(Vector(881, 484));
        points_.push_back(Vector(977, 496));
        points_.push_back(Vector(1097, 437));
        points_.push_back(Vector(1070, 359));
        points_.push_back(Vector(977, 194));
        points_.push_back(Vector(894, 112));
        points_.push_back(Vector(847, 29));

        color_ = Vector(1, 0, 0);
        normalize();
    }
}


}
