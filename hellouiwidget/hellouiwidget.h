// hellouiwidget.h
#include "ui_hello.h"
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

class HelloUIWidget : public QWidget, public Ui::Form {
  Q_OBJECT
public:
  explicit HelloUIWidget(QWidget *parent = 0);
  ~HelloUIWidget();

protected:
  void AdjustLabel();
};