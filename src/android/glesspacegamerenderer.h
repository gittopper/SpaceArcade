#pragma once

#include <game/objects/gameobjects.h>
#include <rendering/spacegamerenderer.h>

#include <android/glesrenderer.h>

#include <SFML/Graphics/Image.hpp>

namespace Game {
class GLESSpaceGameRenderer :
    virtual public SpaceGameRenderer,
    virtual public GLESRenderer {
  public:
    void visit(IObject&) override;

  protected:
    void drawGameObject(IObject& obj) const;
    void setPosition(const Mat& m, const Vector& v) const;
    void drawArray(VArray& points, V4Array& colors) const;
    void drawSprite(int x,
                    int y,
                    int w,
                    int h,
                    int pixel_size,
                    const RGBAPixel* sprite) override;
    void drawOverlay(const Sprite& sprite) override;
    void drawOverlay(const sf::Image& sprite) override;
    void drawOverlay(const void* data, int data_width, int data_height);
};
}  // namespace Game
