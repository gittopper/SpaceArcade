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

    void getScreeenSize(int& w, int& h) override;
    void setScreeenSize(int w, int h) override;
    void setScale(float s) override;

    bool initRenderer(ResourceLoader* loader) override;
    void drawSprite(int x,
                    int y,
                    int w,
                    int h,
                    int pixel_size,
                    const RGBAPixel* sprite) override;
    void drawOverlay(const Sprite& sprite) override;
    void drawOverlay(const sf::Image& sprite) override;

  protected:
    void drawOverlayRGBA(const char* data, int data_width, int data_height);

    void drawGameObject(IObject& obj) const;
    int width_ = 500;
    int height_ = 500;
    double scale_;
    GLuint overlay_id_;
};
}  // namespace Game
