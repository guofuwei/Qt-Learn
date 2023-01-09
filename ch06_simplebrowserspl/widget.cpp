#include "widget.h"
#include "qfiledialog.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QDebug>
#include <QTextDocumentWriter>
#include <QSettings>

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
  // 加载配置文件
  LoadSettings();
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



void Widget::closeEvent(QCloseEvent *event) {
  SaveSettings();
}


void Widget::SaveSettings() {
  QSettings settings("QtGuide", "SimpleBrowser");
  QByteArray baMainWidget = this->saveGeometry();
  QByteArray baSplitter = ui->splitter->saveState();
  QUrl urlSrc = ui->textBrowser->source();
  settings.setValue("MainWidget", baMainWidget);
  settings.setValue("Splitter", baSplitter);
  settings.setValue("URL", urlSrc);
}

void Widget::LoadSettings() {
  QSettings settings("QtGuide", "SimpleBrowser");
  if(settings.contains("MainWidget")) {
    QByteArray baMainWidget = settings.value("MainWidget").toByteArray();
    this->restoreGeometry(baMainWidget);
  }
  if(settings.contains("Splitter")) {
    QByteArray baSplitter = settings.value("Splitter").toByteArray();
    ui->splitter->restoreState(baSplitter);
  }
  if(settings.contains("URL")) {
    QUrl urlSrc = settings.value("URL").toUrl();
    ui->textBrowser->setSource(urlSrc);
  }
}
