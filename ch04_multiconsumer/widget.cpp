#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  connect(ui->pushButtonAnderson, SIGNAL(clicked(bool)), this,
          SLOT(FoodIsComing()));
  connect(ui->pushButtonBruce, SIGNAL(clicked(bool)), this,
          SLOT(FoodIsComing()));
  connect(ui->pushButtonCastiel, SIGNAL(clicked(bool)), this,
          SLOT(FoodIsComing()));
}

Widget::~Widget() { delete ui; }

void Widget::FoodIsComing() {
  QString strObjectSrc = this->sender()->objectName();
  qDebug() << strObjectSrc;

  QString strMsg;
  if ("pushButtonAnderson" == strObjectSrc) {
    strMsg = tr("Hello Anderson! Your food is coming!");
  } else if ("pushButtonBruce" == strObjectSrc) {
    strMsg = tr("Hello Bruce! Your food is coming!");
  } else if ("pushButtonCastiel" == strObjectSrc) {
    strMsg = tr("Hello Castiel! Your food is coming!");
  } else {
    // do nothing
    return;
  }

  QMessageBox::information(this, tr("food"), strMsg);
}
