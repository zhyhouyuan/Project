#ifndef GCOMBOX_H
#define GCOMBOX_H

#include <QWidget>
#include<QComboBox>
#include<QMouseEvent>
#include<QTreeView>
#include<QStandardItemModel>
class Gcombox: public QComboBox
{
    Q_OBJECT
public:
    Gcombox(QWidget *parent = 0);
    //~Gcombox();
    void setView(QTreeView *view);
    QString getParent();
    QTreeView *myview;
    void setflag(int,bool);
    void setCText(QString);
    void setModel(QStandardItemModel *model_0);

signals:
    void send_flag(int,bool);

private:
   void mousePressEvent(QMouseEvent *e);
   QStandardItemModel *model;
   //void hideEvent(QHideEvent *e);
   void hidePopup();
   int num;
   //void GetItem(QStandardItem *,QString);
   bool if_thenflag;
   //double maxvalue;
   //double minvalue;
private slots:
    void send_0();
};

#endif // GCOMBOX_H
