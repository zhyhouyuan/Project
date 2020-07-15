#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include<QAbstractTableModel>
#include<QSqlTableModel>
#include<QDomDocument>
#include"rule_fact.h"
class viewmodel:public QAbstractTableModel
{
    Q_OBJECT
public:
    //viewmodel();
    viewmodel(QObject * parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role );
    bool removeRow(int arow);
    //QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    //Qt::ItemFlags flags(const QModelIndex &index) const;
    void setview(QList<QSqlTableModel*>);
    QVariant setview_0(QList<QSqlTableModel*>);
    //void checkout();
    QSqlRecord getrecord(int);
    bool findrecord(QList<QString> namelist);
    bool addrecord(QList<QString>,int);
    bool setrecord(QSqlRecord,int);
    //void settransmodel(QString,QSqlDatabase);
    QString ChtoEnl(QString)const;
    QString EnltoCh(QString)const;
    QString transRule(QString ch,int flag)const;
    void updata();
    bool removeRow_checked();
    void WriteXml(QString dirPath);
    bool submit_checked();
    void sub_fact(QString ch,bool ad_de);

    QList<int>listnum;

    QList<QSqlTableModel*>modellist0;
    //QList<QAbstractTableModel*>modellist1;
    QSqlTableModel *EntoCh;
    Rule_fact  *rulefact;
    QMap<int, Qt::CheckState> check_state_map;
    QList<QList<QString>>Tablehead;
    int rowcount;
    int columncount;
    bool disflag,open_close;
signals:
    void sendRowchanged(bool flag);
private:
    int checkrecord(QString if_text,QString then_text,QSqlTableModel*checkmodel);
    void addxmlnode(QDomDocument doc,QDomElement node,QString data_0,QString noname);
    void add_div_rule(QDomDocument doc, QSqlRecord record_out,QDomElement node);
    QList<QList<QVariant*>*>datalist;
};



#endif // VIEWMODEL_H
