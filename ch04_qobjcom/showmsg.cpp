#include "showmsg.h"
#include <QMessageBox>

ShowMsg::ShowMsg(QObject *parent) : QObject{parent} {}

void ShowMsg::RecvMsg(QString str) {
  QMessageBox::information(NULL, tr("Show"), str);
}
