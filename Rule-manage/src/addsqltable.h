#ifndef ADDSQLTABLE_H
#define ADDSQLTABLE_H
//#include<QWidget>
#include <QDialog>
#include<QList>
namespace Ui {
class addsqltable;
}

class addsqltable : public QDialog
{
    Q_OBJECT

public:
    explicit addsqltable(QWidget *parent = nullptr);
    ~addsqltable();
    void datain(QList<QString>);
    QList<QString> dataout();
private:
    Ui::addsqltable *ui;
signals:
    void send_flag1(bool flag);
private slots:
    void send_1();
};

#endif // ADDSQLTABLE_H
