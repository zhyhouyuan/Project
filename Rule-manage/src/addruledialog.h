#ifndef ADDRULEDIALOG_H
#define ADDRULEDIALOG_H
#include<QTreeView>
#include <QDialog>
#include<QStandardItemModel>
#include<QDomDocument>
namespace Ui {
class addruleDialog;
}
class addruleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addruleDialog(QWidget *parent = nullptr);
    ~addruleDialog();
    QString getIf();
    QString getThen();
    QString getWeight();
    void cleartext();
    QString qukuohao(QString text);
    QString qufan(QString text);
    QDomDocument doc;
    void LoadClassifyFile();
private:

    QList<QString>redata_nat(QDomNode,QString name);
    Ui::addruleDialog *ui;
    QStandardItemModel *model;
    QStandardItemModel *model_then;
    //QStandardItemModel *modelin;
    //QTreeView *treeView;
    void additem(QDomNode itemnode,QStandardItem *item0);
    void addfuhedataitem(QStandardItem*item);
    void appendMessage(const QString &message,int);
    QTreeView *treeView ;
    QTreeView *treeView2;

    QList<QDomNode*>domlist;
   // datain0* datain_0;
    bool ifthenflag;

signals:
    void sendflag(bool flag);
private slots:

    void addcondition();
    void addresult();
    //void add_ANDOR(bool,bool);
    void add_AND1();
    void add_AND2();
    void add_OR1();
    void add_OR2();
    void send();
    void setLine_if();
    void setLine_then();
   // void setcbxdata();
    void addkh_L1();
    void addkh_R1();
    void addkh_L0();
    void addkh_R0();
    void add_NOT1();
    void add_NOT2();
   // void addAND();

};

#endif // ADDRULEDIALOG_H
