#pragma once

#include <game/gameconfig.h>
#include <game/igame.h>
#include <game/level.h>
#include <game/overlay.h>
#include <game/resourceloader.h>
#include <game/timer.h>
#include <rendering/spacegamerenderer.h>

namespace Game {

class SpaceGame : public IGame {
  public:
    SpaceGame();

    void setupGame(int w, int h);

    void resize(int w, int h);

    void drag(int x, int y);

    void zoom(float zoom);

    void dragStart(int x1, int y1, int x2, int y2);
    void drag(int x1, int y1, int x2, int y2);
    void dragStop();

    void tap(int x, int y);

    LevelConfig* getLevelConfig() override {
        return &level_state_.config_;
    }
    void renderStep();
    void showFrame();
    void setRenderer(std::shared_ptr<SpaceGameRenderer> r) {
        renderer_ = r;
    }
    std::shared_ptr<SpaceGameRenderer> getRenderer() {
        return renderer_;
    }

    void gameOver() override;

    void pause();

    void resume();

    void step();

  private:
    void renderOverlay();
    void initLevel();

    Level level_state_;
    Overlay overlay_;
    double drag_start_;
    double internal_scale_start_;

    std::shared_ptr<SpaceGameRenderer> renderer_;
    Timer level_presentation_timer_;
    Timer level_pass_timer_;
};
}  // namespace Game
