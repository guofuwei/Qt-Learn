#include "widget.h"
#include "qfiledialog.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QTextDocumentWriter>

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget) {
  ui->setupUi(this);
  ui->plainTextEdit->setReadOnly(true);
  ui->textBrowser->setOpenExternalLinks(true);
  ui->pushButtonBackward->setEnabled(false);
  ui->pushButtonForeward->setEnabled(false);
  connect(ui->pushButtonForeward, SIGNAL(clicked(bool)), ui->textBrowser, SLOT(forward()));
  connect(ui->pushButtonBackward, SIGNAL(clicked(bool)), ui->textBrowser, SLOT(backward()));
}

Widget::~Widget() {
  delete ui;
}


void Widget::on_pushButtonOpen_clicked() {
  QUrl urlFile = QFileDialog::getOpenFileUrl(this, "open HTML", QUrl(""), \
                 "HTML files(*.htm *.html)");
  if(!urlFile.isEmpty()) {
    m_url = urlFile;
    qDebug() << urlFile.toString();
    ui->textBrowser->setSource(urlFile);
  }
}


void Widget::on_textBrowser_backwardAvailable(bool arg1) {
  ui->pushButtonBackward->setEnabled(arg1);
}


void Widget::on_textBrowser_forwardAvailable(bool arg1) {
  ui->pushButtonForeward->setEnabled(arg1);
}


void Widget::on_textBrowser_textChanged() {
  QString strHtml = ui->textBrowser->toHtml();
  ui->plainTextEdit->setPlainText(strHtml);
}




