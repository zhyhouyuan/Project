#ifndef CHECKDIALOG_H
#define CHECKDIALOG_H

#include <QDialog>
#include <QtDebug>
#include <QLabel>
#include <QString>

class checkDialog
{
public:
    explicit checkDialog();
    ~checkDialog();
    static bool check_rule(QString rule);
    static int search_attribute(QString item);
    static bool check_maxmin(QString type, QString maxvalue,QString minvalue,QString invalue);
    static int isDigitStr(QString src);

private:
//    bool check_rule(QString rule);
signals:

public slots:
};

#endif // CHECKDIALOG_H
