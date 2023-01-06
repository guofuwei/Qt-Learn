#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  this->on_pushButtonConn_clicked();
}

Widget::~Widget() { delete ui; }

void Widget::on_pushButtonConn_clicked() {
  connect(ui->lineEdit, &QLineEdit::textEdited, ui->label, &QLabel::setText);

  ui->pushButtonConn->setEnabled(false);
  ui->pushButtonDisconn->setEnabled(true);
}

void Widget::on_pushButtonDisconn_clicked() {
  disconnect(ui->lineEdit, &QLineEdit::textEdited, ui->label, &QLabel::setText);

  ui->pushButtonConn->setEnabled(true);
  ui->pushButtonDisconn->setEnabled(false);
}
