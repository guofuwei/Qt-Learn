#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  connect(ui->pushButton, SIGNAL(clicked(bool)), this, SIGNAL(SendVoid()));
}

Widget::~Widget() { delete ui; }
