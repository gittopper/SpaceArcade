#pragma once

#include "game/objects/gameobjects.h"
#include "spacegamerenderer.h"

namespace Game {
class OpenGLRenderer : public SpaceGameRenderer {
   public:
    OpenGLRenderer();
    void visit(IObject&) override;
    void createFramebuffer() override;
    void destroyFramebuffer() override;
    bool updateInfoAboutWindow() override;

    void prepareFrame() override;
    void showFrame() override;

    void getScreeenSize(int& w, int& h) override;
    void setScreeenSize(int w, int h) override;
    void setScale(float s) override;

    bool initRenderer(ResourceLoader* loader) override;

   protected:
    void drawGameObject(IObject& obj) const;
    int width_ = 500;
    int height_ = 500;
    double scale_;
};
}  // namespace Game
