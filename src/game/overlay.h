#pragma once

#include <game/font.h>
#include <game/igame.h>
#include <game/sprite.h>

#include <memory>

#include <SFML/Graphics/Font.hpp>

namespace Game {

class Overlay {
  public:
    enum State { NewLevel, Stats, LiveLost };
    State state = Stats;
    Rect2D game_lost_rect_;
    std::shared_ptr<Sprite> overlay_;
    Overlay(IGame::GameStateData& game_data);
    void setup();
    void resize();

    void renderOverlay();

  private:
    std::shared_ptr<Sprite> overlay_transparent_;
    std::shared_ptr<Sprite> overlay_dark_;

    std::shared_ptr<Font> font_;
    IGame::GameStateData& game_data_;
};
}  // namespace Game
