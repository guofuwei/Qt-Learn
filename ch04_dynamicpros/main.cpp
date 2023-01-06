#include "widget.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;

  qDebug() << w.property("invalidvalue").isValid();

  w.setProperty("myValue", 80);
  qDebug() << fixed << w.property("myValue").toDouble();

  w.setProperty("myName", "hanshan");
  qDebug() << w.property("myName").toString();

  qDebug() << w.dynamicPropertyNames();

  w.show();
  return a.exec();
}
