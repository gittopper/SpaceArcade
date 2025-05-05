//
//  glesspacegamerenderer.cpp
//  SpaceArcade
//
//  Created by Stanislav Fedorov on 21/10/14.
//
//

#include "glesspacegamerenderer.h"

#include "game/objects/gameobjects.h"
#include "math/gamemath.h"

using namespace Math;

namespace Game {
void GLESSpaceGameRenderer::visit(IObject& a) {
    drawGameObject(a);
}

void GLESSpaceGameRenderer::drawGameObject(IObject& obj) const {
    setPosition(obj.getTransform(), obj.getShift());
    drawArray(obj.getDrawPoints(), obj.getColors());
}
void GLESSpaceGameRenderer::setPosition(const Mat& m, const Vector& v) const {
    Mat44 objMat;
    convertTo44(objMat, m, v);

    Mat44 mvp;
    Mul(mvp, objMat, proj_);

    glUniformMatrix4fv(u_mvpHandle_, 1, GL_FALSE, (GLfloat*)&mvp.m_[0]);
}
void GLESSpaceGameRenderer::drawArray(VArray& points, V4Array& colors) const {
    glVertexAttribPointer(a_positionHandle_, 3, GL_FLOAT, GL_FALSE, 0,
                          &points[0]);
    glEnableVertexAttribArray(a_positionHandle_);
    glVertexAttribPointer(a_colorHandle_, 4, GL_FLOAT, GL_FALSE, 0, &colors[0]);
    glEnableVertexAttribArray(a_colorHandle_);
    glDrawArrays(GL_TRIANGLE_FAN, 0, (int)points.size());
}
void GLESSpaceGameRenderer::drawSprite(
    int x, int y, int w, int h, int pixel_size, const Color* sprite) {
    float scale = camera_->internalWidth() / camera_->width();
    float psize = pixel_size * scale;
    VArray points;
    V4Array colors;
    Mat tr{};
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            const auto& c = sprite[j * w + i];
            if (c.a == 0) {
                continue;
            }
            float pos_x =
                camera_->xLeft() + static_cast<float>(x + i) * psize;
            float pos_y = camera_->yTop() -
                          static_cast<float>(y + j + 1) * psize;
            Vector4 color{static_cast<float>(c.r) / 255.0f,
                          static_cast<float>(c.g) / 255.0f,
                          static_cast<float>(c.b) / 255.0f,
                          static_cast<float>(c.a) / 255.0f};
            colors.clear();
            points.clear();
            colors.push_back(color);
            colors.push_back(color);
            colors.push_back(color);
            colors.push_back(color);
            points.push_back(Vector{0, 0, 0.0});
            points.push_back(Vector{0,  psize, 0.0});
            points.push_back(
                Vector{psize,  psize, 0.0});
            points.push_back(Vector{ psize, 0, 0.0});
            Vector shift{pos_x ,  pos_y , 0.0};
            setPosition(tr, shift);
            drawArray(points, colors);
        }
    }
}
void GLESSpaceGameRenderer::drawOverlay(const Sprite& sprite) {
    drawOverlay(sprite.data(), sprite.glWidth(), sprite.glHeight());
}

void GLESSpaceGameRenderer::drawOverlay(const sf::Image& sprite) {
    const auto size = sprite.getSize();
    drawOverlay(sprite.getPixelsPtr(), size.x, size.y);
}

void GLESSpaceGameRenderer::drawOverlay(const void* data,
                                        int data_width,
                                        int data_height) {
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data_width, data_height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);


    float vertices[] = {
        camera_->xLeft(), camera_->yTop(), 0.f, camera_->xLeft(), camera_->yBottom(), 0.f,
        camera_->xRight(),  camera_->yTop(), 0.f, camera_->xRight(),  camera_->yBottom(), 0.f,
    };

    float texture[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};

    glUseProgram(program_overlay_id_);
    glVertexAttribPointer(overlay_vert_loc_, 3, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(overlay_vert_loc_);

    glVertexAttribPointer(overlay_tex_loc_, 2, GL_FLOAT, false, 0, texture);
    glEnableVertexAttribArray(overlay_tex_loc_);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_DST_ALPHA);
    glUniformMatrix4fv(overlay_mat_loc_, 1, GL_FALSE, (GLfloat*)&proj_.m_[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisable(GL_BLEND);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &texture_id);
}

}  // namespace Game
