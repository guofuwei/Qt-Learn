#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QResizeEvent> //调整大小的事件
#include <QFontMetrics> //字体度量对象，用于计算文本显示宽度

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget)
{
  ui->setupUi(this);
  //指定窗口最小尺寸，根据第三行控件定宽度
  this->setMinimumSize(10 + 54 + 10 + 75 + 10, 24 * 3 + 10 * 4);
}

Widget::~Widget()
{
  delete ui;
}


void Widget::on_lineEdit_textEdited(const QString &arg1)
{
  //获取按钮文本字体度量对象
  QFontMetrics fm = ui->pushButtonDynamic->fontMetrics();
  int nTextWidth = fm.horizontalAdvance(arg1);
  QSize szButtonDynamic = ui->pushButtonDynamic->size();
  szButtonDynamic.setWidth(nTextWidth + 10);
  ui->pushButtonDynamic->resize(szButtonDynamic);
  ui->pushButtonDynamic->setText(arg1);
  ui->pushButtonDynamic -> setToolTip(arg1);
  //设置固定按钮，两个按钮的字体一样，不需要重新计算原文 arg1 显示宽度
  //固定按钮尺寸为 75*24，可显示文本的宽度为 75-10 == 65
  if (nTextWidth <= 65) {
    ui->pushButtonFixed->setText(arg1);
  } else {
    QString strPart;
    QString strDot = "...";
    int nStrLen = arg1.length();
    int nNewTextWidth = 0;
    for (int i = 0; i < nStrLen; i++) {
      strPart += arg1[i];
      nNewTextWidth = fm.horizontalAdvance(strPart + strDot);
      if (nNewTextWidth >= 65) {
        break;
      }
      ui->pushButtonFixed->setText(strPart + strDot);
    }
  }
  ui->pushButtonFixed->setToolTip(arg1);
}



void Widget::resizeEvent(QResizeEvent *event)
{
  int W = event->size().width();
  int H = event->size().height();
  //计算第一行控件分布，标签尺寸都是 54*24
  //标签1
  int xLabel1 = 10;
  int yLabel1 = H / 4 - 12;
  ui->label_1->move(xLabel1, yLabel1);
  //单行编辑控件
  int xLineEdit = xLabel1 + 54 + 10;  //54是标签宽度，10是间隙
  int yLineEdit = yLabel1;
  int wLineEdit = W - xLineEdit - 10; // 10 是右边距
  int hLineEdit = 24;
  //设置矩形
  ui->lineEdit->setGeometry(xLineEdit, yLineEdit, wLineEdit, hLineEdit);
  //计算第二行控件分布，标签控件 54*24
  //标签2
  int xLabel2 = 10;
  int yLabel2 = 2 * H / 4 - 12;
  //移动标签
  ui->label_2->move(xLabel2, yLabel2);
  //动态按钮
  int xButtonDynamic = xLabel2 + 54 + 10;
  int yButtonDynamic = yLabel2;
  //移动即可，尺寸由上面槽函数 on_lineEdit_textEdited 处理
  ui->pushButtonDynamic->move(xButtonDynamic, yButtonDynamic);
  //计算第三行控件分布，标签控件 54*24
  //标签3
  int xLabel3 = 10;
  int yLabel3 = 3 * H / 4 - 12;
  //移动标签
  ui->label_3->move(xLabel3, yLabel3);
  //固定按钮
  int xButtonFixed = xLabel3 + 54 + 10;
  int yButtonFixed = yLabel3;
  //移动即可，尺寸固定
  ui->pushButtonFixed->move(xButtonFixed, yButtonFixed);
}
