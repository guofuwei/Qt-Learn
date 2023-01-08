#include "widget.h"
#include "qfiledialog.h"
#include "qmessagebox.h"
#include "qpixmap.h"
#include "qscrollarea.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>  //打开文件对话框
#include <QScrollArea>  //为标签添加滚动区域
#include <QMessageBox>  //消息框
#include <QResizeEvent> //调整窗口大小的事件类

Widget::Widget(QWidget *parent)
  : QWidget(parent)
  , ui(new Ui::Widget)
{
  ui->setupUi(this);
  // 初始化变量
  m_pPixMap = NULL;
  m_pMovie = NULL;
  m_bIsMovie = false;
  m_bIsPlaying = false;
  // 获取标签矩形
  QRect rcLabel = ui->labelShow->geometry();
  QScrollArea *pSA = new QScrollArea(this);
  pSA->setWidget(ui->labelShow);
  pSA->setGeometry(rcLabel);
  //打印支持的图片格式
  qDebug() << QImageReader::supportedImageFormats();
  //打印支持的动态图格式
  qDebug() << QMovie::supportedFormats();
  //设置主界面窗体最小尺寸
  this->setMinimumSize(350, 350);
}

Widget::~Widget()
{
  ClearOldShow();
  delete ui;
}


void Widget::on_pushButtonOpenPic_clicked()
{
  QString strFileName;
  strFileName = QFileDialog::getOpenFileName(this, tr("打开静态图片"), \
                                             "", "Pictures (*.bmp *.jpg *.jpeg *.png *.xpm);;All files(*)");
  if (strFileName.isEmpty()) {
    return;
  }
  ClearOldShow();
  qDebug() << strFileName;
  m_pPixMap = new QPixmap();
  if (m_pPixMap->load(strFileName)) {
    ui->labelShow->setPixmap(*m_pPixMap);
    ui->labelShow->setGeometry(m_pPixMap->rect());
    m_bIsMovie = false;
    m_bIsPlaying = false;
  } else {
    delete m_pPixMap;
    m_pPixMap = NULL;
    QMessageBox::critical(this, tr("打开失败"),
                          tr("打开图片失败，文件名为：\r\n%1").arg(strFileName));
  }
}


void Widget::on_pushButtonOpenMov_clicked()
{
  QString strFileName;
  strFileName = QFileDialog::getOpenFileName(this, tr("打开动态图片"), "",
                                             "Movies (*.gif *.mng);;All files(*)");
  if (strFileName.isEmpty()) {
    return;
  }
  ClearOldShow();
  qDebug() << strFileName;
  //新建动态图
  m_pMovie = new QMovie(strFileName);
  if (!m_pMovie->isValid()) {
    QMessageBox::critical(this, tr("动态图不可用"),
                          tr("动态图格式不支持或读取出错，文件名为：\r\n%1").arg(strFileName));
    //清除
    delete m_pMovie;
    m_pMovie = NULL;
    return;
  }
  int nCount = m_pMovie->frameCount();
  qDebug() << tr("总帧数：%1").arg(nCount);
  //如果有统计帧数，那就设置滑动条上限
  if (nCount > 0) {
    ui->horizontalSlider->setMaximum(nCount);
  } else {
    ui->horizontalSlider->setMaximum(100);
  }
  ui->labelShow->setMovie(m_pMovie);
  m_bIsMovie = true;
  m_bIsPlaying = false;
  //关联播放时的信号
  //播放出错信号
  connect(m_pMovie, SIGNAL(error(QImageReader::ImageReaderError)), this, SLOT(RecvPlayerError(QImageReader::ImageReaderError)));
  connect(m_pMovie, SIGNAL(frameChanged(int)), this, SLOT(RecvPlayerFrameNumber(int)));
  if (m_pMovie->jumpToFrame(0)) {
    ui->labelShow->setGeometry(m_pMovie->frameRect());
  }
}


void Widget::on_pushButtonStart_clicked()
{
  if (!m_bIsMovie) {
    return;
  }
  if (m_bIsPlaying) {
    return;
  }
  m_bIsPlaying = true;
  m_pMovie->start();
  //打印动态图默认的播放循环轮数，0 代表不循环，-1 代表无限循环
  qDebug() << tr("循环计数：%1").arg(m_pMovie->loopCount());
}


void Widget::on_pushButtonStop_clicked()
{
  if (! m_bIsMovie) { //不是动态图
    return;
  }
  if (! m_bIsPlaying) { //没有处于播放状态
    return;
  }
  //停止播放
  m_bIsPlaying = false;
  m_pMovie->stop();
}

void Widget::ClearOldShow()
{
  ui->labelShow->clear();
  if (m_pPixMap != NULL) {
    delete m_pPixMap;
    m_pPixMap = NULL;
  }
  if (m_pMovie != NULL) {
    if (m_bIsPlaying) {
      m_pMovie->stop();
    }
    delete m_pMovie;
    m_pMovie = NULL;
  }
  //标志位重置
  m_bIsMovie = false;
  m_bIsPlaying = false;
}

void Widget::RecvPlayerError(QImageReader::ImageReaderError error)
{
  //打印
  qDebug() << tr("读取动态图错误的代码：%1").arg(error);
  //提示播放出错
  QMessageBox::critical(this, tr("播放出错"),
                        tr("播放动态图出错，文件名为：\r\n%1").arg(m_pMovie->fileName()));
  //回到停止状态
  m_bIsPlaying = false;
}

void Widget::RecvPlayerFrameNumber(int frameNumber)
{
  ui->horizontalSlider->setValue(frameNumber);
}



void Widget::resizeEvent(QResizeEvent *event)
{
  //获取当前宽度、高度
  int W = event->size().width();
  int H = event->size().height();
  //先计算第二行四个按钮的左上角坐标，按钮尺寸固定为 75*23
  //第一个按钮
  int x1 = 10;            //左边距 10
  int y1 = H - 10 - 21 - 10 - 23;  // 10 都是间隔，21 是水平滑动条高度，23 是按钮高度
  //第四个按钮
  int x4 = W - 10 - 75;   //10 是右边距，75 是按钮宽度
  int y4 = y1;            //与第一个按钮同一水平线
  //计算四个按钮的三个间隙总大小
  int nTriGap = W - 10 - 10 - 75 * 4;
  //计算单个间隙
  int nGap = nTriGap / 3 ;
  //计算第二个按钮坐标
  int x2 = x1 + 75 + nGap;
  int y2 = y1;
  //计算第三个按钮左边
  int x3 = x4 - 75 - nGap;
  int y3 = y1;
  //设置四个按钮的矩形
  ui->pushButtonOpenPic->setGeometry(x1, y1, 75, 23);
  ui->pushButtonOpenMov->setGeometry(x2, y2, 75, 23);
  ui->pushButtonStart->setGeometry(x3, y3, 75, 23);
  ui->pushButtonStop->setGeometry(x4, y4, 75, 23);
  //计算第三行水平滑动条的坐标和尺寸
  int xSlider = x2;
  int ySlider = H - 10 - 21;
  int wSlider = W - x2 - 10;
  int hSlider = 21;
  //设置水平滑动条的矩形
  ui->horizontalSlider->setGeometry(xSlider, ySlider, wSlider, hSlider);
  //计算包裹标签的滚动区域占用的矩形
  int xLabel = 10;
  int yLabel = 10;
  int wLabel = W - 10 - 10;
  int hLabel = H - 10 - 21 - 10 - 23 - 10 - 10;
  //设置包裹标签的滚动区域矩形
  QScrollArea *pSA = this->findChild<QScrollArea *>();    //查找子对象
  if (pSA != NULL) {  //如果 pSA 不为 NULL 才能设置矩形
    pSA->setGeometry(xLabel, yLabel, wLabel, hLabel);
  }
}
