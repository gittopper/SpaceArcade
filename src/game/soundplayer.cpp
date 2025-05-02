
#include "soundplayer.h"

SoundPlayer::SoundPlayer(ResourceLoaderPtr resource_loader) {
    auto add_sound = [this,
                      &resource_loader](const std::string sound_file_name) {
        auto msound = resource_loader->readFile(sound_file_name);
        sf::SoundBuffer buffer;
        buffer.loadFromMemory(msound.data(), msound.size());
        sounds_.emplace(sound_file_name, std::move(buffer));
    };
    add_sound("shoot.ogg");
    add_sound("small_explode.ogg");
    add_sound("big_explode.ogg");
}

void SoundPlayer::play(const std::string& sound_file_name) {
    if (sounds_.find(sound_file_name) == sounds_.end()) {
        throw std::runtime_error("no sound " + sound_file_name);
    }
    for (auto it = playing_sounds_.begin(); it != playing_sounds_.end();) {
        if (it->getStatus() == sf::Sound::Status::Stopped) {
            it = playing_sounds_.erase(it);
        } else {
            ++it;
        }
    }
    sf::Sound sound(sounds_[sound_file_name]);
    playing_sounds_.emplace_back(std::move(sound));
    playing_sounds_.back().play();
}
