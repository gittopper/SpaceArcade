#include "pngreader.h"
extern "C" {
#include <png.h>
}
#include <cstring>

namespace {

struct image {
    png_uint_32 imWidth, imHeight; //реальный размер картинки
    png_uint_32 glWidth, glHeight; //размер который подойдет для OpenGL
    int bit_depth, color_type;
    char* data; //данные RGB/RGBA
};
int reNpot(int w) {
    //поддерживает ли OpenGL текстуры размера не кратным двум
    //эту переменную конечно надо определять один раз при старте проги с помощью
    //String s = gl.glGetString(GL10.GL_EXTENSIONS);
    //NON_POWER_OF_TWO_SUPPORTED = s.contains("texture_2D_limited_npot") || s.contains("texture_npot") || s.contains("texture_non_power_of_two");
    bool NON_POWER_OF_TWO_SUPPORTED = false;
    if (NON_POWER_OF_TWO_SUPPORTED) {
        if (w % 2) w++;
    } else {
        if (w <= 4) w = 4;
        else if (w <= 8) w = 8;
        else if (w <= 16) w = 16;
        else if (w <= 32) w = 32;
        else if (w <= 64) w = 64;
        else if (w <= 128) w = 128;
        else if (w <= 256) w = 256;
        else if (w <= 512) w = 512;
        else if (w <= 1024) w = 1024;
        else if (w <= 2048) w = 2048;
        else if (w <= 4096) w = 4096;
    }
    return w;
}
struct mypng {
    unsigned int pos;//текущая позиция в массиве
    unsigned int length;//длинна массива
    const char* data;//массив содержащий сжатую картинку
};

void userReadData(png_structp png_ptr, png_bytep data, png_size_t length) {
    //получаем ссылку на структуру
    mypng* png = (mypng*) png_get_io_ptr(png_ptr);
    //смотрим чтобы не вылезти за края массива
    if (png->pos + length > png->length) {
        length += png->pos-png->length;
    }
    if (length > 0) {
        //копируем данные из массива
        memcpy(data, png->data + png->pos, length);
        //двигаем текущую позицию
        png->pos += length;
    }
}

image readPng(const char* data, unsigned int length, bool gl_arrange) {
    image im;
    //пропускаем заголовок, хотя именно сюда можно добавить проверку PNG это или JPEG, чтобы ф-ция сама определяла как грузить картинку

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    png_infop info_ptr = png_create_info_struct(png_ptr);

    mypng png = { 8, length, data };
    png_init_io(png_ptr, (FILE*) &png);
    png_set_read_fn(png_ptr, png_get_io_ptr(png_ptr), userReadData);

    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    //читаем данные о картинке
    png_get_IHDR(png_ptr, info_ptr, &im.imWidth, &im.imHeight, &im.bit_depth, &im.color_type, nullptr, nullptr, nullptr);

    //определяем размер картинки подходящий для OpenGL
    im.glWidth = gl_arrange ? reNpot(im.imWidth) : im.imWidth;
    im.glHeight = gl_arrange ? reNpot(im.imHeight) : im.imHeight;

    //если картинка содержит прозрачность то на каждый пиксель 4 байта (RGBA), иначе 3 (RGB)
    int row = im.glWidth * (im.color_type == PNG_COLOR_TYPE_RGBA ? 4 : 3);
    im.data = new char[row * im.glHeight];

    //в этом массиве содержатся указатели на начало каждой строки
    png_bytep * row_pointers = new png_bytep[im.imHeight];
    for(int i = 0; i < im.imHeight; ++i)
        row_pointers[i] = (png_bytep) (im.data + i * row);

    //читаем картинку
    png_read_image(png_ptr, row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    delete[] row_pointers;

    return im;
}

}

Sprite PngReader::read(const std::vector<char>& buffer, bool gl_arrange) {
    image img = readPng(buffer.data(), buffer.size(), gl_arrange);
    bool is_4b = img.color_type == PNG_COLOR_TYPE_RGBA;
    std::size_t bytes_per_pixel = is_4b ? 4 : 3;
    std::vector<char> data(img.data, img.data + img.glHeight * img.glWidth * bytes_per_pixel);
    Sprite sprite(img.imWidth, img.imHeight, img.glWidth, img.glHeight, (is_4b ? Sprite::RGBA: Sprite::RGB), std::move(data));
    delete[] img.data;
    return sprite;
}
