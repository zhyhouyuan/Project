#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
class findDialog;
}

class findDialog : public QDialog
{
    Q_OBJECT

public:
    QList<QString> getfindtext();
    //void send();
    explicit findDialog(QWidget *parent = nullptr);
    ~findDialog();

private:
    Ui::findDialog *ui;
    //bool flag;
signals:
    void sendflag(bool flag);
private slots:
    void send();
};

#endif // FINDDIALOG_H
