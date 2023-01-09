#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
  class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

private slots:
  void on_pushButtonOpen_clicked();

  void on_textBrowser_backwardAvailable(bool arg1);

  void on_textBrowser_forwardAvailable(bool arg1);

  void on_textBrowser_textChanged();


private:
  Ui::Widget *ui;
  QUrl m_url;

  void SaveSettings();
  void LoadSettings();

  // QWidget interface
protected:
  virtual void closeEvent(QCloseEvent *event);
};
#endif // WIDGET_H
