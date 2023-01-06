#include "widget.h"

#include <QApplication>
#include <QDebug>
#include <QMetaClassInfo>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Widget w;

  //  const QMetaObject *pMO = w.metaObject();
  QObject *pObj = &w;
  const QMetaObject *pMO = pObj->metaObject();
  int nInfoCount = pMO->classInfoCount();
  for (int i = 0; i < nInfoCount; i++) {
    QMetaClassInfo info = pMO->classInfo(i);
    qDebug() << info.name() << "\t" << info.value();
  }

  qDebug() << "Class Name:" << pMO->className();
  qDebug() << "Object Name:" << w.objectName();

  qDebug() << w.inherits("QWidget");
  qDebug() << w.inherits("nothing");

  w.show();
  return a.exec();
}
