#pragma once

#include <game/isoundplayer.h>
#include <game/resourceloader.h>

#include <list>
#include <map>

#include <SFML/Audio.hpp>

class SoundPlayer : public ISoundPlayer {
  public:
    SoundPlayer(ResourceLoaderPtr resource_loader);
    void play(const std::string& sound_file_name) override;

  private:
    std::map<std::string, sf::SoundBuffer> sounds_;
    std::list<sf::Sound> playing_sounds_;
};
