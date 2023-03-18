#include <rendering/openglrenderer.h>

#include <QtOpenGL>

#include "game/objects/gameobjects.h"
#include "math/gamemath.h"

using namespace Math;

namespace Game {
void OpenGLRenderer::visit(IObject &a) { drawGameObject(a); }

void OpenGLRenderer::drawGameObject(IObject &obj) const {
  glBegin(GL_POLYGON);
  for (size_t i = 0; i < obj.getDrawPoints().size(); ++i) {
    auto c = obj.getColors()[i];
    auto p = obj.getDrawPoints()[i];
    glColor3f(c[0], c[1], c[2]); // Цвет курсора
    // Координаты курсора
    glVertex2f((p[0] * obj.getTransform().el(0, 0) +
                p[1] * obj.getTransform().el(0, 1) + obj.getShift()[0]) *
                   width / scale,
               (p[0] * obj.getTransform().el(1, 0) +
                p[1] * obj.getTransform().el(1, 1) + obj.getShift()[1]) *
                   height / scale);
  }
  glEnd();
}

OpenGLRenderer::OpenGLRenderer() {}

void OpenGLRenderer::createFramebuffer() {}

void OpenGLRenderer::destroyFramebuffer() {}

bool OpenGLRenderer::updateInfoAboutWindow() {}

void OpenGLRenderer::prepareFrame() {
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
  glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
  glLoadIdentity();            // загружаем матрицу
  glOrtho(-width / 2, width / 2, height / 2, -height / 2, 1,
          0); // подготавливаем плоскости для матрицы
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLRenderer::showFrame() {}

void OpenGLRenderer::getScreeenSize(int &w, int &h) {
  w = width;
  h = height;
}

void OpenGLRenderer::setScreeenSize(int &w, int &h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, (GLint)w, (GLint)h);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  width = w;
  height = h;
}

void OpenGLRenderer::setScale(float s) { scale = s; }

bool OpenGLRenderer::initRenderer(ResourceLoader *loader) {}

} // namespace Game
