#include "widget.h"
#include "qcompleter.h"
#include "ui_widget.h"
#include <QCompleter>
#include <QDebug>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  QStringList listDayOfWeek;
  listDayOfWeek << "Monday" << "Tuesday" << "Wednesday"
                << "Thursday" << "Friday" << "Saturday" << "Sunday";
  QCompleter *cpDayOfWeek = new QCompleter(listDayOfWeek);
  //大小写不敏感
  cpDayOfWeek->setCaseSensitivity(Qt::CaseInsensitive);
  //设置给 lineEditDayOfWeek
  ui->lineEditDayOfWeek->setCompleter(cpDayOfWeek);
  QStringList listYear;
  listYear << "2016" << "2015"
           << "2008" << "2006"
           << "1999" << "1991";
  // sort
  listYear.sort();
  // complete
  QCompleter *cpYear = new QCompleter(listYear);
  ui->lineEditYear->setCompleter(cpYear);
  QStringList listHeXi;
  listHeXi << "何百夕" << "何千夕" << "何万夕" << "何亿夕";
  //构建补全器
  QCompleter *cpHeXi = new QCompleter(listHeXi);
  ui->lineEditHeXi->setCompleter(cpHeXi);
}

Widget::~Widget() {
  delete ui;
}


void Widget::on_lineEditDayOfWeek_textChanged(const QString &arg1) {
  qDebug() << "DayOfWeek: " << arg1;
}


void Widget::on_lineEditYear_textChanged(const QString &arg1) {
  qDebug() << "Year: " << arg1;
}


void Widget::on_lineEditHeXi_textChanged(const QString &arg1) {
  qDebug() << "何夕：" << arg1;
}

