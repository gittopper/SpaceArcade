#ifndef PNGREADER_H
#define PNGREADER_H
#include <game/sprite.h>

class PngReader {
  public:
    static Sprite read(const std::vector<char>& buffer, bool gl_arrange);
};

#endif  // PNGREADER_H
