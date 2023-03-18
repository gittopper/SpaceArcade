#include <game/spacegame.h>
#include <mainwindow.h>
#include <rendering/openglrenderer.h>
using namespace Game;
std::unique_ptr<SpaceGame> game;

MainWindow::MainWindow(QWidget *parent) : QGLWidget(parent) {

  point = 0;
  singling = false;
  setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
  glDepthFunc(GL_LEQUAL);                  // Буфер глубины
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(render()));
  timer->start(50);
}

void MainWindow::initializeGL() {
  qglClearColor(Qt::black); // Черный цвет фона
}

void MainWindow::resizeGL(int nWidth, int nHeight) {
  if (!game) {
    game.reset(new SpaceGame);
    game->setRenderer(new OpenGLRenderer);
    GameConfig config;
    config.dt = 1. / 20;
    game->getRenderer()->setScreeenSize(nWidth, nHeight);
    game->setupGame(config);
  }
  game->getRenderer()->setScreeenSize(nWidth, nHeight);
  render();
}

void MainWindow::paintGL() {

  //  qglColor(Qt::white);
  //  renderText(10, 10, 0, QString::fromUtf8("Вы набрали %1
  //  очков:").arg(point),
  //             QFont());

  game->renderStep();

  swapBuffers();
}

void MainWindow::keyPressEvent(QKeyEvent *ke) {
  switch (ke->key()) {
  case Qt::Key_Space:
    break;
  }
  updateGL();
}

void MainWindow::mouseMoveEvent(QMouseEvent *me) {
  // Получаем координаты курсора
  cax = me->x();
  cay = me->y();
  if (singling) {
    game->drag(cax - cbx, cby - cay);
  }
  // updateGL();
}

void MainWindow::mousePressEvent(QMouseEvent *me) {
  if (me->button() == Qt::LeftButton) {
    game->tap(me->x(), me->y());
    singling = true;
    cbx = me->x();
    cby = me->y();
    updateGL();
  } else {
    singling = false;
  }
  updateGL();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *me) {
  // Если отпускаем левую кнопку мыши - удалить выделение
  if (singling == true && me->button() == Qt::LeftButton) {
    singling = false;
  }
  updateGL();
}

void MainWindow::render() { updateGL(); }
