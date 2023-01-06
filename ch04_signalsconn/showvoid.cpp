#include "showvoid.h"
#include <QMessageBox>

ShowVoid::ShowVoid(QObject *parent) : QObject{parent} {}

void ShowVoid::RecvVoid() {
  QMessageBox::information(NULL, tr("show"), tr("Just Void!"));
}
