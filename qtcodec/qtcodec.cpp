// qtcodec.cpp
#include <QApplication>
#include <QDebug>
#include <QString>
#include <QTextBrowser>
#include <iostream>

using namespace std;

void Testcout(const QString &str) {
  // Locale charset
  cout << str.toLocal8Bit().data() << endl;

  // UTF-8
  cout << str.toUtf8().data() << endl;
  cout << str.toStdString() << endl;

  // UTF-16, Windows Unicode, UCS2
  cout << str.unicode() << endl;
  cout << str.utf16() << endl;
  cout << str.data() << endl;

  // UTF-32, UCS4
  cout << str.toUcs4().data() << endl;

  // wchar_t: Windows = UTF-16; Linux/Unix = UTF-32
  wcout << str.toStdWString();

  cout << endl << endl;
}

void TestqDebug(const QString &str) {
  // Locale charset
  qDebug() << str.toLocal8Bit().data();

  // UTF-8
  qDebug() << str.toUtf8().data();
  qDebug() << str.toStdString().data();

  // UTF-16, Windows Unicode, UCS2
  qDebug() << str.unicode();
  qDebug() << str.utf16();
  qDebug() << str.data();

  // UTF-32, UCS4
  qDebug() << str.toUcs4().data();

  // wchar_t: Windows = UTF-16; Linux/Unix = UTF-32
  qDebug() << str.toStdWString().data();

  // QString object
  qDebug() << str;
}

void Test_operator() {

  // =

  QString strE1, strE2, strE3;

  strE1 = QObject::tr("abcd");

  strE2 = strE1;

  strE3 = strE2;

  //打印数据指针

  qDebug() << strE1.data_ptr() << "\t" << strE2.data_ptr() << "\t"
           << strE3.data_ptr();

  //改变字符串，追加

  strE2.append(QObject::tr("1234"));

  //再次打印数据指针，谁修改了数据，谁的数据指针就变

  qDebug() << strE1.data_ptr() << "\t" << strE2.data_ptr() << "\t"
           << strE3.data_ptr();

  // += 和 append 函数类似

  strE3 += QObject::tr("1234");

  qDebug() << strE2 << "\t" << strE3;

  //比较 1 vs 2

  qDebug() << "strE1 < strE2: " << (strE1 < strE2);

  qDebug() << "strE1 <= strE2: " << (strE1 <= strE2);

  qDebug() << "strE1 == strE2: " << (strE1 == strE2);

  qDebug() << "strE1 != strE2: " << (strE1 != strE2);

  // 2 vs 3

  qDebug() << "strE2 > strE3" << (strE2 > strE3);

  qDebug() << "strE2 >= strE3" << (strE2 >= strE3);

  qDebug() << "strE2 == strE3" << (strE2 == strE3);

  //类似数组取数

  qDebug() << strE1[0];

  strE1[0] = QChar('?'); //修改

  qDebug() << strE1;

  //拼接

  QString strPlus;

  strPlus = strE1 + strE2 + strE3;

  qDebug() << strPlus;
}

void Test_QTextStream()

{

  //内存输出流

  QString strOut;

  QTextStream streamOut(&strOut);

  //打印多种进制数字

  streamOut << 800 << endl;

  streamOut << hex << 127 << endl;

  streamOut << oct << 63 << endl;

  //还原为十进制

  streamOut << dec;

  //设置域宽和填充字符

  streamOut << qSetFieldWidth(8) << qSetPadChar('0') << 800;

  //还原默认域宽和填充

  streamOut << qSetFieldWidth(0) << qSetPadChar(' ') << endl;

  //设置精度

  streamOut << qSetRealNumberPrecision(3) << fixed << 123.789999 << endl;

  streamOut << qSetRealNumberPrecision(6) << scientific << 123.789999 << endl;

  //打印字符串和数字混搭

  streamOut << QObject::tr("7*7 == ") << 7 * 7 << endl;

  //显示现在的字符串对象

  qDebug() << strOut;

  //内存输入流

  QString strIn = QObject::tr("800  abcd  123.789999");

  QTextStream streamIn(&strIn);

  int numDec = 0;

  QString strSub;

  double dblReal = 0.0;

  //输入到变量里

  streamIn >> numDec >> strSub >> dblReal;

  //显示

  qDebug() << numDec;

  qDebug() << strSub;

  qDebug() << fixed << dblReal; //定点数显示
}

int main(int argc, char *argv[]) {
  //  QApplication a(argc, argv);
  //  QString strText = QObject::tr("1234打印汉字");
  //  QTextBrowser tb;
  //  tb.setText(strText);
  //  tb.setGeometry(40, 40, 400, 300);
  //  tb.show();

  // Test cout
  // Testcout(strText);

  // Test qDebug
  //  TestqDebug(strText);

  // Test_operator
  //  Test_operator();

  //    Test_QTextStream
  Test_QTextStream();
  //  return a.exec();
}
