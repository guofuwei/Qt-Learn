#include "widget.h"
#include "qcolordialog.h"
#include "qfont.h"
#include "qnamespace.h"
#include "qvalidator.h"
#include "ui_widget.h"
#include <QDebug>
#include <QIntValidator>    //整数验证器
#include <QFont>            //综合字体格式
#include <QColorDialog>     //用于选取前景色和背景色
#include <QBrush>           //颜色画刷

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  ui->pushButtonBold->setCheckable(true);
  ui->pushButtonItalic->setCheckable(true);
  ui->pushButtonUnderline->setCheckable(true);
  //字号原本是浮点数，这里简化为整数
  //字体点阵大小，这里设置下限 0，上限 72
  //0 不是没有字号，是不确定字号多大
  QIntValidator *vali = new QIntValidator(0, 72);
  ui->lineEditFontSize->setValidator(vali);
  ui->lineEditFontSize->setText(QString("").setNum(9));
  //字体家族设置，直接关联组合框的信号到编辑框槽函数
  connect(ui->fontComboBox, SIGNAL(currentIndexChanged(QString)), ui->textEdit, \
          SLOT(setFontFamily(QString)));
  ui->textEdit->setHtml("<b>粗体字的行<br></b>"
                        "<i>斜体字的行<br></i>"
                        "<u>下划线的行<br></u>"
                        "<font style=\"color:red;\">文本前景色<br></font>"
                        "<font style=\"background:yellow;\">文字背景色<br></font>"
                        "<font style=\"font-size:18pt;\">字号大小变化的行<br></font>"
                        "<font style=\"font-family:黑体;\">字体家族变化的行<br></font>"
                       );
  //html 字号有 pt(PointSize) 和 px(PixelSize) 两种形式，例子代码适用于 pt
  //通常 1 英寸 == 72pt(点) == 96px (像素)，网页中最常用到的：9pt == 12px
}

Widget::~Widget() {
  delete ui;
}


void Widget::on_pushButtonBold_clicked(bool checked) {
  if(checked) {
    ui->textEdit->setFontWeight(QFont::Bold);
  } else {
    ui->textEdit->setFontWeight(QFont::Normal);
  }
}


void Widget::on_pushButtonItalic_clicked(bool checked) {
  ui->textEdit->setFontItalic(checked);
}


void Widget::on_pushButtonUnderline_clicked(bool checked) {
  ui->textEdit->setFontUnderline(checked);
}


void Widget::on_pushButtonColor_clicked() {
  QColor clr = QColorDialog::getColor(Qt::black);
  if(clr.isValid()  ) {
    ui->textEdit->setTextColor(clr);
    //同步设置该按钮的前景色
    QString strSS = tr("color：%1").arg(clr.name());
    ui->pushButtonColor ->setStyleSheet(strSS);
  }
}


void Widget::on_pushButtonBGColor_clicked() {
  QColor bgclr = QColorDialog::getColor(Qt::white);
  if(bgclr.isValid()) {
    ui->textEdit->setTextBackgroundColor(bgclr);
    //同步设置该按钮的背景色
    QString strBgSS = tr("background：%1").arg(bgclr.name());
    ui->pushButtonBGColor->setStyleSheet(strBgSS);
  }
}


void Widget::on_lineEditFontSize_editingFinished() {
  int nFontSize = ui->lineEditFontSize->text().toInt();
  ui->textEdit->setFontPointSize(nFontSize);
}


void Widget::on_textEdit_currentCharFormatChanged(const QTextCharFormat &format) {
  // 上面的按钮同步文本的格式
  if(format.fontWeight() == QFont::Bold) {
    ui->pushButtonBold->setChecked(true);
  } else {
    ui->pushButtonBold->setChecked(false);
  }
  ui->pushButtonItalic->setChecked(format.fontItalic());
  ui->pushButtonUnderline->setChecked(format.fontUnderline());
  //文字前景色画刷，不一定有
  QBrush brushText = format.foreground();
  if( brushText != Qt::NoBrush ) { //有前景色画刷
    QColor clrText = brushText.color();
    QString strSS = tr("color: %1").arg( clrText.name() );
    ui->pushButtonColor->setStyleSheet( strSS );
  } else { //没有前景色画刷 Qt::NoBrush
    ui->pushButtonColor->setStyleSheet("");
  }
  //文字背景画刷，不一定有
  QBrush brushBG = format.background();
  if( brushBG != Qt::NoBrush ) { //有背景色画刷
    QColor clrBG = brushBG.color();
    QString strSSBG = tr("background: %1").arg(clrBG.name());
    ui->pushButtonBGColor->setStyleSheet(strSSBG);
  } else { //没背景画刷 Qt::NoBrush
    ui->pushButtonBGColor->setStyleSheet("");
  }
  // 同步字号
  QFont curFont = format.font();
  int nFontSize = curFont.pointSize();//字号检测
  if( -1 == nFontSize ) { //如果 pt 是 -1，是 px 格式
    //如果是 px ，换算成 px
    nFontSize = (int)( curFont.pixelSize() * 12.0 / 9.0 ) ;
  }
  ui->lineEditFontSize->setText( QString("").setNum(nFontSize) );
  // 同步字体
  QString strFontFamily = curFont.family();
  ui->fontComboBox->setCurrentFont(strFontFamily);
}


void Widget::on_textEdit_textChanged() {
  qDebug() << ui->textEdit->toHtml() << endl; //打印丰富文本
}

