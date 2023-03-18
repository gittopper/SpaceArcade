#pragma once

#include <QGLWidget>
#include <QTimer>
#include <QtOpenGL>

class MainWindow : public QGLWidget {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);

protected:
  void initializeGL(); // Метод для инициализирования opengl
  void resizeGL(
      int nWidth,
      int nHeight); // Метод вызываемый после каждого изменения размера окна
  void paintGL(); // Метод для вывода изображения на экран
  void
  keyPressEvent(QKeyEvent *ke); // Для перехвата нажатия клавиш на клавиатуре
  void
  mouseMoveEvent(QMouseEvent *me); // Метод реагирует на перемещение указателя,
                                   // но по умолчанию setMouseTracking(false)
  void mousePressEvent(QMouseEvent *me); // Реагирует на нажатие кнопок мыши
  void mouseReleaseEvent(
      QMouseEvent *me); // Метод реагирует на "отжатие" кнопки мыши

  int point;              // набранные очки
  int gdx, gdy;           // Координаты объектов (гусей)
  int cax, cay, cbx, cby; // Координаты курсора
  bool singling;          // Для выделение области

protected slots:
  void render(); // Определяем координаты объектов
};
