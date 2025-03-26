#include <QApplication>

#include "mainwindow.h"
#include <png.h>
#include <desktop/fileresourceloader.h>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  FileResourceLoader rloader;
  auto png_image = rloader.readFile(QApplication::applicationDirPath().toStdString()  + "/assets/daco2.png");

  MainWindow window;
  window.show();
  return app.exec();
}
