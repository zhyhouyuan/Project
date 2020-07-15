#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>
#include <QtGui>
#include<iostream>
#include<istream>


//#include <QThread>
//class MyThread : public QThread
//{
//public:
//    void run()
//    {
//        qDebug() << "QThread begin" << endl;
//        qDebug() << "child thread" << QThread::currentThreadId() << endl;
//        QThread::sleep(5);
//        qDebug() << "QThread end"   << endl;
//        exec();
//    }
//};

using namespace std;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("规则设计软件");//设置应用程序名称
    app.setApplicationVersion("V1.0");//设置应用程序版本

    //myHelper::SetUTF8Code();
    qApp->setStyle("Plastique");
    qApp->setStyleSheet("QLineEdit{border:1px groove gray;border-radius:6px;}");
    //加载中文字符
    QTranslator translator;
    translator.load(":/image/qt_zh_CN.qm");
    app.installTranslator(&translator);
   // qDebug()<<qApp->applicationDirPath()<<"a";
    QApplication::addLibraryPath("./plugins");
    //赋值当前应用程序路径
//   myApp::AppPath=QApplication::applicationDirPath()+"/";
//   myApp::ReadConfig();
  //  QFont font  = app.font();
     //   font.setPointSize(12);
    //    app.setFont(font);
    MainWindow w;
     w.show();
     QFile file(":/style.qss");
     file.open(QFile::ReadOnly);
     QString styleSheet = QString(file.readAll());
     app.setStyleSheet(styleSheet);

     file.close();
     //qDebug()<<QThread::currentThreadId();
//    MyThread thread;
//        thread.start();
//        qDebug() << "main thread" << QThread::currentThreadId() << endl;

//        QThread::sleep(5);

//        qDebug() << "main thread" << QThread::currentThreadId() << endl;
//        thread.quit();
//        qDebug() << "main thread thread.quit()" << endl;
//        thread.wait();
//        qDebug() << "main thread thread.wait()" << endl;



    return app.exec();
}

