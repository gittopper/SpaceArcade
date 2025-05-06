#include <desktop/openglrenderer.h>

#include "game/objects/gameobjects.h"
#include "math/gamemath.h"
#include <GL/gl.h>
#include <GLES3/gl3.h>
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
                    p[1] * obj.getTransform().el(0, 1) + obj.getShift()[0]),
                   (p[0] * obj.getTransform().el(1, 0) +
                    p[1] * obj.getTransform().el(1, 1) + obj.getShift()[1]));
    }
    glEnd();
}

OpenGLRenderer::OpenGLRenderer() {}

void OpenGLRenderer::createFramebuffer() {}

void OpenGLRenderer::destroyFramebuffer() {}

bool OpenGLRenderer::updateInfoAboutWindow() {
    return true;
}

void OpenGLRenderer::prepareFrame() {
    glClear(GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT);  // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, camera_->width(), camera_->height());
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);  // устанавливаем матрицу
    glLoadIdentity();            // загружаем матрицу
    glOrtho(camera_->xLeft(), camera_->xRight(), camera_->yBottom(),
            camera_->yTop(), 1,
            0);  // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::drawSprite(
    int x, int y, int w, int h, int pixel_size, const Color* sprite) {
    auto pix_size = static_cast<float>(pixel_size) / camera_->width() *
                    camera_->internalWidth();
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            double pos_x =
                camera_->xLeft() + static_cast<double>((x + i)) * pix_size;
            double pos_y =
                camera_->yBottom() + static_cast<double>((y + j)) * pix_size;
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

bool OpenGLRenderer::initRenderer(ResourceLoader* loader) {
    return true;
}
void OpenGLRenderer::drawOverlay(const Sprite& sprite) {
    assert(sprite.type() == Sprite::RGBA);
    drawOverlayRGBA(sprite.data(), sprite.glWidth(), sprite.glHeight());
}

void OpenGLRenderer::drawOverlay(const sf::Image& sprite) {
    const auto size = sprite.getSize();
    drawOverlayRGBA(reinterpret_cast<const char*>(sprite.getPixelsPtr()),
                    size.x, size.y);
}

void OpenGLRenderer::drawOverlayRGBA(const void* data,
                                     int data_width,
                                     int data_height) {
    glEnable(GL_TEXTURE_2D);
    GLuint overlay_id;
    glGenTextures(1, &overlay_id);
    glBindTexture(GL_TEXTURE_2D, overlay_id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data_width, data_height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // glGenerateMipmap(GL_TEXTURE_2D);
    GLfloat verts3[] = {
        camera_->xLeft(),  camera_->yBottom(), -0.5f,
        camera_->xRight(), camera_->yBottom(), -0.5f,
        camera_->xRight(), camera_->yTop(),    -0.5f,
        camera_->xLeft(),  camera_->yTop(),    -0.5f,
    };
    GLfloat texCoords[] = {
        0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    };
    GLuint indices3[] = {0, 1, 2, 3};
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, verts3);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
                        GL_ONE_MINUS_DST_ALPHA);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, indices3);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
    glDeleteTextures(1, &overlay_id);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}

}  // namespace Game
