#ifndef SHOWCHANGES_H
#define SHOWCHANGES_H

#include <QObject>

class ShowChanges : public QObject {
  Q_OBJECT
public:
  explicit ShowChanges(QObject *parent = nullptr);

signals:

public slots:
  void RecvValue(double v);
  void RecvCount(int count);
  void RecvNickName(const QString &nickName);
};

#endif // SHOWCHANGES_H
