#ifndef DATAIN0_H
#define DATAIN0_H
#include <QWidget>
#include <QDialog>
#include<QDomDocument>
#include<QComboBox>
namespace Ui {
class datain0;
}

class datain0 : public QDialog
{
    Q_OBJECT

public:
    explicit datain0(QWidget *parent = nullptr);
    ~datain0();
    void settable(QDomElement);
    QString getalltext();
    QList<QComboBox*> CBox_list;
    QList<QComboBox*> DBox_list;
signals:
    void send_flag(bool flag);
private:
    Ui::datain0 *ui;
    QList<QString> datatypelist;
    QList<QString> maxvalue;
    QList<QString> minvalue;
    QList<QString> dwlist;
private slots:
    void send_0();


};

#endif // DATAIN0_H
