#include <QtOpenGL>

#include <desktop/openglrenderer.h>

#include "game/objects/gameobjects.h"
#include "math/gamemath.h"

using namespace Math;

namespace Game {
void OpenGLRenderer::visit(IObject& a) {
    drawGameObject(a);
}

void OpenGLRenderer::drawGameObject(IObject& obj) const {
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < obj.getDrawPoints().size(); ++i) {
        auto c = obj.getColors()[i];
        auto p = obj.getDrawPoints()[i];
        glColor3f(c[0], c[1], c[2]);  // Цвет курсора
        // Координаты курсора
        glVertex2f((p[0] * obj.getTransform().el(0, 0) +
                    p[1] * obj.getTransform().el(0, 1) + obj.getShift()[0]) *
                       width_ / scale_,
                   (p[0] * obj.getTransform().el(1, 0) +
                    p[1] * obj.getTransform().el(1, 1) + obj.getShift()[1]) *
                       width_ / scale_);
    }
    glEnd();
}

OpenGLRenderer::OpenGLRenderer() {
}

void OpenGLRenderer::createFramebuffer() {}

void OpenGLRenderer::destroyFramebuffer() {}

bool OpenGLRenderer::updateInfoAboutWindow() {
    return true;
}

void OpenGLRenderer::prepareFrame() {
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);  // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_MODELVIEW);  // устанавливаем матрицу
    glLoadIdentity();             // загружаем матрицу
    glOrtho(-width_ / 2, width_ / 2, height_ / 2, -height_ / 2, 1,
            0);  // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::drawSprite(
    int x, int y, int w, int h, int pixel_size, const RGBAPixel* sprite) {
    for(int i = 0; i < w; ++i) {
        for(int j = 0; j < h; ++j) {
            double pos_x = -width_/2 + static_cast<double>((x + i)) * pixel_size;
            double pos_y = -height_/2 + static_cast<double>((y + j)) * pixel_size;
            const auto& c = sprite[j * w + i];
            glColor4f(c.r / 255.0, c.g / 255.0, c.b / 255.0, c.a / 255.0);
            glBegin(GL_QUADS);
            glVertex2f(pos_x, pos_y);
            glVertex2f(pos_x + pixel_size, pos_y);
            glVertex2f(pos_x + pixel_size, pos_y + pixel_size);
            glVertex2f(pos_x, pos_y + pixel_size);
            glEnd();
        }
    }
}

void OpenGLRenderer::showFrame() {}

void OpenGLRenderer::getScreeenSize(int& w, int& h) {
    w = width_;
    h = height_;
}

void OpenGLRenderer::setScreeenSize(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)w, (GLint)h);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    width_ = w;
    height_ = h;
}

void OpenGLRenderer::setScale(float s) {
    scale_ = s;
}

bool OpenGLRenderer::initRenderer(ResourceLoader* loader) {
    return true;
}

void OpenGLRenderer::drawOverlay(const Sprite& sprite) {
    assert(sprite.type() == Sprite::RGBA);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glDeleteTextures(1, &overlay_id_);
    glGenTextures(1, &overlay_id_);
    glBindTexture(GL_TEXTURE_2D, overlay_id_);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sprite.glWidth(), sprite.glHeight(), 0,
            GL_RGBA, GL_UNSIGNED_BYTE, sprite.data());

    glColor4f(1., 1., 1., 0.5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //glGenerateMipmap(GL_TEXTURE_2D);
    float width = width_ / 2;
    float height = height_ / 2;
    GLfloat verts3[] = {
        -width, -height, 0.0f,
        width, -height, 0.0f,
        width, height, 0.0f,
        -width, height, 0.0f,
    };
    GLfloat texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
    };
    GLuint indices3[] = {
        0, 1, 2, 3
    };
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);

    glVertexPointer  (3, GL_FLOAT, 0, verts3);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, indices3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glBindTexture(GL_TEXTURE_2D, 0);
    //glDisable(GL_TEXTURE_2D);
}


}  // namespace Game
