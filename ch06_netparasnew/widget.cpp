#include "widget.h"
#include "qvalidator.h"
#include "ui_widget.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QDebug>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  ui->lineEditMAC->setInputMask("HH:HH:HH:HH:HH:HH");
  QRegExp re("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
             "(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
  QRegExpValidator *reVali = new QRegExpValidator(re);
  ui->lineEditIP->setValidator(reVali);
  //新建整数验证器
  QIntValidator *intVali = new QIntValidator(0, 65535);
  //设置给 lineEditPort
  ui->lineEditPort->setValidator(intVali);
//  setLayout(ui->verticalLayout);
}

Widget::~Widget() {
  delete ui;
}


void Widget::on_lineEditMAC_textChanged(const QString &arg1) {
  qDebug() << "MAC: " << arg1;
}


void Widget::on_lineEditIP_textChanged(const QString &arg1) {
  qDebug() << "IP: " << arg1;
}


void Widget::on_lineEditPort_textChanged(const QString &arg1) {
  qDebug() << "Port: " << arg1;
}

