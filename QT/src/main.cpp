#include <QApplication>

#include "mainwindow.h"
#include <desktop/fileresourceloader.h>
#include <game/pngreader.h>

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  FileResourceLoader rloader;
  auto resource_path = QApplication::applicationDirPath().toStdString()  + "/assets/daco2.png";
  auto png_image = rloader.readFile(resource_path);
  auto png = PngReader::read(png_image, false);
  MainWindow window;
  window.show();
  return app.exec();
}
