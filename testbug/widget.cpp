#include "widget.h"
#include "ui_widget.h"
#include <QtTest/QtTest>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    qDebug()<<(void*)(ui->label);
    ui->setupUi(this);

    ui->label->setText(tr("Test Bug!"));

    QTest::qSleep(1000);

    qDebug()<<(void*)(ui->label);
    qDebug()<<ui->label;
}

Widget::~Widget()
{
    delete ui;
}

