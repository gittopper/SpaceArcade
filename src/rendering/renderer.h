#pragma once

#include <game/resourceloader.h>
#include <game/sprite.h>

#include <string>

#include <SFML/Graphics/Image.hpp>

class Renderer {
  public:
    virtual bool initRenderer(ResourceLoader* loader) = 0;

    virtual void createFramebuffer() = 0;
    virtual void destroyFramebuffer() = 0;
    virtual bool updateInfoAboutWindow() = 0;

    virtual void prepareFrame() = 0;
    virtual void drawSprite(int x,
                            int y,
                            int w,
                            int h,
                            int pixel_size,
                            const RGBAPixel* sprite) = 0;
    virtual void drawOverlay(const Sprite& sprite) = 0;
    virtual void drawOverlay(const sf::Image& sprite) = 0;

    virtual void showFrame() = 0;

    virtual void getScreeenSize(int& w, int& h) = 0;
    virtual void setScreeenSize(int w, int h) = 0;
    virtual void setScale(float s) = 0;

    virtual ~Renderer() {}
};
