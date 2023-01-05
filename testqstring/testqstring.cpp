//testqstring.cpp
#include <QApplication>
#include <QTextBrowser>
#include <QDebug>
#include <QTextStream>

void Test_setNum()
{
    QString strTest;
    //to Hex string
    short numHex = 127;
    strTest.setNum(numHex, 16);
    qDebug()<<"Hex: "<<strTest;

    //to Oct string
    int numOct = 63;
    strTest.setNum(numOct, 8);
    qDebug()<<"Oct: "<<strTest;

    //to normal Dec string
    long numDec = 800;
    strTest.setNum(numDec);
    qDebug()<<"Normal: "<<strTest;

    //to float string
    float numFixed = 123.78999;
    strTest.setNum(numFixed, 'f', 3);
    qDebug()<<"Fixed: "<<strTest;

    //to scientific double string
    double numScientific = 456.78999;
    strTest.setNum(numScientific, 'e', 6);
    qDebug()<<"Scientific: "<<strTest;
}

void Test_arg()
{
    //使用 strResult 存储 arg 返回的新对象
    QString strResult;

    //Dec
    long numDec = 800;
    QString strMod = QObject::tr("Normal: %1");
    strResult = strMod.arg(numDec);  //%1是占位符，第一个arg函数参数变量转后的字符串填充到 %1 位置
    qDebug()<<"Mod: "<<strMod<<" \t Result: "<<strResult;

    //Oct
    int numOct = 63;
    strResult = QObject::tr("Oct: %1").arg(numOct, 4, 8, QChar('0'));  //numOct转换后为4字符域宽，8进制，填充0
    qDebug()<<strResult;

    //Hex
    short numHex = 127;
    QString strPrefix = QObject::tr("0x");
    //占位符里可填充数值转的字符串，也可以直接填充原有的字符串
    strResult = QObject::tr("Hex: %1%2").arg(strPrefix).arg(numHex, 0, 16);  //串联：第一个arg函数参数填充到%1，第二个arg填充到%2
    qDebug()<<strResult;

    //double
    double numReal = 123.78999;
    strResult = QObject::tr("Fixed: %1 \t Scientific: %2").arg(numReal, 0, 'f').arg(numReal, 0, 'e', 3);
    qDebug()<<strResult;

    //占位符可重复，也可乱序
    int one = 1;
    int two = 2;
    int three = 3;
    strResult = QObject::tr("%1 小于 %2，%1 小于 %3，%3 大于 %2 。").arg(one).arg(two).arg(three);
    qDebug()<<strResult;
}

void Test_toValue()
{
    bool bok = false;
    //dec
    QString strDec = QObject::tr("800");
    int nDec = strDec.toInt(&bok, 10);
    qDebug()<<nDec<<"\t"<<bok;       //成功
    //Hex
    QString strHex = QObject::tr("FFFF");
    nDec = strHex.toInt(&bok, 10);  //基数错误，转换失败
    qDebug()<<nDec<<"\t"<<bok;

    short nHexShort = strHex.toShort(&bok, 16);
    qDebug()<<nHexShort<<"\t"<<bok; //FFFF正整数太大，超出范围，转换失败，没有负号 - 的都算正数。

    ushort nHexUShort = strHex.toUShort(&bok, 16);
    qDebug()<<nHexUShort<<"\t"<<bok;//成功

    //自动转换
    QString strOct = QObject::tr("0077");
    int nOct = strOct.toInt(&bok, 0);
    qDebug()<<nOct<<"\t"<<bok;  //字符 0 打头自动按八进制转

    QString strHexWithPre = QObject::tr("0xFFFF");
    int nHexWithPre = strHexWithPre.toInt(&bok, 0);
    qDebug()<<nHexWithPre<<"\t"<<bok;   //字符 0x 打头自动按十六进制转

    int nDecAuto = strDec.toInt(&bok, 0);   //"800" ，自动按十进制
    qDebug()<<nDecAuto<<"\t"<<bok;

    //浮点数转换
    QString strFixed = QObject::tr("123.78999");
    double dblFixed = strFixed.toDouble(&bok);
    qDebug()<<fixed<<dblFixed<<"\t"<<bok;
    //科学计数法
    QString strScientific = QObject::tr("1.238e-5");
    double dblScientific = strScientific.toDouble(&bok);
    qDebug()<<scientific<<dblScientific<<"\t"<<bok;
}

void Test_operator()
{
    // =
    QString strE1, strE2, strE3;
    strE1 = QObject::tr("abcd");
    strE2 = strE1;
    strE3 = strE2;
    //打印数据指针
    qDebug()<<strE1.data_ptr()<<"\t"<<strE2.data_ptr()<<"\t"<<strE3.data_ptr();
    //改变字符串，追加
    strE2.append( QObject::tr("1234") );
    //再次打印数据指针，谁修改了数据，谁的数据指针就变
    qDebug()<<strE1.data_ptr()<<"\t"<<strE2.data_ptr()<<"\t"<<strE3.data_ptr();

    // += 和 append 函数类似
    strE3 += QObject::tr("1234");
    qDebug()<<strE2<<"\t"<<strE3;

    //比较 1 vs 2
    qDebug()<<"strE1 < strE2: "<<(strE1 < strE2);
    qDebug()<<"strE1 <= strE2: "<<(strE1 <= strE2);
    qDebug()<<"strE1 == strE2: "<<(strE1 == strE2);
    qDebug()<<"strE1 != strE2: "<<(strE1 != strE2);
    //2 vs 3
    qDebug()<<"strE2 > strE3"<<(strE2 > strE3);
    qDebug()<<"strE2 >= strE3"<<(strE2 >= strE3);
    qDebug()<<"strE2 == strE3"<<(strE2 == strE3);

    //类似数组取数
    qDebug()<<strE1[0];
    strE1[0] = QChar('?');  //修改
    qDebug()<<strE1;

    //拼接
    QString strPlus;
    strPlus = strE1 + strE2 + strE3;
    qDebug()<<strPlus;
}

void Test_substring()
{
    QString strOne = QObject::tr("abcd");
    QString strThree = strOne.repeated(3); //abcd 重复三次
    qDebug()<<strThree.isEmpty();   //是否为空
    qDebug()<<strThree.length()<<"\t"<<strThree.size(); //都是长度
    qDebug()<<strThree;

    //子串查询
    qDebug()<<strThree.contains(strOne);    //是否包含
    qDebug()<<strThree.count(strOne);       //包含几个
    qDebug()<<strThree.startsWith(strOne);  //打头的子串
    qDebug()<<strThree.indexOf(strOne);     //左边开始的子串位置
    qDebug()<<strThree.lastIndexOf(strOne); //右边开始的子串位置

    //剔除两端的空白
    QString strComplexFileName = QObject::tr("   /home/user/somefile.txt  \t\t ");
    QString strFileName = strComplexFileName.trimmed();
    qDebug()<<strFileName;
    if(strFileName.endsWith( QObject::tr(".txt") ))
    {
        qDebug()<<"This is a .txt file";
    }
    //分隔子串
    QStringList subsList = strFileName.split(QChar('/'));
    for(int i=0; i<subsList.length(); i++)  //打印各个子串
    {
        qDebug()<<i<<"\t"<<subsList[i];
    }
    //获取段落
    QString subsections = strFileName.section(QChar('/'), 2, 3);
    qDebug()<<subsections;
}

void Test_QTextStream()
{
    //内存输出流
    QString strOut;
    QTextStream streamOut(&strOut);
    //打印多种进制数字
    streamOut<<800<<endl;
    streamOut<<hex<<127<<endl;
    streamOut<<oct<<63<<endl;
    //还原为十进制
    streamOut<<dec;

    //设置域宽和填充字符
    streamOut<<qSetFieldWidth(8)<<qSetPadChar('0')<<800;
    //还原默认域宽和填充
    streamOut<<qSetFieldWidth(0)<<qSetPadChar(' ')<<endl;

    //设置精度
    streamOut<<qSetRealNumberPrecision(3)<<fixed<<123.789999<<endl;
    streamOut<<qSetRealNumberPrecision(6)<<scientific<<123.789999<<endl;

    //打印字符串和数字混搭
    streamOut<<QObject::tr("7*7 == ")<<7*7<<endl;
    //显示现在的字符串对象
    qDebug()<<strOut;


    //内存输入流
    QString strIn = QObject::tr("800  abcd  123.789999");
    QTextStream streamIn(&strIn);
    int numDec = 0;
    QString strSub;
    double dblReal = 0.0;
    //输入到变量里
    streamIn>>numDec>>strSub>>dblReal;
    //显示
    qDebug()<<numDec;
    qDebug()<<strSub;
    qDebug()<<fixed<<dblReal;   //定点数显示
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString strText = QObject::tr("测试字符串类 QString");
    QTextBrowser tb;
    tb.setText(strText);
    tb.setGeometry(40, 40, 400, 300);
    tb.show();

    //setNum
//    Test_setNum();

    //arg
    Test_arg();

    //toValue
    //Test_toValue();

    //operator
    //Test_operator();

    //substring
    //Test_substring();

    //QTextStream
    //Test_QTextStream();

    return a.exec();
}
