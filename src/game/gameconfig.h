#pragma once

namespace Game {
struct GameConfig {
    GameConfig() :
        scale_(10),
        ship_size_(1.),
        asteroids_avg_per_sec_(3.),
        asteroids_sigma_per_sec_(1.),
        asteroid_avg_size_(0.5),
        asteroid_avg_parts_number_(4),
        asteroid_sigma_parts_(0),
        asteroid_unevenness_sigma_(0.2),
        collide_with_asteroid_parts_(true),
        mark_exploded_(true),
        asteroids_avg_speed_(4.),
        asteroids_sigma_speed_(1.),
        asteroids_speed_angle_sigma_(10.),
        bullet_speed_(4),
        max_space_ship_speed_(4),
        level_presentation_time_(3),
        level_pass_time_(60) {}

    // screen width length in relative points
    float scale_;

    float ship_size_;

    float asteroids_avg_per_sec_;
    float asteroids_sigma_per_sec_;
    float asteroid_avg_size_;

    int asteroid_avg_parts_number_;
    int asteroid_sigma_parts_;

    float asteroid_unevenness_sigma_;

    bool collide_with_asteroid_parts_;
    bool mark_exploded_;

    float asteroids_avg_speed_;
    float asteroids_sigma_speed_;

    // in degreees
    float asteroids_speed_angle_sigma_;

    float bullet_speed_;
    float max_space_ship_speed_;
    float level_presentation_time_;
    float level_pass_time_;
};
}  // namespace Game
