#ifndef WIDGET_H
#define WIDGET_H

#include <QButtonGroup>
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

 public slots:
  void RecvGenderID(int id);
  void RecvStatusID(int id);

 private slots:
  void on_radioButton0to19_toggled(bool checked);

  void on_radioButton20to39_toggled(bool checked);

  void on_radioButton40to59_toggled(bool checked);

  void on_radioButton60to_toggled(bool checked);

  void on_pushButton_clicked();

 private:
  Ui::Widget *ui;
  QButtonGroup *m_pGenderGroup;
  QButtonGroup *m_pStatusGroup;
};
#endif  // WIDGET_H
