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

  //检查兴趣爱好，同步更新三态复选框的状态
  void CheckHobbies();

private slots:
  void on_checkBoxRead_toggled(bool checked);

  void on_checkBoxClimb_toggled(bool checked);

  void on_checkBoxSwim_toggled(bool checked);

  void on_checkBoxDaze_toggled(bool checked);

  void on_checkBoxShopping_toggled(bool checked);

  void on_checkBoxEat_toggled(bool checked);

  void on_pushButton_clicked();

  void on_commandLinkButton_clicked();

  void on_commandLinkButton_2_clicked();

private:
  Ui::Widget *ui;
};
#endif // WIDGET_H
