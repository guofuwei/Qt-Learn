#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextCharFormat>

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
  void on_pushButtonBold_clicked(bool checked);

  void on_pushButtonItalic_clicked(bool checked);

  void on_pushButtonUnderline_clicked(bool checked);

  void on_pushButtonColor_clicked();

  void on_pushButtonBGColor_clicked();

  void on_lineEditFontSize_editingFinished();

  void on_textEdit_currentCharFormatChanged(const QTextCharFormat &format);

  void on_textEdit_textChanged();

private:
  Ui::Widget *ui;
};
#endif // WIDGET_H
