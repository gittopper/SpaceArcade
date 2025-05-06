#include <QApplication>
#include <QtOpenGL>

#include <desktop/fileresourceloader.h>
#include <game/soundplayer.h>
#include <game/spacegame.h>
#include <rendering/glesspacegamerenderer.h>

#include <mainwindow.h>
#include <mutex>

using namespace Game;
std::unique_ptr<SpaceGame> game;
std::mutex mutex_;

MainWindow::MainWindow(QWidget* parent) : QOpenGLWidget(parent) {
    point = 0;
    singling = false;
    QSurfaceFormat format;
    format.setGreenBufferSize(8);
    format.setRedBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    setFormat(format);
    glDepthFunc(GL_LEQUAL);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(render()));
    timer->start(50);
}

void MainWindow::initializeGL() {}

void MainWindow::resizeGL(int w, int h) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!game) {
        game.reset(new SpaceGame);
        auto renderer = std::make_shared<GLESSpaceGameRenderer>();
        auto rloader = std::make_shared<FileResourceLoader>();
        rloader->setResourcesPath(
            QApplication::applicationDirPath().toStdString() + "/assets/");
        renderer->initRenderer(rloader.get());
        game->setRenderer(renderer);
        game->game_state_.player_ = std::make_shared<SoundPlayer>(rloader);
        game->game_state_.resource_loader_ = rloader;
        GameConfig config;
        game->setupGame(w, h);
    }
    game->resize(w, h);
    render();
}

void MainWindow::paintGL() {
    std::lock_guard<std::mutex> lock(mutex_);

    game->renderStep();

    // swapBuffers();
}

void MainWindow::keyPressEvent(QKeyEvent* ke) {
    std::lock_guard<std::mutex> lock(mutex_);
    switch (ke->key()) {
        case Qt::Key_Space:
            break;
    }
    update();
}

void MainWindow::wheelEvent(QWheelEvent* we) {
    if (we->angleDelta().y() > 0) {
        game->zoom(1.1);
    } else {
        game->zoom(0.9);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* me) {
    std::lock_guard<std::mutex> lock(mutex_);
    // Получаем координаты курсора
    cax = me->position().x();
    cay = game->game_state_.camera_.height() - me->position().y();
    if (singling) {
        game->drag(cax - cbx, cby - cay);
    }
    // updateGL();
}

void MainWindow::mousePressEvent(QMouseEvent* me) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (me->button() == Qt::LeftButton) {
        game->tap(me->position().x(), me->position().y());
        singling = true;
        cbx = me->position().x();
        cby = game->game_state_.camera_.height() - me->position().y();
        update();
    } else {
        singling = false;
    }
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* me) {
    std::lock_guard<std::mutex> lock(mutex_);
    // Если отпускаем левую кнопку мыши - удалить выделение
    if (singling == true && me->button() == Qt::LeftButton) {
        singling = false;
    }
    update();
}

void MainWindow::render() {
    update();
}
