#ifndef WIDGET_H
#define WIDGET_H

#include "qmovie.h"
#include "qpixmap.h"
#include <QWidget>
#include <QPixmap>
#include <QMovie>
#include <QImageReader>

QT_BEGIN_NAMESPACE
namespace Ui {
  class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
  Q_OBJECT

public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

public slots:
  //接收出错的信号
  void RecvPlayerError(QImageReader::ImageReaderError error);
  //接收播放时帧号变化
  void RecvPlayerFrameNumber(int frameNumber);

private slots:
  void on_pushButtonOpenPic_clicked();

  void on_pushButtonOpenMov_clicked();

  void on_pushButtonStart_clicked();

  void on_pushButtonStop_clicked();

private:
  Ui::Widget *ui;
  QPixmap *m_pPixMap;
  QMovie *m_pMovie;
  bool m_bIsMovie;
  bool m_bIsPlaying;

  //清除函数，在打开新图之前，清空旧的
  void ClearOldShow();

  // QWidget interface
protected:
  virtual void resizeEvent(QResizeEvent *event);
};
#endif // WIDGET_H
