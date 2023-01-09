#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>  //消息框
#include <QDateTime>    //日期时间类，可以获取当前时间
#include <QDebug>



Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  ui->comboBoxJob->setEditable(true);
  ui->dateEdit->setCalendarPopup(true);
}

Widget::~Widget() {
  delete ui;
}


void Widget::on_comboBoxGender_currentIndexChanged(int index) {
  if(index < 0) {
    return;
  }
  qDebug() << "性别:" << ui->comboBoxGender->itemText(index);
}



void Widget::on_comboBoxJob_currentTextChanged(const QString &arg1) {
  qDebug() << "职业" << arg1;
}




void Widget::on_dateEdit_dateChanged(const QDate &date) {
  qDebug() << date.toString("yyyy-MM-dd"); //参数是日期字符串格式
  //yyyy 是四位数年份，MM 是两位数月份，dd 是两位数日子，比如 "2000-01-01"
}


void Widget::on_pushButtonCommit_clicked() {
  QString strResult;
  //获取姓名
  strResult += tr("姓名：%1\r\n").arg( ui->lineEditName->text() );
  //性别
  strResult += tr("性别：%1\r\n").arg(ui->comboBoxGender->currentText());
  //职业
  strResult += tr("职业：%1\r\n").arg( ui->comboBoxJob->currentText() );
  //生日
  strResult += tr("生日：%1\r\n").arg( ui->dateEdit->date().toString() );
  //额外功能，根据当前时间和用户生日，计算用户当前岁数
  QDateTime dtCur = QDateTime::currentDateTime();
  int nYears = dtCur.date().year() - ui->dateEdit->date().year();
  strResult += tr("岁数：%1").arg(nYears);
  QMessageBox::information(this, tr("信息"), strResult);
}

