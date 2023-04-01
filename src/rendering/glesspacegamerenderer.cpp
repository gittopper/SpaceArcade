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
void GLESSpaceGameRenderer::visit(IObject& a) { drawGameObject(a); }

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
}  // namespace Game
