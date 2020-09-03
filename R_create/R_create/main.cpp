#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFile file(":/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QString(file.readAll());
    a.setStyleSheet(styleSheet);

    file.close();

    return a.exec();
}
