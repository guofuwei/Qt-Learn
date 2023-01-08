#include "widget.h"
#include "ui_widget.h"
#include <QDateTime>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  this->setWindowTitle(tr("电子钟"));
  m_timer = new QTimer();
  m_timer->setSingleShot(false);
  m_timer->setInterval(1 * 1000);
  connect(m_timer, SIGNAL(timeout()), this, SLOT(RecvTimer()));
  m_timer->start();
  on_pushButton_clicked();
}

Widget::~Widget() {
  delete ui;
}


void Widget::on_pushButton_clicked() {
  //获取当前时间
  QDateTime dt = QDateTime::currentDateTime();
  //设置日历为今天
  ui->calendarWidget->setSelectedDate(dt.date());
  //点击按钮时，输入焦点在按钮上，这时候日历选中的日子是灰色，容易看不清
  //将输入焦点回到日历控件，这样日历选中日子会重新变成高亮蓝色
  ui->calendarWidget->setFocus();
}

void Widget::RecvTimer() {
  // 获取当地时间
  QDateTime dt = QDateTime::currentDateTime();
  QString strTime = dt.time().toString("HH:mm:ss");
  ui->lcdNumber->display(strTime);
  ui->progressBar->setValue(dt.time().second() % 10);
}

