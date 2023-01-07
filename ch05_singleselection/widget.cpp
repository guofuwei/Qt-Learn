#include "widget.h"

#include <QDebug>
#include <QMessageBox>

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
  m_pGenderGroup = new QButtonGroup(this);
  m_pGenderGroup->addButton(ui->radioButtonMan, 0);
  m_pGenderGroup->addButton(ui->radioButtonWoman, 1);
  m_pStatusGroup = new QButtonGroup(this);
  m_pStatusGroup->addButton(ui->radioButtonBang, 0);
  m_pStatusGroup->addButton(ui->radioButtonMeng, 1);
  m_pStatusGroup->addButton(ui->radioButtonYao, 2);
  connect(m_pGenderGroup, SIGNAL(buttonClicked(int)), this,
          SLOT(RecvGenderID(int)));
  connect(m_pStatusGroup, SIGNAL(buttonClicked(int)), this,
          SLOT(RecvStausID(int)));
  //初始化选中状态
  ui->radioButtonMan->setChecked(true);
  ui->radioButtonBang->setChecked(true);
  ui->radioButton0to19->setChecked(true);
}

Widget::~Widget() {
  delete ui;
}

void Widget::RecvGenderID(int id) {
  switch (id) {
    case 0:
      qDebug() << tr("性别：男");
      break;
    case 1:
      qDebug() << tr("性别：女");
      break;
    default:
      break;
  }
}

void Widget::RecvStatusID(int id) {
  switch (id) {
    case 0:
      qDebug() << tr("状态：棒棒哒");
      break;
    case 1:
      qDebug() << tr("状态：萌萌哒");
      break;
    case 2:
      qDebug() << tr("状态：该吃药了");
      break;
    default:
      break;
  }
}

void Widget::on_radioButton0to19_toggled(bool checked) {
  if (checked) {
    qDebug() << tr("年龄段：0-19");
  } else {
    qDebug() << tr("不是0-19");
  }
}

void Widget::on_radioButton20to39_toggled(bool checked) {
  if (checked) {
    qDebug() << tr("年龄段：20-39");
  } else {
    qDebug() << tr("不是 20-39");
  }
}

void Widget::on_radioButton40to59_toggled(bool checked) {
  if (checked) {
    qDebug() << tr("年龄段：40-59");
  } else {
    qDebug() << tr("不是 40-59");
  }
}

void Widget::on_radioButton60to_toggled(bool checked) {
  if (checked) {
    qDebug() << tr("年龄段：60 以上");
  } else {
    qDebug() << tr("不是 60 以上");
  }
}

void Widget::on_pushButton_clicked() {
  QString strResult;
  int nGenderID = m_pGenderGroup->checkedId();
  switch (nGenderID) {
    case 0:
      strResult += tr("性别：男\r\n");
      break;
    case 1:
      strResult += tr("性别：女\r\n");
      break;
    default:
      strResult += tr("性别：未选中\r\n");
      break;
  }
  //状态分组
  int nStatusID = m_pStatusGroup->checkedId();  //获取被选中的 id
  switch (nStatusID) {
    case 0:
      strResult += tr("状态：棒棒哒\r\n");
      break;
    case 1:
      strResult += tr("状态：萌萌哒\r\n");
      break;
    case 2:
      strResult += tr("状态：该吃药了\r\n");
      break;
    default:
      strResult += tr("状态：未选中\r\n");
      break;
  }
  //年龄段四个按钮判断
  if (ui->radioButton0to19->isChecked()) {
    strResult += tr("年龄段：0-19\r\n");
  } else if (ui->radioButton20to39->isChecked()) {
    strResult += tr("年龄段：20-39\r\n");
  } else if (ui->radioButton40to59->isChecked()) {
    strResult += tr("年龄段：40-59\r\n");
  } else if (ui->radioButton60to->isChecked()) {
    strResult += tr("年龄段：60 以上\r\n");
  } else {
    strResult += tr("年龄段：未选中\r\n");
  }
  QMessageBox::information(this, tr("综合信息"), strResult);
}
