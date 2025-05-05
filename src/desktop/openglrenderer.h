#pragma once

#include <game/objects/gameobjects.h>
#include <rendering/spacegamerenderer.h>

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

    void setCamera(Camera* camera) override {
        camera_ = camera;
    }

    bool initRenderer(ResourceLoader* loader) override;
    void drawSprite(int x,
                    int y,
                    int w,
                    int h,
                    int pixel_size,
                    const Color* sprite) override;
    void drawOverlay(const Sprite& sprite) override;
    void drawOverlay(const sf::Image& sprite) override;

  protected:
    void drawOverlayRGBA(const void* data, int data_width, int data_height);

    void drawGameObject(IObject& obj) const;
    Camera* camera_ = nullptr;
};
}  // namespace Game
