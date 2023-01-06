#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);
}

Widget::~Widget() { delete ui; }

const QString &Widget::nickName() { return m_nickName; }

int Widget::count() { return m_count; }

void Widget::setNickName(const QString &strNewNickName) {
  if (m_nickName == strNewNickName) {
    return;
  }
  m_nickName = strNewNickName;
  emit nickNameChanged(strNewNickName);
}

void Widget::setCount(int nNewCount) {
  if (nNewCount == m_count) {
    return;
  }
  m_count = nNewCount;
  emit countChanged(nNewCount);
}
