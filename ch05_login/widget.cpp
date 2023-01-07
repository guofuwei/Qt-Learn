#include "widget.h"
#include "qcryptographichash.h"
#include "qmessagebox.h"
#include "ui_widget.h"
#include <QLineEdit>
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  ui->lineEditPassword->setEchoMode(QLineEdit::Password);
}

Widget::~Widget() {
  delete ui;
}


void Widget::on_pushButtonLogin_clicked() {
  if(ui->lineEditUser->text().isEmpty() || ui->lineEditPassword->text().isEmpty()) {
    QMessageBox::warning(this, "警告", "用户名或密码不能为空");
    return;
  }
  m_strUser = ui->lineEditUser->text();
  m_bytePasswordHash = QCryptographicHash::hash(ui->lineEditPassword->text().toUtf8(), \
                       QCryptographicHash::Sha3_256);
  QString strMsg = tr("用户名：") + m_strUser + tr("\r\n") + tr("密码 Hash：");
  //把每个 Hash 字节转成一对十六进制字符显示
  // 256 bit 对应 32 字节，变成 64 个十六进制字符打印
  strMsg += m_bytePasswordHash.toHex();
  //打印消息
  qDebug() << strMsg;
  //弹窗显示，注意：实际应用中会将用户名和密码 Hash 与数据库或配置文件里的做比较，而不是弹窗
  QMessageBox::information(this, tr("用户信息"), strMsg);
}


void Widget::on_pushButtonExit_clicked() {
  this->close();
}

