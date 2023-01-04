// qtcodec.cpp
#include <QApplication>
#include <QDebug>
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

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QString strText = QObject::tr("1234打印汉字");
  QTextBrowser tb;
  tb.setText(strText);
  tb.setGeometry(40, 40, 400, 300);
  tb.show();
  // Test cout
  //    Testcout(strText);
  // Test qDebug
  TestqDebug(strText);

  return a.exec();
}
