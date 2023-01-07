#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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

private slots:
  void on_comboBoxSnacks_currentIndexChanged(int index);

  void on_pushButtonCalc_clicked();

private:
  Ui::Widget *ui;
};
#endif // WIDGET_H
