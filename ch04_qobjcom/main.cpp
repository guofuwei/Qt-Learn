#include "showmsg.h"
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;
  ShowMsg s;

  QObject::connect(&w, SIGNAL(SendMsg(QString)), &s, SLOT(RecvMsg(QString)));

  w.show();
  return a.exec();
}
