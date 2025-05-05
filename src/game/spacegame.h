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

    void tap(int x, int y);

    LevelConfig* getLevelConfig() override {
        return &level_state_.config_;
    }
    void renderStep();
    void showFrame();
    void setRenderer(SpaceGameRenderer* r) {
        renderer_ = r;
    }
    Renderer* getRenderer() {
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

    SpaceGameRenderer* renderer_ = nullptr;
    Timer level_presentation_timer_;
    Timer level_pass_timer_;
};
}  // namespace Game
