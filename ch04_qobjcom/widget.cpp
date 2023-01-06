#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(ButtonClicked()));
}

Widget::~Widget() { delete ui; }

void Widget::ButtonClicked() { emit SendMsg(tr("This is the message!")); }
