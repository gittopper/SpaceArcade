#include <game/overlay.h>

namespace Game {

Overlay::Overlay(IGame::GameStateData& game_data) : game_data_(game_data) {}
void Overlay::setup() {
    auto font_mem_file = game_data_.resource_loader_->readFile("XI20.ttf");
    font_ = std::make_shared<Font>(font_mem_file);
    resize();
}
void Overlay::resize() {
    int w = game_data_.camera_.width();
    int h = game_data_.camera_.height();
    if (nullptr != overlay_ && overlay_->width() == w &&
        overlay_->height() == h) {
    }
    overlay_transparent_ = std::make_shared<Sprite>(w, h, Color(0, 0, 0, 0));
    overlay_dark_ = std::make_shared<Sprite>(w, h, Color(0, 0, 0, 150));
    overlay_ = std::make_shared<Sprite>(w, h, Color(0, 0, 0, 0));
}

void Overlay::renderOverlay() {
    overlay_->copy(state == NewLevel || state == LiveLost
                       ? *overlay_dark_
                       : *overlay_transparent_);
    if (state == NewLevel || state == LiveLost) {
        std::string str = game_data_.num_lives_ > 0 ? "TRY AGAIN" : "GAME LOST";
        if (state == NewLevel) {
            str = "LEVEL " + std::to_string(game_data_.num_level_);
        }
        auto text = Font::convertToUtf32(str);
        font_->setFontSize(100);
        Color green{0, 255, 0, 255};
        Color red{255, 0, 0, 255};
        font_->setColor(game_data_.num_lives_ > 0 || state == NewLevel ? green
                                                                       : red);
        auto rect = font_->getTextRect(text);
        rect.x = game_data_.camera_.width() / 2 - rect.width / 2;
        rect.y = game_data_.camera_.height() / 2 - rect.height / 2;
        font_->renderText(*overlay_, rect.x, rect.y, text);
        game_lost_rect_ = rect;
    }
    font_->setFontSize(40);
    font_->setColor(Color{0, 0, 0, 255});
    auto text_y = 10;
    auto num_lives = Font::convertToUtf32(
        "num lives: " + std::to_string(game_data_.num_lives_));
    font_->renderText(*overlay_, 10, text_y, num_lives);
    auto font_shift = font_->getTextRect(num_lives).height + 10;
    text_y += font_shift;
    auto elapsed_time = Font::convertToUtf32(
        "elapsed time: " + game_data_.time_.elapsedAsString(false));
    font_->renderText(*overlay_, 10, text_y, elapsed_time);
    text_y += font_shift;
    auto num_exploded_asteroids =
        Font::convertToUtf32("num shooted asteroids: " +
                             std::to_string(game_data_.num_exploded_asteroids));
    font_->renderText(*overlay_, 10, text_y, num_exploded_asteroids);
    text_y += font_shift;
    auto num_shoots = Font::convertToUtf32(
        "num shoots: " + std::to_string(game_data_.num_shoots));
    font_->renderText(*overlay_, 10, text_y, num_shoots);
    text_y += font_shift;
    auto num_asteroids = Font::convertToUtf32(
        "num asteroids: " + std::to_string(game_data_.num_asteroids));
    font_->renderText(*overlay_, 10, text_y, num_asteroids);
}
}  // namespace Game
