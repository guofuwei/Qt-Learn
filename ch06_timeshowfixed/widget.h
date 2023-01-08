#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>   //定时器类

QT_BEGIN_NAMESPACE
namespace Ui {
  class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

public slots:
  //接收定时器信号的槽函数
  void RecvTimer();

private slots:
  void on_pushButton_clicked();


private:
  Ui::Widget *ui;
  QTimer *m_timer;
};
#endif // WIDGET_H
