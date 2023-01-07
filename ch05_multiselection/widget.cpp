#include "widget.h"
#include "qdesktopservices.h"
#include "qmessagebox.h"
#include "qnamespace.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  ui->checkBoxTristate->setTristate(true);
}

Widget::~Widget() {
  delete ui;
}

void Widget::CheckHobbies() {
  int count = 0;
  if(ui->checkBoxClimb->isChecked()) {
    count++;
  }
  if(ui->checkBoxDaze->isChecked()) {
    count++;
  }
  if(ui->checkBoxEat->isChecked()) {
    count++;
  }
  if(ui->checkBoxRead->isChecked()) {
    count++;
  }
  if(ui->checkBoxShopping->isChecked()) {
    count++;
  }
  if(ui->checkBoxSwim->isChecked()) {
    count++;
  }
  if(count <= 0) {
    ui->checkBoxTristate->setCheckState(Qt::Unchecked);
  } else if(count <= 5) {
    ui->checkBoxTristate->setCheckState(Qt::PartiallyChecked);
  } else {
    ui->checkBoxTristate->setCheckState(Qt::Checked);
  }
}


void Widget::on_checkBoxRead_toggled(bool checked) {
  if(checked) {
    qDebug() << tr("读书");
  }
  CheckHobbies();
}


void Widget::on_checkBoxClimb_toggled(bool checked) {
  if(checked) {
    qDebug() << tr("爬山");
  }
  CheckHobbies(); //更新三态复选框
}


void Widget::on_checkBoxSwim_toggled(bool checked) {
  if(checked) {
    qDebug() << tr("游泳");
  }
  CheckHobbies(); //更新三态复选框
}


void Widget::on_checkBoxDaze_toggled(bool checked) {
  if(checked) {
    qDebug() << tr("发呆");
  }
  CheckHobbies(); //更新三态复选框
}


void Widget::on_checkBoxShopping_toggled(bool checked) {
  if(checked) {
    qDebug() << tr("逛街");
  }
  CheckHobbies(); //更新三态复选框
}


void Widget::on_checkBoxEat_toggled(bool checked) {
  if(checked) {
    qDebug() << tr("吃货");
  }
  CheckHobbies(); //更新三态复选框
}


void Widget::on_pushButton_clicked() {
  QString strResult = tr("兴趣爱好为：\r\n");
  if( ui->checkBoxRead->isChecked() ) {
    strResult += tr("读书\r\n");
  }
  if( ui->checkBoxClimb->isChecked() ) {
    strResult += tr("爬山\r\n");
  }
  if( ui->checkBoxSwim->isChecked() ) {
    strResult += tr("游泳\r\n");
  }
  if( ui->checkBoxDaze->isChecked() ) {
    strResult += tr("发呆\r\n");
  }
  if( ui->checkBoxShopping->isChecked() ) {
    strResult += tr("逛街\r\n");
  }
  if( ui->checkBoxEat->isChecked() ) {
    strResult += tr("吃货\r\n");
  }
  QMessageBox::information(this, tr("兴趣爱好"), strResult);
}


void Widget::on_commandLinkButton_clicked() {
  QDesktopServices::openUrl(QUrl("file:///home/hanshan/Desktop"));
}


void Widget::on_commandLinkButton_2_clicked() {
  QDesktopServices::openUrl(QUrl("https://www.google.com"));
}

