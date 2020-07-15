#ifndef CHANGE_WDIALOG_H
#define CHANGE_WDIALOG_H

#include <QDialog>

namespace Ui {
class Change_WDialog;
}

class Change_WDialog : public QDialog
{
    Q_OBJECT

public:
    explicit Change_WDialog(QWidget *parent = nullptr);
    ~Change_WDialog();
    void set_wdata(int);

private:
    Ui::Change_WDialog *ui;
signals:
    void send_chflag(int value);
private slots:
    void send_ch();
};

#endif // CHANGE_WDIALOG_H
