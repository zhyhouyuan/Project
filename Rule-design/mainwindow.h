#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSplitter>
#include"scene.h"
#include"finddialog.h"
#include"logdialog.h"
//#include"node.h"
#include <QQueue>
#include <QMouseEvent>
#include <windows.h>        //注意头文件
#include <windowsx.h>
#include"connectionpool.h"
#include"viewmodel.h"
#include"addruledialog.h"
#include"changedialog.h"
#include"addsqltable.h"
#include<QTreeWidgetItem>
#include <QCloseEvent>
#include"change_wdialog.h"
#include "titlebar.h"
#include"tiltleitem.h"
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

    void LoadClassifyFile();
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
    bool add_sqltable(QString);

    void checkchildnode(int row,int cloum,QTreeWidgetItem *item,bool rbf);
    //void addwindowshow_node(QStringList);
    QTreeWidgetItem* findchilditem(QTreeWidgetItem *parent,QString text);
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
    addsqltable *add_table0;
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
    Node  *findnode1,*findnode2,*findnode3,*findnode4,*findnode5;
private slots:
    void m_submit_clicked();
    void m_findshow();
    void m_logshow();
    void m_dismiss_clicked();
    void loadLandscape();
    void loadLandscape_D();
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
    void updateID();
    void changerule();
    void change_W(int);
    void findrulebase();
    void change_Wclicked();
    void setcomboxitem(int);
    void m_submit_W();
    void hideheadname();
    void changeTable_item(QModelIndex);
    void open_close(int);
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *e);
     //void mouseMoveEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H
