#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>

namespace Ui {
class logdialog;
}

class logdialog : public QDialog
{
    Q_OBJECT

public:
    explicit logdialog(QWidget *parent = nullptr);
    ~logdialog();
    //QString getnametext();
    QString getpassword();
    QString getusername();

private:
    Ui::logdialog *ui;
signals:
    void sendflag(bool flag);
    void send_closeflag(bool);
private slots:
    void send();
    void on_btnClose_clicked();
};

#endif // LOGDIALOG_H
