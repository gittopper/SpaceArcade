#include <game/collider.h>
#include <game/level.h>
#include <game/objects/asteroid.h>
#include <game/physics.h>

namespace Game {

void Level::setupLevel(const LevelConfig& level_config) {
    clearScene();
    config_ = level_config;
    asteroids_next_time_ = game_data_.time_.time();
    scene_.setupScene(game_data_.camera_.internalWidth(),
                      game_data_.camera_.internalHeight());
    spaceship_ = new SpaceShip(config_.bullet_speed_);
    scene_.addChild(spaceship_);

    spaceship_->scale(config_.ship_size_);
    spaceship_->getV() = {};
    spaceship_->move(Vector(
        0, scene_.getBBox().getMin()[1] +
               (spaceship_->getShift() - spaceship_->getBBox().getMin())[1]));
    asteroids_delay_ = normal_distribution<float>(
        1 / (config_.asteroids_avg_per_sec_ * game_data_.camera_.internalWidth()),
        config_.asteroids_sigma_per_sec_);
    live_perk_delay_ = normal_distribution<float>(
        1 / (config_.live_perk_settings.avg_per_sec_ * game_data_.camera_.internalWidth()),
        config_.live_perk_settings.sigma_per_sec_);
    live_perk_next_time_ = game_data_.time_.time() + live_perk_delay_(game_data_.generator_);

    asteroids_speed_ = normal_distribution<float>(
        config_.asteroids_avg_speed_, config_.asteroids_sigma_speed_);

    asteroid_place_ = uniform_real_distribution<float>(
        game_data_.camera_.xLeft(), game_data_.camera_.xRight());

    asteroids_speed_angle_ = normal_distribution<float>(
        0, config_.asteroids_speed_angle_sigma_ / 180 * (atan(1) * 4));

    asteroids_size_ = normal_distribution<float>(
        config_.asteroid_avg_size_, config_.asteroid_avg_size_ / 5);

    Asteroid::parts_distrib = normal_distribution<float>(
        config_.asteroid_avg_parts_number_, config_.asteroid_sigma_parts_);
    Asteroid::uneven_distrib =
        normal_distribution<float>(1, config_.asteroid_unevenness_sigma_);
}

Level::~Level() {
    clearScene();
}
void Level::clearScene() {
    scene_.removeChildren();
    spaceship_ = nullptr;
}
void Level::pause() {
    game_data_.time_.pause();
}
void Level::resume() {
    game_data_.time_.resume();
}
void Level::drag(int x, int y) {
    Vector impact = Vector(x, -y) * (game_data_.camera_.internalWidth() /
                                     game_data_.camera_.width());
    if (impact.len() > config_.max_space_ship_speed_) {
        impact = impact.normalized() * config_.max_space_ship_speed_;
    }
    spaceship_->getV() = impact;
}
void Level::step() {
    if (!game_data_.time_.isRunning()) {
        return;
    }
    if (asteroids_next_time_ < game_data_.time_.time()) {
        createAsteroid();

        asteroids_next_time_ =
            game_data_.time_.time() + asteroids_delay_(game_data_.generator_);
    }
    if (live_perk_next_time_ < game_data_.time_.time()) {
        createLivePerk();
        live_perk_next_time_ = game_data_.time_.time() + live_perk_delay_(game_data_.generator_);
    }
    Collider collider(&scene_);
    scene_.visitAll(collider);
    removePostponed(&scene_);

    auto cur_time = game_data_.time_.time();
    auto dt = cur_time - last_update_time_;
    last_update_time_ = cur_time;
    Physics physics;
    physics.setDt(dt > 1 ? 0 : dt);
    scene_.visitAll(physics);
}
void Level::resize() {
    scene_.setupScene(game_data_.camera_.internalWidth(),
                      game_data_.camera_.internalHeight());
    if (spaceship_) {
        spaceship_->getShift() = spaceship_->getShift() +
                                 spaceship_->getBBox().clamp(scene_.getBBox());
    }
}
void Level::setInternalWidth(float internal_scale) {
    game_data_.camera_.setInternalWidth(internal_scale);
    resize();
    asteroid_place_ = uniform_real_distribution<float>(
        game_data_.camera_.xLeft(), game_data_.camera_.xRight());
}
void Level::createAsteroid() {
    IObject* asteroid = new Asteroid;
    float size = asteroids_size_(game_data_.generator_);
    size = size < 0.1 ? 0.1 : size;
    asteroid->scale(size);
    asteroid->move(Vector(asteroid_place_(game_data_.generator_),
                          game_data_.camera_.internalHeight(), 0));
    float angle = asteroids_speed_angle_(game_data_.generator_);
    asteroid->getV() =
        Vector((asteroids_speed_(game_data_.generator_) -
                config_.asteroids_avg_speed_) *
                   sin(angle),
               -asteroids_speed_(game_data_.generator_) * cos(angle), 0);

    scene_.addChild(asteroid);
}
void Level::createLivePerk() {
    IObject* live_perk = new Perk(Perk::Live);

    live_perk->scale(config_.live_perk_settings.size);
    live_perk->move(Vector(asteroid_place_(game_data_.generator_),
                          game_data_.camera_.internalHeight(), 0));
    float angle = asteroids_speed_angle_(game_data_.generator_);
    live_perk->getV() =
        Vector((asteroids_speed_(game_data_.generator_) -
                config_.asteroids_avg_speed_) *
                   sin(angle),
               -asteroids_speed_(game_data_.generator_) * cos(angle), 0);

    scene_.addChild(live_perk);
}

}  // namespace Game
