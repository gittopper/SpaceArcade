#pragma once

#include <cstdint>
#include <vector>

#pragma pack(push, 1)

struct RGBAPixel {
    RGBAPixel() : r(0), g(0), b(0), a(0) {}
    RGBAPixel(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) :
        r(r), g(g), b(b), a(a) {}
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

class Sprite {
  public:
    enum Type { RGBA, RGB };
    Sprite(std::size_t width,
           std::size_t height,
           std::size_t gl_width,
           std::size_t gl_height,
           Type type,
           std::vector<char>&& data) :
        width_(width),
        height_(height),
        gl_width_(gl_width),
        gl_height_(gl_height),
        type_(type),
        data_(std::move(data)) {}
    std::size_t width() const {
        return width_;
    }
    std::size_t height() const {
        return height_;
    }
    std::size_t glWidth() const {
        return gl_width_;
    }
    std::size_t glHeight() const {
        return gl_height_;
    }
    const char* data() const {
        return data_.data();
    }
    Type type() const {
        return type_;
    }

  private:
    std::size_t width_;
    std::size_t height_;
    std::size_t gl_width_;
    std::size_t gl_height_;
    Type type_;
    std::vector<char> data_;
};
