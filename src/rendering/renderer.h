//
//  renderer.h
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 20/10/14.
//
//

#ifndef __SpaceArcade__renderer__
#define __SpaceArcade__renderer__

#include <string>

#include <game/resourceloader.h>

using namespace std;

#pragma pack(push, 1)

struct RGBAPixel {
    RGBAPixel():
    r(0), g(0), b(0), a(0){}
    RGBAPixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) : r(r), g(g), b(b), a(a) {}
    RGBAPixel(std::uint32_t c) {
        setColor(c);
    }
    void setColor(std::uint32_t c) {
        a = c % 256;
        b = (c >> 8) % 256;
        g = (c >> 16) % 256;
        r = (c >> 24) % 256;
    }
    std::uint8_t a;
    std::uint8_t b;
    std::uint8_t g;
    std::uint8_t r;
};

#pragma pack(pop)

class Renderer {
  public:
    virtual bool initRenderer(ResourceLoader* loader) = 0;

    virtual void createFramebuffer() = 0;
    virtual void destroyFramebuffer() = 0;
    virtual bool updateInfoAboutWindow() = 0;

    virtual void prepareFrame() = 0;
    virtual void drawSprite(
        int x, int y, int w, int h, int pixel_size, const RGBAPixel* sprite) = 0;
    virtual void showFrame() = 0;

    virtual void getScreeenSize(int& w, int& h) = 0;
    virtual void setScreeenSize(int w, int h) = 0;
    virtual void setScale(float s) = 0;

    virtual ~Renderer() {}
};
#endif /* defined(__SpaceArcade__renderer__) */
