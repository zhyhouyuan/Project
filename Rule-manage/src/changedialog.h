#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H
#include<QTreeView>
#include <QDialog>
#include<QDomDocument>
#include "datain0.h"
#include <QDialog>
#include<QSqlRecord>
#include<QStandardItemModel>
#include<QFileDialog>
#include<QMenu>
#include"gcombox.h"
#include<QTableWidgetItem>
namespace Ui {
class changeDialog;
}

class changeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit changeDialog(QWidget *parent = nullptr);
    ~changeDialog();
    void setRuleData(QSqlRecord*);
    bool getRuleData(QSqlRecord*);
    QSqlRecord *record_ze;
    void combox_rn();
    static QStringList StringSplit(QString);
    QDomDocument doc;
signals:
    void send_chflag(bool chflag);
private:
    Ui::changeDialog *ui;

    QStandardItemModel *model;
    QStandardItemModel *model_then;
    bool LoadClassifyFile();
     void additem(QDomNode itemnode,QStandardItem *item0);
     void addfuhedataitem(QStandardItem *item0);
     void createActions();


    //datain0 *datain_0;
    QMenu          *m_topMenu;
    QAction        *m_actAdd;
    QAction        *m_actDel;
    QMenu          *m_topMenu_2;
    QAction        *m_actAdd_2;
    QAction        *m_actDel_2;
    bool            ifthenflag;
    QList<Gcombox*> if_boxlist;
    int   RuleID;
    bool  init_fg;
    bool  first_fg;
private slots:
    void send_ch();
    //void setvale_if(QTableWidgetItem *item);
    //void setvale_then(int,int);
    void onUpdateContextMenu(QPoint pos);
    void onUpdateContextMenu2(QPoint pos);
    void add_if();
    void del_if();
    void add_then();
    void del_then();
    //void setfhdata();
    void set_value(int i,bool flag);

};

#endif // CHANGEDIALOG_H
