#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QSplitter>
#include"srcsq/scene.h"

#include <QMouseEvent>
#include <windows.h>        //注意头文件
#include <windowsx.h>
#include"finddialog.h"
#include"logdialog.h"
//#include"node.h"
#include <QQueue>
#include"srcsq/connectionpool.h"
#include"srcsq/viewmodel.h"
#include"addruledialog.h"
#include"changedialog.h"
#include"addsqltable.h"
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
    void ruledsp();
     void LoadClassifyFile();
    void onAdd(Node*fromNode,QString name);
    QList<Node*> findlastnode(Node*node,QList<Node*>nodelist);
    //void adjustNodes(Node *fromNode, int nodeSpace);
    void adjustnode();
    Node*findnextnode(Node*node,QString data0);
    void changeTable(Node*);
    void chatables();
    void addtable(Node*,bool);
    void createActions();
    void initViewActions();
    void addCHtoEN(QDomElement);

    bool add_sqltable(QString);
    void del_sqltable(QString);

    void addwindowshow_node(QStringList);
    QSqlDatabase db;
    //QList<mytablemodel*> model;
    QList<QSqlTableModel*> modelin;
    QList<QSqlTableModel*> model_display;
    QSqlTableModel *modelroot;
    viewmodel *myviewmodel;
private:
    Ui::MainWindow *ui;
    int boundaryWidth;
    QPoint clickPos;

    Scene          *m_scene;
    QList<Node *>  m_nodeQueue;
    QQueue<Link *>  m_link;
    QList<tiltleItem*>     T_item;
    findDialog    *m_findwindow;
    logdialog     *m_logwindow;

    addruleDialog *addwindow;
    changeDialog *changewindow;
    addsqltable *add_table0;
    QMenu          *m_topMenu;
    QAction        *m_actAdd;
    QAction        *m_actDel;
    QAction        *m_actDis;
    QAction        *m_actSubmit;
    //QAction        *m_actFind;
    QAction        *m_actBack;
    TitleBar      *pTitlebar;

    Node  *findnode1,*findnode2,*findnode3,*findnode4,*findnode5;

    QDomDocument doc;

    bool               menuflag;
    int   adjust_n;
    bool rootflag;
    QString currentTablename;

//    QAction        *m_actInsertBgImage;
//    QAction        *m_actProperty;
//    QAction        *m_actAbout;
private slots:
    void m_submit_clicked();
    void m_findshow();
    void m_logshow();
    void m_dismiss_clicked();
    void m_remove_clicked();
    //void m_add_clicked();
    void m_find_clicked();
    void m_change_clicked();
    void onUpdateContextMenu(QPoint);
    void adjustscene(int);
    void rulebaseload();
    void m_out_clicked();
    //void on_listWidget_pressed();
    void oncheck_clicked();
    void oncheckall_clicked();
    void addwindowshow();
    void m_addrule();
    void Returnroottable();
    void updateID();
    void changerule();
    void m_remove_checked();
    void setcomboxitem(int);
    void hideheadname();
    void open_close(int);
protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void mousePressEvent(QMouseEvent *e);
    // void mouseMoveEvent(QMouseEvent *e);

};

#endif // MAINWINDOW_H
