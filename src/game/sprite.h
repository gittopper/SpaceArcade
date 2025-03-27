#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

class Sprite {
public:
    enum Type {
        RGBA,
        RGB
    };
    Sprite(std::size_t width, std::size_t height,
           std::size_t gl_width, std::size_t gl_height,
           Type type, std::vector<char>&& data):
        width_(width),
        height_(height),
        gl_width_(gl_width),
        gl_height_(gl_height),
        type_(type),
        data_(std::move(data))
    {}
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
    Type type() const {return type_;}
private:
    std::size_t width_;
    std::size_t height_;
    std::size_t gl_width_;
    std::size_t gl_height_;
    Type type_;
    std::vector<char> data_;
};

#endif // SPRITE_H
