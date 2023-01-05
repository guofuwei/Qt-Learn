//testqbytearray.cpp
#include <QApplication>
#include <QTextBrowser>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>
#include <QTextCodec>

void TestStr()  //内码 UTF-8
{
    //数值与字符串转换
    int nDec = 800;
    QByteArray basDec;
    basDec.setNum(nDec);    //数值转字符串
    qDebug()<<basDec;
    QByteArray basReal = "125.78999";
    double dblReal = basReal.toDouble();    //字符串转数值
    qDebug()<<fixed<<dblReal;

    //运算符
    QByteArray basABCD = "ABCD";
    QByteArray basXYZ = "XYZ";
    qDebug()<<(basABCD < basXYZ);   //二者字符编码一致才能比较！
    qDebug()<<(basABCD == basXYZ);
    qDebug()<<(basABCD >= basXYZ);
    qDebug()<<(basABCD + basXYZ);

    //子串处理
    QByteArray basHanzi = "1234打印汉字";
    //作为字符串时 QByteArray::length() 和 qstrlen() 一致
    qDebug()<<basHanzi.length()<<"\t"<<qstrlen( basHanzi.data() );
    //重复
    QByteArray basMoreHanzi = basHanzi.repeated(2);
    qDebug()<<basMoreHanzi.count("1234"); //统计次数
    qDebug()<<basMoreHanzi.startsWith("1234");  //开头判断
    qDebug()<<basMoreHanzi.endsWith("汉字");     //结尾判断
    qDebug()<<basMoreHanzi.indexOf("1234");   //从左边查出现位置
    qDebug()<<basMoreHanzi.lastIndexOf("1234"); //从右边查出现位置
    //替换
    basMoreHanzi.replace("1234", "一二三四");
    qDebug()<<basMoreHanzi;

    //切割字符串
    QByteArray basComplexFile = "   /home/user/somefile.txt  \t\t ";
    QByteArray basFileName = basComplexFile.trimmed();  //剔除两端空白
    qDebug()<<basFileName;
    //分隔得到新的 QByteArray 对象列表
    QList<QByteArray> baList = basFileName.split('/');
    //打印
    for(int i=0; i<baList.length(); i++)
    {
        qDebug()<<i<<"\t"<<baList[i];
    }
    //没有段落函数
}

/*
//C++ 结构体方法
struct NetData
{
    int nVersion;
    double dblValue;
    char strName[256];
};
*/
//Qt 串行化方法
QByteArray TestSerialOut()
{
    //数据
    int nVersion = 1;
    double dblValue = 125.78999;
    QString strName = QObject::tr("This an example.");
    //字节数组保存结果
    QByteArray baResult;
    //串行化的流
    QDataStream dsOut(&baResult, QIODevice::ReadWrite);  //做输出，构造函数用指针
    //设置Qt串行化版本
    dsOut.setVersion(QDataStream::Qt_5_0);//使用Qt 5.0 版本流
    //串行化输出
    dsOut<<nVersion<<dblValue<<strName;

    //显示长度
    qDebug()<<baResult.length()<<"\t"<<qstrlen(baResult.data());
    //返回对象
    return baResult;
}

void TestSerialIn(const QByteArray& baIn)
{
    //输入流
    QDataStream dsIn(baIn); //只读的流，构造函数用常量引用
    //设置Qt串行化版本
    dsIn.setVersion(QDataStream::Qt_5_0);//使用Qt 5.0 版本流
    //变量
    int nVersion;
    double dblValue;
    QString strName;
    //串行化输入
    dsIn>>nVersion>>dblValue>>strName;

    //打印
    qDebug()<<nVersion;
    qDebug()<<fixed<<dblValue;
    qDebug()<<strName;
}

//测试协作
void TestCooperation()
{
    //源字符串
    QString strSrc = QObject::tr("1234abcd 千秋萬載 壹統江湖");
    //转为 UTF-8
    qDebug()<<strSrc.toUtf8();

    //明确地转为 GB18030
    QTextCodec *codecGB = QTextCodec::codecForName("GB18030");
    QByteArray strGB = codecGB->fromUnicode(strSrc); //转为GB18030
    qDebug()<<strGB;
    qDebug()<<codecGB->toUnicode(strGB);  //转回QString

    //明确地转为 Big5
    QTextCodec *codecBig5 = QTextCodec::codecForName("Big5");
    QByteArray strBig5 = codecBig5->fromUnicode(strSrc); //转为Big5
    qDebug()<<strBig5;
    qDebug()<<codecBig5->toUnicode(strBig5);    //转回QString
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString strText = QObject::tr("测试 QByteArray");
    QTextBrowser tb;
    tb.setText(strText);
    tb.setGeometry(40, 40, 400, 300);
    tb.show();

    //str
    TestStr();
    qDebug()<<endl;

    //serialization
    QByteArray baSerial = TestSerialOut();
    //baSerial 可用于网络发送
    //接收到 baSerial 之后解析
    TestSerialIn(baSerial);
    qDebug()<<endl;

    //测试协作
    TestCooperation();

    return a.exec();
}
