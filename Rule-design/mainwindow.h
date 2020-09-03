#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSplitter>
#include"uisrc/scene.h"
#include"uisrc/finddialog.h"
#include"uisrc/logdialog.h"
//#include"node.h"
#include"src/m_treeview.h"
#include <QQueue>
#include <QMouseEvent>
#include <windows.h>        //注意头文件
#include <windowsx.h>
#include"src/connectionpool.h"
#include"src/viewmodel.h"
#include"uisrc/addruledialog.h"
#include"uisrc/changedialog.h"
#include"uisrc/addsqltable.h"
#include<QTreeWidgetItem>
#include <QCloseEvent>
#include"uisrc/change_wdialog.h"
#include "uisrc/titlebar.h"
#include"uisrc/tiltleitem.h"
class Node;
class Link;
class QMenu;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Scene *getruleScene();
    void itemsMove(Node*node);
    Node*getSelectedNode();
    void ruledsp(bool);


    void addCHtoEN(QDomElement );

    Node* onAdd(Node*fromNode,QString name,bool rb);
    QList<Node*> findlastnode(Node*node,QList<Node*>nodelist);
    //void adjustNodes(Node *fromNode, int nodeSpace);
    void adjustnode(bool);
    Node*findnextnode(Node*node,QString data0,bool);
    void changeTable(Node*);
    void chatables();
    void addtable(Node*,bool);
    void createActions();
    void initViewActions();
    void loadLandscape_D();
    //bool add_sqltable(QString);

    //void checkchildnode(int row,int cloum,QStandardItem *item,bool rbf);
    //void addwindowshow_node(QStringList);

    QSqlDatabase db;
    //QList<mytablemodel*> model;
    QList<QSqlTableModel*> modelin;
    QList<QSqlTableModel*> model_display;
    QSqlTableModel *modelroot;
    viewmodel *myviewmodel;
    //QSqlTableModel *modellandscape;

private:
    Ui::MainWindow *ui;
    const int boundaryWidth =4;
    void Pushbuttonable(bool);
    void setItemList(QComboBox*a,QComboBox*prea,QList<Node*>&list0,QList<Node*>&list1,int);
    QPoint clickPos;
    //QSplitter *Splitter;
    //QGraphicsView  *m_view;
    Scene          *m_scene;
    QList<Node *>  m_node_red,m_node_blue;
    QQueue<Link *>  m_link;

   QList<tiltleItem*>     T_item;

    //findDialog    *m_findwindow;
    logdialog     *m_logwindow;
    Change_WDialog *m_chang_W;
    addruleDialog *addwindow;
    changeDialog *changewindow;
    //addsqltable *add_table0;
    QMenu          *m_topMenu;
    QAction        *m_actAdd;
    QAction        *m_actDis;
    QAction        *m_actSubmit;
    //QAction        *m_actFind;
    QAction        *m_actBack;
    TitleBar *pTitleBar;

    QDomDocument doc;

    int   adjust_n;
    int    cupos;
    bool rootflag;
    bool flag_find;
    bool dis_flag0;
    QList<int> idlist_r,idlist_b;
    QString currentTablename;
   // QList<Node*> findlist1;
    QList<Node*>  findlist1,findlist2,findlist3,findlist4,findlist5;
    QSlider*m_slider;
private slots:
    void m_submit_clicked();
    void m_findshow();
    void m_logshow();
    void m_dismiss_clicked();
    void loadLandscape();
    void LoadClassifyFile();
    void m_find_clicked();
    void m_change_clicked();
    void onUpdateContextMenu(QPoint);
    void adjustscene(int);
    void rulebaseload();
    void m_out_clicked();
    void on_listWidget_pressed();
    void oncheck_clicked();
    void oncheckall_clicked(int);
    void addwindowshow();
    void m_addrule();
    void Returnroottable();
    //void updateID();
    void changerule();
    void change_W(int);
    //void findrulebase();
    void change_Wclicked();
    void setcomboxitem(int);
    void m_submit_W();
    void hideheadname();
    void changeTable_item(QModelIndex);
    void open_close(int);
    void item_upcheck();
protected:
    bool loadfile;
//    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
//    void mousePressEvent(QMouseEvent *e);
//     //void mouseMoveEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H
