#pragma once

#include <QOpenGLWidget>
#include <QTimer>
#include <QtOpenGL>

class MainWindow : public QOpenGLWidget {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = 0);

  protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent* ke) override;
    void mouseMoveEvent(QMouseEvent* me) override;
    void mousePressEvent(QMouseEvent* me) override;
    void wheelEvent(QWheelEvent* we) override;
    void mouseReleaseEvent(QMouseEvent* me) override;

    int point;
    int gdx, gdy;
    int cax, cay, cbx, cby;
    bool singling;
  protected slots:
    void render();  // Определяем координаты объектов
};
