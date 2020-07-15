#include "src/mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>
#include <QtGui>
#include<iostream>
#include<istream>
#include"srcsq/datamanage.h"
#include"srcsq/connectionpool.h"
using namespace std;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("规则库管理软件");//设置应用程序名称
    app.setApplicationVersion("V1.0");//设置应用程序版本

    //myHelper::SetUTF8Code();
    qApp->setStyle("Plastique");
    qApp->setStyleSheet("QLineEdit{border:1px groove gray;border-radius:6px;}");
    //加载中文字符
    QTranslator translator;
    translator.load(":/image/qt_zh_CN.qm");
    app.installTranslator(&translator);

    QApplication::addLibraryPath("./plugins");


    MainWindow w;
    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString(file.readAll());
    app.setStyleSheet(styleSheet);

    w.show();


    file.close();
    return app.exec();
}

