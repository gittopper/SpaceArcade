#include <game/font.h>

#include <cassert>
#include <cuchar>
#include <stdexcept>

Font::Font(std::vector<char> font_ttf_data, int font_size) :
    font_ttf_data_(std::move(font_ttf_data)) {
    if (FT_Init_FreeType(&library_)) {
        throw std::runtime_error("FT_Init_FreeType failed");
    }
    if (FT_New_Memory_Face(library_,
                           reinterpret_cast<FT_Byte*>(font_ttf_data_.data()),
                           font_ttf_data_.size(), 0, &face_)) {
        throw std::runtime_error("FT_Init_FreeType failed");
    }
    setFontSize(font_size);
}

void Font::setFontSize(int font_size) {
    FT_Set_Char_Size(face_, font_size << 6, font_size << 6, 64, 64);
}

void Font::renderText(Sprite& sprite,
                      std::size_t x,
                      std::size_t y,
                      const UString& text) {
    auto cur_x = x;
    auto ascender = face_->size->metrics.ascender >> 6;
    const auto transparency = color_.a / 255.;
    for (auto& symbol : text) {
        FT_UInt glyph_index = FT_Get_Char_Index(face_, symbol);
        if (FT_Load_Glyph(face_, glyph_index, FT_LOAD_RENDER)) {
            throw std::runtime_error("FT_Load_Glyph failed");
        }
        FT_Bitmap* bitmap = &(face_->glyph->bitmap);
        auto glyph_x = cur_x + face_->glyph->bitmap_left;
        auto glyph_y = y + ascender - face_->glyph->bitmap_top;
        for (auto c = 0; c < bitmap->width; ++c) {
            for (auto r = 0; r < bitmap->rows; ++r) {
                auto gray = bitmap->buffer[r * bitmap->pitch + c];
                auto color = color_;
                color.a = gray * transparency;
                if (color.a < 255) {
                    auto sprite_color =
                        sprite.getPixel(glyph_x + c, glyph_y + r);
                    color.blend(sprite_color);
                }
                if (gray > 0) {
                    sprite.setPixel(glyph_x + c, glyph_y + r, color);
                }
            }
        }
        cur_x += (face_->glyph->advance.x >> 6);
    }
}
Rect2D Font::getTextRect(const UString& text) {
    Rect2D rect{};
    auto ascender = face_->size->metrics.ascender >> 6;
    auto descender = face_->size->metrics.descender >> 6;
    rect.height = ascender - descender;
    for (auto& symbol : text) {
        FT_UInt glyph_index = FT_Get_Char_Index(face_, symbol);
        if (FT_Load_Glyph(face_, glyph_index, FT_LOAD_RENDER)) {
            throw std::runtime_error("FT_Load_Glyph failed");
        }
        FT_Bitmap* bitmap = &(face_->glyph->bitmap);
        auto glyph_x = face_->glyph->bitmap_left;
        auto glyph_y = ascender - face_->glyph->bitmap_top;
        auto glyph_advance = face_->glyph->advance.x >> 6;
        auto glyph_width = bitmap->width;
        auto glyph_height = bitmap->rows;
        assert(rect.height >= glyph_y + glyph_height);
        assert(glyph_advance + 1 >= glyph_x + glyph_width);
        rect.width += (face_->glyph->advance.x >> 6);
    }
    return rect;
}
UString Font::convertToUtf32(const std::string& text) {
    UString result;
    std::mbstate_t state{};
    for (const auto& c : text) {
        char32_t c32;
        std::mbrtoc32(&c32, &c, 1, &state);
        result.push_back(c32);
    }
    return result;
}
