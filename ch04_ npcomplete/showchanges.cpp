#include "showchanges.h"
#include <QDebug>

ShowChanges::ShowChanges(QObject *parent) : QObject{parent} {}

void ShowChanges::RecvValue(double v) {
  qDebug() << "RecvValue:" << fixed << v;
}

void ShowChanges::RecvCount(int count) { qDebug() << "RecvCount:" << count; }

void ShowChanges::RecvNickName(const QString &nickName) {
  qDebug() << "RecvNickName:" << nickName;
}
