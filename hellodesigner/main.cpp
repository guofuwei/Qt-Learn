#include "QtWidgets/qapplication.h"
#include "QtWidgets/qwidget.h"
#include "ui_hello.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget *hw = new QWidget();
  Ui::Form createUi;
  createUi.setupUi(hw);
  hw->show();

  return a.exec();
}