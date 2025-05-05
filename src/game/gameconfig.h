#pragma once

namespace Game {
struct GameConfig {
    int num_lives_ = 5;
    float internal_width_ = 10;
};

struct LevelConfig {
    // screen width length in relative points

    float ship_size_ = 1.;

    float asteroids_avg_per_sec_ = 3.;
    float asteroids_sigma_per_sec_ = 1.;
    float asteroid_avg_size_ = 0.5;

    int asteroid_avg_parts_number_ = 4;
    int asteroid_sigma_parts_ = 4;

    float asteroid_unevenness_sigma_ = 0.2;

    bool collide_with_asteroid_parts_ = true;
    bool mark_exploded_ = true;

    float asteroids_avg_speed_ = 4.;
    float asteroids_sigma_speed_ = 1.;

    // in degreees
    float asteroids_speed_angle_sigma_ = 10.;

    float bullet_speed_ = 4;
    float max_space_ship_speed_ = 4;
    float level_presentation_time_ = 3;
    float level_pass_time_ = 20;
};

}  // namespace Game
