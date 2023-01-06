#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),ui->label,SLOT(setText(QString)));
    connect(ui->lineEdit,SIGNAL(textChanged(QString)),ui->textBrowser,SLOT(setText(QString)));
//    connect(ui->lineEdit,SIGNAL(textChanged(QString)),this,SLOT(PrintSlot(QString)));
    connect(ui->lineEdit,&QLineEdit::textEdited,this,&Widget::PrintSlot);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::PrintSlot(const QString &text)
{
    qDebug()<<text;
}
