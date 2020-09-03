#ifndef M_TREEVIEW_H
#define M_TREEVIEW_H
#include <QList>
#include<QTreeView>
#include <QPersistentModelIndex>
#include<QStandardItemModel>
#include<QMap>
#include"viewmodel.h"
#include"node.h"
#include<QMap>
class M_TreeView:public QTreeView
{
    Q_OBJECT
public:
    explicit M_TreeView(QWidget *parent = nullptr);
   // bool setData( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
    QList<QPersistentModelIndex> m_checkedList;
    //QMap<QString,int> checkmap;
    //QVariant data(const QModelIndex &index, int role) const;
   // Qt::ItemFlags flags(const QModelIndex &index) const;
    void treeItem_checkAllChild(QStandardItem * item, bool check);
    void treeItem_checkAllChild_recursion(QStandardItem * item,bool check);
    void treeItem_CheckChildChanged(QStandardItem * item);
    Qt::CheckState checkSibling(QStandardItem * item);
    void initmodel();
    QStandardItem* addmodelItem(QStandardItem*item0,QStringList*list0);
    //QStandardItem* findchilditem(QStandardItem *parent,QString text);
    void clealmodel();
    void LoadScape(QSqlTableModel*modelroot);
    void additem(QDomNode itemnode,QStandardItem *item0);
    void updata_node();
    QStandardItemModel* model;
    //Node*node_r,*node_b;
    QMap<QStandardItem*,int>item_table;//item-ID
    QMap<int,QString>item_tablename;
    QMap<QString,QStandardItem*>name_item;//编队；
    QMap<int,QStringList>headnamelist;
    QMap<int,int>IDlist_red,IDlist_blue;
    QMap<int,int>CheckList;//ID_选择次数
signals:
    void sendChange(bool flag);
public slots:
    void treeItemChanged(QStandardItem*item);
private:
    QSqlTableModel*model_root;
    bool rb_flg;
    bool a_flag;

};


#endif // M_TREEVIEW_H
