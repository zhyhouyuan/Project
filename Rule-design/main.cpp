#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QTextEdit>
#include <QtGui>
#include<iostream>
#include<istream>

bool updataflag=0;
using namespace std;

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    static QMutex mutex;
    mutex.lock();
    QString text;
    switch(type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
    }
    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);
    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();
    mutex.unlock();
}
void clearlog(){
    QFile filelog("log.txt");
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
  //  std::cout<<current_date_time;
    if(filelog.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream text_stream(&filelog);
        QString Lasttime=text_stream.readLine(0);
        filelog.close();
        //qDebug()<<Lasttime;
        if(Lasttime.isEmpty()){
            updataflag=1;
        }
        else{
           long long daylen=QDateTime::currentDateTime().daysTo(QDateTime::fromString(Lasttime,"yyyy-MM-dd hh:mm:ss ddd"));
                    //.daysTo(QDateTime::fromString(Lasttime));
           // qDebug()<<daylen<<QDateTime::fromString(Lasttime,"yyyy-MM-dd hh:mm:ss ddd");
            if(abs(daylen)>=10){
                updataflag=1;
                filelog.open(QIODevice::WriteOnly | QIODevice::Text|QFile::Truncate);
                filelog.close();
             }
        }
    }
    else{
        updataflag=1;
    }
    if(updataflag==1){
        filelog.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream text_stream(&filelog);
        text_stream << current_date_time << "\r\n";
        filelog.close();
    }
}
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("规则设计软件");//设置应用程序名称
    app.setApplicationVersion("V1.0");//设置应用程序版本
     clearlog();
    //myHelper::SetUTF8Code();
    qApp->setStyle("Plastique");
    qApp->setStyleSheet("QLineEdit{border:1px groove gray;border-radius:6px;}");
    //加载中文字符
    QTranslator translator;
    translator.load(":/image/qt_zh_CN.qm");
    app.installTranslator(&translator);

    //注册MessageHandler
     qInstallMessageHandler(outputMessage); //注册MessageHandler

    QApplication::addLibraryPath("./plugins");
    //赋值当前应用程序路径
    MainWindow w;
     w.show();
     QFile file(":/style.qss");
     file.open(QFile::ReadOnly);
     QString styleSheet = QString(file.readAll());
     app.setStyleSheet(styleSheet);

     file.close();
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

