#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

private slots:


  void on_lineEdit_textEdited(const QString &arg1);

private:
  Ui::Widget *ui;

  // QWidget interface
protected:
  virtual void resizeEvent(QResizeEvent *event);
};
#endif // WIDGET_H
