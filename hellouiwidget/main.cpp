// main.cpp
#include "hellouiwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  HelloUIWidget *huiw = new HelloUIWidget();
  huiw->show();

  return a.exec();
}