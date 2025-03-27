#include <game/spacegame.h>
#include <mainwindow.h>
#include <desktop/openglrenderer.h>
#include <QtOpenGL>
#include <desktop/soundplayer.h>
#include <desktop/fileresourceloader.h>
#include <QApplication>

using namespace Game;
std::unique_ptr<SpaceGame> game;

MainWindow::MainWindow(QWidget *parent) : QOpenGLWidget(parent) {

  point = 0;
  singling = false;
  QSurfaceFormat format;
  format.setGreenBufferSize(8);
  format.setRedBufferSize(8);
  format.setBlueBufferSize(8);
  format.setAlphaBufferSize(8);
  format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
  setFormat(format); // Двойная буферизация
  glDepthFunc(GL_LEQUAL);                  // Буфер глубины
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(render()));
  timer->start(50);
}

void MainWindow::initializeGL() {
  //glClearColor(Qt::black); // Черный цвет фона
}

void MainWindow::resizeGL(int nWidth, int nHeight) {
  if (!game) {
    game.reset(new SpaceGame);
    game->setRenderer(new OpenGLRenderer);
    game->setPlayer(std::make_shared<SoundPlayer>());
    auto rloader = std::make_shared<FileResourceLoader>();
    rloader->setResourcesPath(QApplication::applicationDirPath().toStdString()  + "/assets/");
    game->setResourceLoader(rloader);
    GameConfig config;
    config.dt_ = 1. / 20;
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

  //swapBuffers();
}

void MainWindow::keyPressEvent(QKeyEvent *ke) {
  switch (ke->key()) {
  case Qt::Key_Space:
    break;
  }
  update();
}

void MainWindow::mouseMoveEvent(QMouseEvent *me) {
  // Получаем координаты курсора
  cax = me->position().x();
  cay = me->position().y();
  if (singling) {
    game->drag(cax - cbx, cby - cay);
  }
  // updateGL();
}

void MainWindow::mousePressEvent(QMouseEvent *me) {
  if (me->button() == Qt::LeftButton) {
    game->tap(me->position().x(), me->position().y());
    singling = true;
    cbx = me->position().x();
    cby = me->position().y();
    update();
  } else {
    singling = false;
  }
  update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *me) {
  // Если отпускаем левую кнопку мыши - удалить выделение
  if (singling == true && me->button() == Qt::LeftButton) {
    singling = false;
  }
  update();
}

void MainWindow::render() { update(); }
