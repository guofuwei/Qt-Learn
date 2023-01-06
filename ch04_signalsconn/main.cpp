#include "showvoid.h"
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;
  ShowVoid s;

  QObject::connect(&w, SIGNAL(SendVoid()), &s, SLOT(RecvVoid()));
  w.show();
  return a.exec();
}
