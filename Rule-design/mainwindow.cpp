#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "node.h"
#include"link.h"
#include<QTextEdit>
#include<QStack>
#include <QSqlError>
#include <QMessageBox>
#include<QFileDialog>
#include "addruledialog.h"
#include "datamanage.h"
#include<QtConcurrent>
#include<QGraphicsDropShadowEffect>
#include"titlebar.h"
#include <stack>
#include<QThread>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);
      //this->setAttribute(Qt::WA_DeleteOnClose);
      currentTablename="test1";
      //m_findwindow=new findDialog(this);
      m_logwindow=new logdialog(this);
      addwindow=new addruleDialog(this);
      changewindow=new changeDialog(this);
      add_table0=new addsqltable(this);
      m_chang_W=new Change_WDialog(this);
      cupos=120;
      setWindowFlags(Qt::FramelessWindowHint);
      setWindowFlags(Qt::FramelessWindowHint | windowFlags());
      //setAttribute(Qt::WA_TranslucentBackground);
      pTitleBar = new TitleBar(this);
      pTitleBar->setObjectName("m_Titlebar");
      installEventFilter(pTitleBar);
      QVBoxLayout *pLayout = new QVBoxLayout();
      pLayout->addWidget(pTitleBar);
      pLayout->addStretch();
      pLayout->setSpacing(0);
      pLayout->setContentsMargins(0, 0, 0, 0);
     //pLayout->addLayout(ui->verticalLayout_9,1);
     ui->verticalLayout_9->insertLayout(0,pLayout);
     ui->verticalLayout_9->setContentsMargins(0,0,0,0);
     //ui->verticalLayout_9->setMargin(0);
     ui->verticalLayout_9->setStretch(1,1);
     ui->verticalLayout_9->setSpacing(1);

    // pTitleBar->setStyleSheet("QWidget{border: 1px solid rgb(111, 156, 207);background-color:rgb(120, 170, 220);}");
      //pLayout->addWidget(ui->centralWidget);
      setWindowTitle(tr("规则设计与优化工具"));
//      QGraphicsDropShadowEffect *pEffect = new QGraphicsDropShadowEffect(this);
//      pEffect->setOffset(20, 20);
//      pEffect->setColor(QColor(QStringLiteral("black")));
//      pEffect->setBlurRadius(30);
//      this->setGraphicsEffect(pEffect);
      ui->groupBox_4->hide();
      ui->groupBox_land->hide();
      //menuflag=1;
      ui->m_slider->setMinimum(-20);  // 最小值
      ui->m_slider->setMaximum(20);  // 最大值
      ui->m_slider->setSingleStep(1); // 步长
      ui->m_slider->setValue(0); // 步长
      adjust_n=0;//节点图大小参数
      rootflag=0;
      dis_flag0=1;
      //ui->treeWidget->setStyle(QStyleFactory::create("windows"));
//     QPalette bgpal = palette();
//    bgpal.setColor (QPalette::Background, QColor (255, 255 , 255, 255));
//     //bgpal.setColor (QPalette::Background, Qt::transparent);
//    bgpal.setColor (QPalette::Foreground, QColor (255,255,255,255)); setPalette (bgpal);
      //ui->listView->(false);
      //ui->listWidget->setCo(QColor(32, 53, 74));
      //ui->listView->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
      //ui->listView->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));
     ui->stackedWidget->setCurrentIndex(0);
     ui->splitter->setStretchFactor(0,2);
     ui->splitter->setStretchFactor(1,1);
     ui->splitter_2->setStretchFactor(0,1);
     ui->splitter_2->setStretchFactor(1,3);
     QObject::connect(ui->addputton, SIGNAL(clicked()), this, SLOT(addwindowshow()));
     QObject::connect(ui->findputton, SIGNAL(clicked()), this, SLOT(m_findshow()));
     QObject::connect(ui->submitputton, SIGNAL(clicked()), this, SLOT(m_submit_clicked()));
     QObject::connect(ui->repputton, SIGNAL(clicked()), this, SLOT(m_dismiss_clicked()));
     QObject::connect(ui->returnputton, SIGNAL(clicked()), this, SLOT(m_change_clicked()));
     //QObject::connect(m_findwindow, SIGNAL(sendflag(bool)), this, SLOT(m_find_clicked()));
     QObject::connect(ui->find_s, SIGNAL(clicked()), this, SLOT(m_find_clicked()));
     QObject::connect(ui->m_slider, SIGNAL(valueChanged(int)), this, SLOT(adjustscene(int)));

     QObject::connect(ui->loadscape, SIGNAL(clicked()), this, SLOT(loadLandscape()));

     QObject::connect(m_logwindow, SIGNAL(sendflag(bool)), this, SLOT(rulebaseload()));
     QObject::connect(m_logwindow, SIGNAL(send_closeflag(bool)), this, SLOT(close()));

     QObject::connect(ui->outputfile, SIGNAL(clicked()), this, SLOT(m_out_clicked()));
     QObject::connect(ui->re_chose, SIGNAL(clicked()), this, SLOT(oncheck_clicked()));
     QObject::connect(ui->checkall, SIGNAL(stateChanged(int)), this, SLOT(oncheckall_clicked(int)));

     QObject::connect(ui->re_chose_W, SIGNAL(clicked()), this, SLOT(oncheck_clicked()));
     QObject::connect(ui->checkall_W, SIGNAL(stateChanged(int)), this, SLOT(oncheckall_clicked(int)));

     QObject::connect(ui->r_return, SIGNAL(clicked()), this, SLOT(Returnroottable()));
     QObject::connect(addwindow,SIGNAL(sendflag(bool)),this,SLOT(m_addrule()));
     QObject::connect(add_table0,SIGNAL(send_flag1(bool)),this,SLOT(updateID()));
     QObject::connect(changewindow,SIGNAL(send_chflag(bool)),this,SLOT(changerule()));
     QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(loadLandscape()));
     QObject::connect(m_chang_W, SIGNAL(send_chflag(int)), this, SLOT(change_W(int)));
     QObject::connect(ui->change_w,SIGNAL(clicked()),this,SLOT(change_Wclicked()));
    // QObject::connect(ui->load_rule,SIGNAL(clicked()),this,SLOT(findrulebase()));

     QObject::connect(ui->repputton_W, SIGNAL(clicked()), this, SLOT(m_dismiss_clicked()));
     QObject::connect(ui->submitputton_W, SIGNAL(clicked()), this, SLOT(m_submit_W()));

     connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->comboBox_4,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->comboBox_5,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(hideheadname()));
     connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(hideheadname()));

     connect(ui->Editmode,SIGNAL(stateChanged(int)),this,SLOT(open_close(int)));

     QObject::connect(ui->treeWidget->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));
     QObject::connect(ui->treeWidget_2->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));
     m_scene = new Scene(0,0,0,0,this);
     ui->graphicsView->setScene(m_scene);
     ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
     ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
     ui->tableView_2->setContextMenuPolicy(Qt::CustomContextMenu);
  //   connect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu(QPoint)));
     createActions();
     initViewActions();
     ui->scrollArea->setWidget(m_logwindow);
     ui->tableView_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 设置label的布局大小策略为扩展
     ui->tableView_2->verticalHeader()->setCascadingSectionResizes(true);
     ui->addputton->setDisabled(true);
     ui->findputton->setDisabled(true);
     ui->submitputton->setDisabled(true);
     ui->repputton->setDisabled(true);
     ui->returnputton->setDisabled(true);
     ui->r_return->setDisabled(true);
     //ui->checkall->setDisabled(true);
     //ui->re_chose->setDisabled(true);
     ui->outputfile->setEnabled(0);
     ui->groupBox->hide();
     ui->listWidget->setEnabled(0);

}
void MainWindow::open_close(int flag){
    if(flag==Qt::Checked){
        ui->groupBox->show();
        ui->checkall->show();
        ui->re_chose->show();
        ui->checkBox->show();
        //m_topMenu->show();
        m_topMenu->setEnabled(1);
        myviewmodel->open_close=1;

        connect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu(QPoint)));

        ui->checkBox->setCheckState(Qt::Unchecked);
        //m_topMenu->setEnabled(1);
    }
    else{
        ui->groupBox->hide();
        ui->checkall->hide();
        ui->re_chose->hide();
        ui->checkBox->hide();
        m_topMenu->setEnabled(0);
       // m_topMenu->hideTearOffMenu();
        myviewmodel->open_close=0;
        //ui->checkBox->setCheckState(Qt::Unchecked);
        ui->checkBox->setCheckState(Qt::Checked);
        disconnect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu(QPoint)));
        //ui->tableView_2->hideColumn(0);
        //ui->tableView_2->verticalHeader()->setVisible(1);
        //ui->tableView_2->verticalHeader()->show();
    }
}
void MainWindow::LoadClassifyFile(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("加载态势文件")," ", tr("XML files (*.xml);;ALL files (*.*)"));
    QList<QStandardItem*>aItemlist;
    QFile file(filePath); //相对路径、绝对路径、资源路径都行
    if(!file.open(QFile::ReadOnly))
        return;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    changewindow->doc=this->doc;
    addwindow->doc=this->doc;

    addwindow->LoadClassifyFile();

    file.close();
    QDomElement root=doc.documentElement(); //返回根节点
    QDomNode node=root.firstChild(); //获得第一个子节点
    addCHtoEN(node.toElement());
//    while(!node.isNull())  //如果节点不空
//    {
//        if(node.isElement()) //如果节点是元素
//        {
//            QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
//            if(!e.attribute("中文名称").isEmpty()){
//               // QSqlRecord record;
//               for(int i=0;i<myviewmodel->EntoCh->rowCount();i++){
//                   //myviewmodel->EntoCh->
//                   myviewmodel->EntoCh->setFilter(QString("chname=%1").arg(e.attribute("中文名称")));
//                   if(!myviewmodel->EntoCh->select()){
//                      int rowNum = myviewmodel->EntoCh->rowCount(); //获得表的行数
//                      int id = rowNum;
//                      myviewmodel->EntoCh->insertRow(rowNum); //添加一行
//                      myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,0),id);
//                      myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,1),e.attribute("映射名称"));
//                      myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,2),e.attribute("中文名称"));
//                   }
//                   //myviewmodel->EntoCh->record(i).value(1).toString();
//            }
//            }
//        }
//        node=node.nextSibling();
//    }
}
void MainWindow::addCHtoEN(QDomElement root)
{
   QDomNode node = root.firstChild();
    while (!node.isNull())
    {
        QDomElement e = node.toElement();
        if(node.isElement()){
            if(!e.attribute("中文名称").isEmpty()){
                bool flag0=0;
                int  i=0;
                while(!flag0&&(i<myviewmodel->EntoCh->rowCount())){
                    if(myviewmodel->EntoCh->data(myviewmodel->EntoCh->index(i,2)).toString()==e.attribute("中文名称")){
                        flag0=1;break;
                    }
                    i++;
                }
                if(!flag0){
                    int rowNum = myviewmodel->EntoCh->rowCount(); //获得表的行数
                    int id = rowNum;
                    myviewmodel->EntoCh->insertRow(rowNum); //添加一行
                    myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,0),id);
                    if(!e.attribute("映射名称").isNull()){
                        myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,1),e.attribute("映射名称"));
                    }
                    else if(!e.attribute("名称").isNull()){
                        myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,1),e.attribute("名称"));
                    }
                    else{
                        myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,1),e.attribute("枚举名"));
                    }

                    myviewmodel->EntoCh->setData(myviewmodel->EntoCh->index(rowNum,2),e.attribute("中文名称"));
                    myviewmodel->EntoCh->submitAll();
                }
            }
            addCHtoEN(e);
        }
        node = node.nextSibling();
   }
}
void MainWindow::Pushbuttonable(bool flag){
//    if(flag){
//        ui->groupBox->show();
//    }
//    else{
//        ui->groupBox->hide();
//    }
    ui->addputton->setEnabled(flag);
    ui->findputton->setEnabled(flag);
    ui->submitputton->setEnabled(flag);
    ui->repputton->setEnabled(flag);
    ui->returnputton->setEnabled(flag);
    ui->checkall->setEnabled(flag);
    ui->re_chose->setEnabled(flag);
    ui->outputfile->setEnabled(flag);
}
void MainWindow::Returnroottable(){
//    model_display.clear();
//    //modelroot->setTable("test1");
//    //modelroot->select();
//    myviewmodel->Tablehead.clear();
//    //model_display.append(modelroot);
//    myviewmodel->setview(model_display);
//    this->Pushbuttonable(0);
//    //ui->tableView_2->setColumnWidth(0, 100);
//    ui->tableView_2->setColumnWidth(1, ui->tableView_2->columnWidth(0));//设置固定宽度
//    ui->tableView_2->setColumnWidth(2, ui->tableView_2->columnWidth(0));
//    rootflag=1;
    if(dis_flag0){
        ui->groupBox_land->show();
        ui->graphicsView->hide();
        ui->m_slider->hide();
        QList<int>listsize;
        listsize<<200<<500;
        ui->splitter->setSizes(listsize);
    }
    else{
        ui->groupBox_land->hide();
        ui->graphicsView->show();
        ui->m_slider->show();
        QList<int>listsize;
        listsize<<400<<400;
        ui->splitter->setSizes(listsize);
    }
    dis_flag0=!dis_flag0;

}
void MainWindow::rulebaseload(){
    //m_scene->clear();
    m_node_red.clear();
    m_link.clear();
    T_item.clear();
    m_scene->clear();
    //m_logwindow->close();
    //ui->tableView_2->clearSpans();
    //ui->tableView_2->clearSpans();
    //modelin.clear();
    //modelroot->clear();
   // QString name=this->m_logwindow->getnametext();
    QString pssw=this->m_logwindow->getpassword();
    QString username=this->m_logwindow->getusername();

    //db=ConnectionPool::openConnection(username, pssw,name);
    //QString filePath = QFileDialog::getOpenFileName(this,tr("open file"),"/home", tr("INI files (*.ini);;ALL files (*.*)"));

    QString filePath2=":/1.ini";
   // qDebug()<<qApp->applicationDirPath()<<"a";
    //"D:/mywork/QTworkspace/Rule-design/1.ini";
    //ConnectionPool::closeConnection(db);
    db=ConnectionPool::openConnection_2(filePath2,username,pssw);
    //qDebug()<<db.open();
    if(!db.open()){
        QMessageBox::warning(this,QString("提示!"),QString("连接数据库错误"));
    }
    else{
        ui->listWidget->setEnabled(1);
        this->ui->stackedWidget->setCurrentIndex(1);
        //ui->checkall->setEnabled(true);
        //ui->re_chose->setEnabled(true);
        modelroot=new QSqlTableModel(this,db);
        myviewmodel=new viewmodel(this);
        connect(myviewmodel,SIGNAL(sendRowchanged(bool)),this,SLOT(hideheadname()));
        myviewmodel->EntoCh=new QSqlTableModel(this,db);
        myviewmodel->EntoCh->setTable("en_ch");
        myviewmodel->EntoCh->select();


        //modellandscape=new QSqlTableModel();
        myviewmodel->rulefact->model_fact=new QSqlTableModel(this,db);
        myviewmodel->rulefact->model_fact->setTable("rule_fact");
        myviewmodel->rulefact->model_fact->select();
        myviewmodel->rulefact->model_fact->setEditStrategy(QSqlTableModel::OnManualSubmit);
        //model.append(new mytablemodel(this,db));
        //modelin.append(new QSqlTableModel(this,db));
        //modelin.append(new QSqlTableModel(this,db));
        if(modelroot){
            modelin.clear();
            model_display.clear();
            modelroot->setTable("test1");
            modelroot->setEditStrategy(QSqlTableModel::OnManualSubmit);
            //modelin.at(0)->setEditStrategy(QSqlTableModel::OnManualSubmit);
            modelroot->select();
            //modelin.at(0)->select();
            //modelin.at(1)->setTable("A9");
            //modelin.at(1)->select();
            //modelin.append(modelroot);
           //model_display.append(modelroot);
           // QtConcurrent::run(myviewmodel,&viewmodel::setview,modelin);
            myviewmodel->setview(model_display);
            //this->hideheadname(ui->checkBox->checkState());
           // ui->tableView_2->reset();
           //ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//所有列都扩展自适应宽度，填充充满整个屏幕宽度
           //horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents );//根据列内容来定列宽
           //ui->tableView_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);//对第0列单独设置固定宽度
            ui->tableView_2->setMinimumWidth(100);
            ui->tableView_2->setModel(myviewmodel);
            //myviewmodel->rulefact->model_fact->setTable("rule_fact_1");
            myviewmodel->rulefact->model_fact->select();

            LoadClassifyFile();
            open_close(ui->Editmode->checkState());
        }
    }
}
void MainWindow::oncheck_clicked(){
    for(int i=0;i<=myviewmodel->listnum.back();i++){
        myviewmodel->setData(myviewmodel->index(i,0),myviewmodel->data(myviewmodel->index(i,0),Qt::CheckStateRole)== Qt::Checked ? Qt::Unchecked : Qt::Checked,Qt::CheckStateRole);
        }
    myviewmodel->updata();
}
void MainWindow::oncheckall_clicked(int flag){
    //int flag=sender()
    if(flag==Qt::Checked){
        for(int i=0;i<=myviewmodel->listnum.back();i++){
            myviewmodel->setData(myviewmodel->index(i,0),Qt::Checked,Qt::CheckStateRole);
            }
    }
    else{
        for(int i=0;i<=myviewmodel->listnum.back();i++){
           myviewmodel->setData(myviewmodel->index(i,0),Qt::Unchecked,Qt::CheckStateRole);
         }
    }
    myviewmodel->updata();
}
void MainWindow::m_out_clicked(){
    QString dirPath;//创建文件夹路径
     QString filePath;//存储保存路径
     //QString saveName="mydb.sql";//保存图片名字
     QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
     QString str = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
    //filePath = QFileDialog::getExistingDirectory(this,"");//获取文件夹路径
    dirPath=QFileDialog::getSaveFileName(this,"导出规则文件","/a.xml","XMl(.xml)");
    QString XmlFilename=  "test.xml";
    myviewmodel->WriteXml(dirPath);
}
void MainWindow::ruledsp(bool brflag){
    //T_item->clearFocus();
    if(brflag){
        Node *node1 = new Node(this);
        node1->setText(QString("红方"));
        int colNum = modelroot->columnCount();
        m_scene->addItem(node1);
        m_node_red.append(node1);
        node1->setPos(100, m_scene->height() /4+100);
        node1->setBasePoint(node1->pos());
        node1->setcolornum(0);
        int rowNum = modelroot->rowCount();
        for(int i=0;i<rowNum;i++){
            Node*currentnode=node1;
            QList<Link *> linksTo = node1->getLinksTo();
            if (linksTo.isEmpty()){
                onAdd(node1,modelroot->index(i,1).data().toString(),1);
                onAdd(m_node_red.back(),modelroot->index(i,2).data().toString(),1);
                onAdd(m_node_red.back(),modelroot->index(i,3).data().toString(),1);
                onAdd(m_node_red.back(),modelroot->index(i,4).data().toString(),1);
                onAdd(m_node_red.back(),modelroot->index(i,5).data().toString(),1);;
            }
            else{
                for(int j=1;j<colNum;j++){
                currentnode=findnextnode(currentnode,modelroot->index(i,j).data().toString(),1);
                }
            }
        }
         adjustnode(1);
         if(T_item.isEmpty()){
             tiltleItem *item1=new tiltleItem(m_node_red.first(),cupos);
             T_item.append(item1);
             m_scene->addItem(item1);
         }
    }
    else{
        Node *node1 = new Node(this);
        node1->setText(QString("蓝方"));
        int colNum = modelroot->columnCount();
        m_scene->addItem(node1);
        m_node_blue.append(node1);
        node1->setPos(100, m_scene->height() /4+100);
        node1->setBasePoint(node1->pos());
        node1->setcolornum(0);
        int rowNum = modelroot->rowCount();
        for(int i=0;i<rowNum;i++){
            Node*currentnode=node1;
            QList<Link *> linksTo = node1->getLinksTo();
            if (linksTo.isEmpty()){
                onAdd(node1,modelroot->index(i,1).data().toString(),0);
                onAdd(m_node_blue.back(),modelroot->index(i,2).data().toString(),0);
                onAdd(m_node_blue.back(),modelroot->index(i,3).data().toString(),0);
                onAdd(m_node_blue.back(),modelroot->index(i,4).data().toString(),0);
                onAdd(m_node_blue.back(),modelroot->index(i,5).data().toString(),0);;
            }
            else{
                for(int j=1;j<colNum;j++){
                currentnode=findnextnode(currentnode,modelroot->index(i,j).data().toString(),0);
                }
            }
        }
        adjustnode(0);

        if(!T_item.isEmpty()){
            m_scene->removeItem(T_item.first());
            T_item.clear();
        }
        tiltleItem *item1=new tiltleItem(m_node_blue.first(),cupos);
        T_item.append(item1);
        m_scene->addItem(item1);
    }
}
Node*MainWindow::findnextnode(Node*node,QString data0,bool rb){
    QList<Link *> linksTo = node->getLinksTo();
    for(int i=0;i<linksTo.count();i++){
        if(data0==linksTo.at(i)->getToNode()->getText()){
            return linksTo.at(i)->getToNode();
        }
    }
    return onAdd(node,data0,rb);
}
Scene *MainWindow::getruleScene()
{
    return m_scene;
}
MainWindow::~MainWindow()
{
    delete ui;
}

Node *MainWindow::getSelectedNode()
{
    QList<QGraphicsItem *> items = m_scene->selectedItems();
    if (items.count() == 1) {
        return dynamic_cast<Node *>(items.first());
    }
    else {
        return 0;
    }
}
void MainWindow::itemsMove(Node*node)
{
    Node *selectedNode = getSelectedNode();
    if (selectedNode&&selectedNode==node) {
            double moveX = selectedNode->x() - selectedNode->getBasePoint().x();
            double moveY = selectedNode->y() - selectedNode->getBasePoint().y();
            if(!T_item.isEmpty()){
                T_item.first()->moveBy(moveX,moveY);
            }
            for(int i=0;i<m_node_red.count();i++){
                if( m_node_red.at(i)!=selectedNode){
                m_node_red.at(i)->setBasePoint(QPointF(m_node_red.at(i)->x() + moveX, m_node_red.at(i)->y() + moveY));
                m_node_red.at(i)->setPos(m_node_red.at(i)->getBasePoint().x() , m_node_red.at(i)->getBasePoint().y());
                }
            }
            for(int i=0;i<m_node_blue.count();i++){
                if( m_node_blue.at(i)!=selectedNode){
                m_node_blue.at(i)->setBasePoint(QPointF(m_node_blue.at(i)->x() + moveX, m_node_blue.at(i)->y() + moveY));
                m_node_blue.at(i)->setPos(m_node_blue.at(i)->getBasePoint().x() , m_node_blue.at(i)->getBasePoint().y());
                }
            }
             for(int j=0;j<m_link.count();j++){
             m_link.at(j)->adjust();
             }
            }
}

Node* MainWindow::onAdd(Node*fromNode,QString name,bool rb)
{
    Node *node = new Node(this);
    node->setText(name);
    if(rb){
        m_node_red.append(node);
    }
    else{
        m_node_blue.append(node);
    }

    QList<QGraphicsItem *> items = m_scene->items();
    m_scene->addItem(node);
    node->setPos(100,100);
    node->setcolornum(fromNode->nodecolor+1);
    Link *newLink = new Link(fromNode, node);
    m_link.append(newLink);
    m_scene->addItem(newLink);
    return node;
}
QList<Node*> MainWindow::findlastnode(Node*node,QList<Node*>nodelist){
    QList<Node*>nodelist0=nodelist;
    if(node->getLinksTo().isEmpty()){
        nodelist0.append(node);
    }
    else{
        for(int i =0;i<node->getLinksTo().count();i++){
            nodelist0=findlastnode(node->getLinksTo().at(i)->getToNode(),nodelist0);
        }
    }
    return nodelist0;
}
void MainWindow::adjustnode(bool br){
    QList<Node*>nodelist;
    QList<Node*>nodelist2;
    Node*currentnode;
    int pos=cupos;
    if(br){
        currentnode=m_node_red.first();
        //pos=120;
   }
    else{
        currentnode=m_node_blue.first();
        //pos=520;
    }
    nodelist=findlastnode(currentnode,nodelist);

    while(!nodelist.isEmpty()){
         Node*cnode=nodelist.first()->getLinkFrom()->getFromNode();
         QList<Link*>link_list1=cnode->getLinksTo();
         for(int j=0;j<link_list1.count();j++){
              pos=pos+40;
              nodelist.removeOne(link_list1.at(j)->getToNode());
              link_list1.at(j)->getToNode()->setPos(500,pos);
              link_list1.at(j)->getToNode()->setBasePoint(link_list1.at(j)->getToNode()->pos());
          }
          nodelist2.append(cnode);
          cnode->setPos(400,(cnode->getLinksTo().first()->getToNode()->y()+cnode->getLinksTo().last()->getToNode()->y())/2);
    }
    while(!nodelist2.isEmpty()){
        if(nodelist2.first()->getLinkFrom()){
        Node*cnode2=nodelist2.first()->getLinkFrom()->getFromNode();
        if(cnode2){
            cnode2->setPos(cnode2->getLinksTo().first()->getToNode()->x()-100,(cnode2->getLinksTo().first()->getToNode()->y()+cnode2->getLinksTo().last()->getToNode()->y())/2);
            //cnode2->setcolor(QColor(200,250,2));
            for(int j=0;j<cnode2->getLinksTo().count();j++){
                nodelist2.removeOne(cnode2->getLinksTo().at(j)->getToNode());
            }
            if(cnode2->getLinkFrom()){ nodelist2.append(cnode2);}
        }
        }
    }
    for(int k=0;k<m_link.count();k++){
        m_link.at(k)->adjust();
    }
    cupos=pos+50;
}
void MainWindow::m_submit_clicked()//提交
{
    if(rootflag==1){
        modelroot->database().transaction(); //
        if (modelroot->submitAll()) {
            modelroot->database().commit(); //
                m_scene->clear();
            //qDeleteAll(m_node_red);//.........................
                m_node_red.clear();
                m_link.clear();
               // this->ruledsp(1);



        } else {
            modelroot->database().rollback(); //
            QMessageBox::warning(this, tr("tableModel"),
                                 tr("database error: %1").arg(modelroot->lastError().text()));
        }
    }
    else{
        //myviewmodel->rulefact->submit();
        myviewmodel->submit_checked();
//        for(int i=0;i<modelin.count();i++){
//            modelin.at(i)->database().transaction();
//            bool flag=modelin.at(i)->submitAll();
//            if (flag) {
//                modelin.at(i)->database().commit(); //

//            } else {
//                modelin.at(i)->database().rollback(); //
//                QMessageBox::warning(this, tr("tableModel"),
//                                     tr("database error: %1").arg(modelin.at(i)->lastError().text()));
//            }
//        }
    }
}
void MainWindow::m_submit_W()//提交
{
    myviewmodel->submit_W();
}
void MainWindow::m_dismiss_clicked() //撤销
{
    for(int i=0;i<modelin.count();i++){
     modelin.at(i)->setTable(modelin.at(i)->tableName());
     modelin.at(i)->select();
    }
    myviewmodel->rulefact->model_fact->setTable("rule_fact_1");
    myviewmodel->rulefact->model_fact->select();
    myviewmodel->setview(model_display);
   // this->hideheadname(ui->checkBox->checkState());
}
void MainWindow::m_find_clicked() //查询
{
    if(findnode5){
        //findnode5->setSelected(1);
        this->changeTable(findnode5);
    }
    //int curRow = ui->tableView_2->currentIndex().row();
    //myviewmodel->getrecord(curRow);
    //menuflag=0;
    //QList<QString> name = m_findwindow->getfindtext();
   // m_findwindow->close();
    //bool fa=myviewmodel->findrecord(name);
//    if(fa==0){
//        QMessageBox::warning(this, tr("result"),
//                             tr("can't find rule!"));
//    }
}
void MainWindow::m_change_clicked() //修改
{
    int row=ui->tableView_2->currentIndex().row();
    QSqlRecord record0=myviewmodel->getrecord(row);

    if(!record0.isEmpty()){
        changewindow->show();
        changewindow->setRuleData(&record0);
        changewindow->combox_rn();
    }
   //changewindow->show();
    //changewindow->setRuleData(&record0);
}
void MainWindow::changerule(){
    int row=ui->tableView_2->currentIndex().row();
    QSqlRecord record0=myviewmodel->getrecord(row);
    QString iftext=record0.value(1).toString();
    QString thentext=record0.value(2).toString();
    bool flg=changewindow->getRuleData(&record0);
    if(flg==1){
        bool flag_2=myviewmodel->setrecord(record0,row);
        if(flag_2){
            changewindow->close();
            myviewmodel->transRule(iftext,3);
            myviewmodel->transRule(thentext,3);
            //myviewmodel->rulefact->submit();
            QMessageBox::information(this,QString("成功!"),QString("修改成功！"));
        }
        else{
            QMessageBox::warning(this,QString("提示!"),QString("修改失败，规则重复或规则无改动"));
        }

    }
}
void MainWindow::addwindowshow(){
   // if(rootflag==0){
        addwindow->show();
        addwindow->cleartext();

  //  }
//    else{
//        int row=ui->tableView_2->currentIndex().row();
//        QList<QString>list_0;
//        for(int i=0;i<modelroot->record(row).count();i++){
//            list_0.append(modelroot->record(row).value(i).toString());
//        }
//        add_table0->datain(list_0);
//        add_table0->show();
//    }
}
//void MainWindow::addwindowshow_node(QStringList list_0){
//        add_table0->datain(list_0);
//        add_table0->show();
//}
void MainWindow::m_addrule(){
    QList<QString>addrule;
    int curRow = ui->tableView_2->currentIndex().row();

    if(curRow<0) curRow=0;
    addrule.append(addwindow->getIf());
    addrule.append(addwindow->getThen());
    addrule.append(addwindow->getWeight());
    bool flag=myviewmodel->addrecord(addrule,curRow);
    if(flag){
        QMessageBox::information(this,QString("成功"),QString("添加成功"));
       // qDebug()<<myviewmodel->listnum;
    }
    else{
        QMessageBox::critical(this,QString("提示!"),QString("规则重复，添加失败"));
    }
   //myviewmodel->addrule();
}
void MainWindow::createActions()
{
    m_topMenu = new QMenu(this);
    m_actAdd = new QAction("添加(Ctrl+N)", this);
    m_actAdd->setShortcut(tr("Ctrl+N"));
    connect(m_actAdd, SIGNAL(triggered(bool)), this, SLOT(addwindowshow()));
    m_topMenu->addAction(m_actAdd);
    //m_topMenu->addSeparator();
    m_actDis= new QAction("回退(Ctrl+X)", this);
    m_actDis->setShortcut(tr("Ctrl+X"));
    connect(m_actDis, SIGNAL(triggered(bool)), this, SLOT(m_dismiss_clicked()));
    m_topMenu->addAction(m_actDis);
    m_actSubmit= new QAction("提交修改(Ctrl+S)", this);
    m_actSubmit->setShortcut(tr("Ctrl+S"));
    connect(m_actSubmit, SIGNAL(triggered(bool)), this, SLOT(m_submit_clicked()));
    m_topMenu->addAction(m_actSubmit);
//    m_actFind = new QAction("查询", this);
//    m_actFind->setShortcut(tr("Ctrl+F"));
//    connect(m_actFind, SIGNAL(triggered(bool)), this, SLOT(m_findshow()));
//    m_topMenu->addAction(m_actFind);
    m_actBack = new QAction("修改", this);
    m_actBack->setShortcut(tr("Ctrl+R"));
    connect(m_actBack, SIGNAL(triggered(bool)), this, SLOT(m_change_clicked()));
    m_topMenu->addAction(m_actBack);
}
void MainWindow::initViewActions()
{
    QList<QAction *> acts = m_topMenu->actions();
    for (int i = 0; i < acts.count(); i++) {
        QAction *act = acts.at(i);
        if (act) {
            ui->tableView_2->addAction(act);
        }
    }
}
void MainWindow::hideheadname(){
    if(ui->stackedWidget->currentIndex()==1){
        int flag=ui->checkBox->checkState();
        if(flag==Qt::Checked){
            ui->tableView_2->hideRow(0);
            for(int i=1;i<myviewmodel->listnum.back();i++){
                if(myviewmodel->listnum.contains(i)){
                    if(!ui->tableView_2->isRowHidden(i))
                            ui->tableView_2->hideRow(i);
                }
                else{
                    //qDebug()<<"要显示的行："<<i;
                    if(ui->tableView_2->isRowHidden(i))
                       //  qDebug()<<i;
                         ui->tableView_2->showRow(i);
                }
            }
        }
        else if(flag==Qt::Unchecked){
            for(int i=0;i<myviewmodel->listnum.back();i++){
                if(ui->tableView_2->isRowHidden(i))
                   // qDebug()<<"显示"<<i;
                     ui->tableView_2->showRow(i);
            }
        }
    }
    else if(ui->stackedWidget->currentIndex()==2){
        int flag=ui->checkBox_2->checkState();
        if(flag==Qt::Checked){
            ui->rule_table->hideRow(0);
            for(int i=1;i<myviewmodel->listnum.back();i++){
                if(myviewmodel->listnum.contains(i)){
                    if(!ui->rule_table->isRowHidden(i))
                            ui->rule_table->hideRow(i);
                }
                else{
                    if(ui->rule_table->isRowHidden(i))
                         ui->rule_table->showRow(i);
                }
            }
        }
        else if(flag==Qt::Unchecked){
            for(int i=0;i<myviewmodel->listnum.back();i++){
             //   if(ui->rule_table->isRowHidden(i))
                     ui->rule_table->showRow(i);
            }
        }
    }
}
//void MainWindow::hideheadname_2(){
//    int flag=ui->checkBox->checkState();
//    if(flag==Qt::Checked){
//        ui->tableView_2->hideRow(0);
//        for(int i=1;i<myviewmodel->rowcount;i++){
//            if(myviewmodel->listnum.contains(i)){
//                if(!ui->tableView_2->isRowHidden(i))
//                        ui->tableView_2->hideRow(i);
//            }
//            else{
//                if(ui->tableView_2->isRowHidden(i))
//                        ui->tableView_2->showRow(i);
//            }
//        }
//    }
//    else if(flag==Qt::Unchecked){
//        for(int i=0;i<myviewmodel->rowcount;i++){
//            if(ui->tableView_2->isRowHidden(i))
//                 ui->tableView_2->showRow(i);
//        }
//    }
//}
void MainWindow::onUpdateContextMenu(QPoint pos)
{
    m_actAdd->setEnabled(1);
    m_actDis->setEnabled(!rootflag);
    m_actSubmit->setEnabled(1);
    //m_actFind->setEnabled(!rootflag);
    m_actBack->setEnabled(!rootflag);
    QModelIndex index = ui->tableView_2->indexAt(pos);
    if (index.isValid())
    {
    m_topMenu->exec(QCursor::pos()); //
    }
}
void MainWindow::m_findshow(){
    ui->comboBox_5->clear();
    ui->comboBox_5->addItem("红方");
    ui->comboBox_5->addItem("蓝方");

    //findnode1=m_node_red.first();

}
void MainWindow::setcomboxitem(int index){
       if(sender() == ui->comboBox_5&&index!=-1){
           if(index==0){
               findnode1=m_node_red.first();
           }
           else{
               findnode1=m_node_blue.first();
           }
           ui->comboBox->clear();
           for(int i=0;i<findnode1->getLinksTo().count();i++){

               ui->comboBox->addItem(findnode1->getLinksTo().at(i)->getToNode()->getText());
           }
        }
       else if (sender() == ui->comboBox&&index!=-1)
        {
        findnode2=findnode1->getLinksTo().at(index)->getToNode();
        ui->comboBox_2->clear();
        for(int i=0;i<findnode2->getLinksTo().count();i++){
            ui->comboBox_2->addItem(findnode2->getLinksTo().at(i)->getToNode()->getText());
        }
        }
        else if (sender() == ui->comboBox_2&&index!=-1)
        {
        findnode3=findnode2->getLinksTo().at(index)->getToNode();
        ui->comboBox_3->clear();
        for(int i=0;i<findnode3->getLinksTo().count();i++){
            ui->comboBox_3->addItem(findnode3->getLinksTo().at(i)->getToNode()->getText());
        }
        }
        else if (sender() == ui->comboBox_3&&index!=-1)
       {
        ui->comboBox_4->clear();
        findnode4=findnode3->getLinksTo().at(index)->getToNode();
        for(int i=0;i<findnode4->getLinksTo().count();i++){
            ui->comboBox_4->addItem(findnode4->getLinksTo().at(i)->getToNode()->getText());
        }
        }
        else if (sender() == ui->comboBox_4&&index!=-1){
            findnode5=findnode4->getLinksTo().at(index)->getToNode();
        }
}
void MainWindow::m_logshow(){
    this->m_logwindow->show();
}
void MainWindow::adjustscene(int adjust_m)
{
    double m_scale=1;
    if(adjust_m>adjust_n){
       m_scale=1+(adjust_m-adjust_n)*0.1;
    }
    else{
       m_scale=1/(1+(adjust_n-adjust_m)*0.1);
    }
    this->ui->graphicsView->scale(m_scale, m_scale);
    adjust_n=adjust_m;
}
void MainWindow::addtable(Node*node,bool flag){
    if(flag){
        if(node->getLinksTo().isEmpty()){
            bool fl=1;
            for(int i=0;i<modelin.count();i++){
                if(node->getText()==modelin.at(i)->tableName()){
                    fl=0;
                    break;
                }
            }
            if(fl){
                modelin.append(new QSqlTableModel(this,db));
                modelin.back()->setEditStrategy(QSqlTableModel::OnManualSubmit);
                modelin.back()->setTable(node->getText());
                modelin.back()->select();
            }
        }
        else{
            for(int i=0;i<node->getLinksTo().count();i++){
                addtable(node->getLinksTo().at(i)->getToNode(),1);
            }
        }
    }
    else{
        if(node->getLinksTo().isEmpty()){
            for(int i=0;i<modelin.count();i++){
                if(modelin.at(i)->tableName()==node->getText()){
                    if(!model_display.contains(modelin.at(i))){
                        model_display.append(modelin.at(i));
                        myviewmodel->Tablehead.append(node->getheadname());
                    }
                }
            }
//            model_display.append(new QSqlTableModel(this,db));
//            modelin.back()->setEditStrategy(QSqlTableModel::OnManualSubmit);
//            modelin.back()->setTable(node->getText());
//            modelin.back()->select();
        }
        else{
            for(int i=0;i<node->getLinksTo().count();i++){
                addtable(node->getLinksTo().at(i)->getToNode(),0);
            }
        }
    }
}
void MainWindow::changeTable(Node*node){
    model_display.clear();
    myviewmodel->Tablehead.clear();
    addtable(node,0);
    myviewmodel->setview(model_display);
    this->Pushbuttonable(1);
    ui->tableView_2->setColumnWidth(1, 200);//设置固定宽度
    ui->tableView_2->setColumnWidth(2, 200);
    myviewmodel->disflag=1;
}
void MainWindow::chatables(){
    model_display.clear();
    myviewmodel->Tablehead.clear();
    QList<Node*>selectlist;
    for(int i=0;i<m_node_red.count();i++){
        if(m_node_red.at(i)->getLinksTo().isEmpty()&&m_node_red.at(i)->isselect==1){
            for(int j=0;j<modelin.count();j++){
                if(modelin.at(j)->tableName()==m_node_red.at(i)->getText()){
                    if(!model_display.contains(modelin.at(j))){
                        model_display.append(modelin.at(j));
                        myviewmodel->Tablehead.append(m_node_red.at(i)->getheadname());
                    }
                    break;
                }
            }

        }
    }
    for(int i=0;i<m_node_blue.count();i++){
        if(m_node_blue.at(i)->getLinksTo().isEmpty()&&m_node_blue.at(i)->isselect==1){
            for(int j=0;j<modelin.count();j++){
                if(modelin.at(j)->tableName()==m_node_blue.at(i)->getText()){
                    if(!model_display.contains(modelin.at(j))){
                        model_display.append(modelin.at(j));
                        myviewmodel->Tablehead.append(m_node_blue.at(i)->getheadname());
                    }
                    break;
                }
            }

        }
    }
   // myviewmodel->rulefact->model_fact->setTable("rule_fact");
   // myviewmodel->rulefact->model_fact->select();
    myviewmodel->setview(model_display);

    this->Pushbuttonable(1);
    ui->tableView_2->setColumnWidth(1, 200);//设置固定宽度
    ui->tableView_2->setColumnWidth(2, 200);
    myviewmodel->disflag=1;

}
void MainWindow::on_listWidget_pressed()
{
    QModelIndex index = ui->listWidget->currentIndex();
    QString text = index.data().toString();
    if (text == "-首页") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (text == "规则设计") {
        ui->stackedWidget->setCurrentIndex(1);
    } /*else if (text == "场景导入") {
        ui->stackedWidget->setCurrentIndex(2);
    }*/
    else if (text == "规则优化") {
        ui->Editmode->setChecked(Qt::Checked);
        ui->stackedWidget->setCurrentIndex(2);
    }
}
bool MainWindow::add_sqltable(QString name){
    bool flag=datamanage::addtable(db,name);
    if(flag){
            QMessageBox::about(this, "创建", "create new table success");
                  }
             else{
             QMessageBox::about(this, "创建", "error create new database");
    }
    return flag;
}
void MainWindow::updateID(){
    int row=modelroot->rowCount()-1;
    QList<QString>list_out=add_table0->dataout();
    add_table0->close();
    int id=modelroot->rowCount();
    modelroot->insertRow(row);
    modelroot->setData(modelroot->index(row,0),id+1);
    for(int i=1;i<list_out.count();i++){
        modelroot->setData(modelroot->index(row,i),list_out.at(i));
    }
    bool flag=add_sqltable(list_out.back());
    if(flag){
        this->m_submit_clicked();
    }
    else{
        modelroot->revertAll();
    }
    myviewmodel->setview(myviewmodel->modellist0);
  //  this->hideheadname(ui->checkBox->checkState());
}
void MainWindow::loadLandscape(){
    ui->treeWidget->clear();
    ui->treeWidget_2->clear();
    ui->treeWidget->setHeaderLabel(tr("场景信息"));    //设置标题
    ui->treeWidget_2->setHeaderLabel(tr("场景信息"));
    /*** 加载场景文件****/
//    QString filePath = QFileDialog::getOpenFileName(this,tr("加载场景文件")," ", tr("XML files (*.xml);;ALL files (*.*)"));
//    QDomDocument doc0;
//    QFile file(filePath); //相对路径、绝对路径、资源路径都行
//    if(!file.open(QFile::ReadOnly))
//        return;
//    if(!doc0.setContent(&file))
//    {
//        file.close();
//        return;
//    }

//    file.close();
//    QDomElement root=doc.documentElement(); //返回根节点
//    QDomNode node=root.firstChild();
//    while(!node.isNull())  //如果节点不空
//    {
//       if(node.isElement()) //如果节点是元素
//        {
//          QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
//            if(!e.attribute("中文名称").isEmpty()){
//                   // QSqlRecord record;
//                }
//            }
//         node=node.nextSibling();
//     }

    if(modelroot){
        modelroot->setTable(modelroot->tableName());
        modelroot->select();
        idlist_r.clear();
        idlist_b.clear();
        QList<QTreeWidgetItem *> items;
        int a=qrand()%10;
        while(a){
            int b=qrand()%modelroot->rowCount();
            QSqlRecord record0=modelroot->record(b);
            idlist_r.append(record0.value(0).toInt());
            int c=qrand()%4;
            bool findflag=0;
            QTreeWidgetItem *item0=new QTreeWidgetItem;
            for(int i=0;i<ui->treeWidget->topLevelItemCount();i++){
                if(ui->treeWidget->topLevelItem(i)->text(0)==record0.value(1).toString()){
                     item0=ui->treeWidget->topLevelItem(i);
                     findflag=1;
                }
            }
            if(findflag==0){
                item0 = new QTreeWidgetItem(ui->treeWidget,QStringList(QString(record0.value(1).toString())));
                items.append(item0);
            }
                switch(c){
                case 1:{
                    this->findchilditem(item0,record0.value(2).toString());
                }
                case 2:{
                    this->findchilditem(this->findchilditem(item0,record0.value(2).toString()),record0.value(3).toString());
                }
                case 3:{
                    this->findchilditem(this->findchilditem(this->findchilditem(item0,record0.value(2).toString()),record0.value(3).toString()),record0.value(4).toString());
                }
                }
            a--;
        }
        ui->treeWidget->insertTopLevelItems(0,items);
        ui->treeWidget->expandAll();
        int aa=qrand()%10;
        QList<QTreeWidgetItem *> items_2;
        while(aa){
            int b=qrand()%modelroot->rowCount();
            QSqlRecord record0=modelroot->record(b);
            idlist_b.append(record0.value(0).toInt());
            int c=qrand()%4;
            bool findflag=0;
            QTreeWidgetItem *item0=new QTreeWidgetItem;
            for(int i=0;i<ui->treeWidget_2->topLevelItemCount();i++){
                if(ui->treeWidget_2->topLevelItem(i)->text(0)==record0.value(1).toString()){
                     item0=ui->treeWidget_2->topLevelItem(i);
                     findflag=1;
                }
            }
            if(findflag==0){
                item0 = new QTreeWidgetItem(ui->treeWidget_2,QStringList(QString(record0.value(1).toString())));
            }
            items_2.append(item0);
                switch(c){
                case 1:{
                    this->findchilditem(item0,record0.value(2).toString());
                }
                case 2:{

                    this->findchilditem(this->findchilditem(item0,record0.value(2).toString()),record0.value(3).toString());
                }
                case 3:{
                    this->findchilditem(this->findchilditem(this->findchilditem(item0,record0.value(2).toString()),record0.value(3).toString()),record0.value(4).toString());
                }
                }
            aa--;
        }
        ui->treeWidget_2->insertTopLevelItems(0,items_2);
        ui->treeWidget_2->expandAll();
        ui->treeView->setModel(ui->treeWidget->model());
        ui->treeView->expandAll();
        ui->treeView_2->setModel(ui->treeWidget_2->model());
        ui->treeView_2->expandAll();
        findrulebase();
        Pushbuttonable(1);
        disconnect(ui->treeView->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));
        QObject::connect(ui->treeView->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));
        disconnect(ui->treeView_2->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));
        QObject::connect(ui->treeView_2->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));

}
}
void MainWindow::changeTable_item(QModelIndex a){
    QModelIndex b=a;
    stack<QModelIndex> astack;
    astack.push(a);
    Node *node0;
    bool enflag=1;
    if(sender()==ui->treeWidget->selectionModel()||sender()==ui->treeView->selectionModel()){
        node0=m_node_red.first();
    }
    else if(sender()==ui->treeWidget_2->selectionModel()||sender()==ui->treeView_2->selectionModel()){
        node0=m_node_blue.first();
    }
    else{
        enflag=0;
    }
    if(enflag){
        while(b.isValid()){
            astack.push(b);
            b=b.parent();
        }
        while(!astack.empty()&&!node0->getLinksTo().isEmpty()){
            bool findfg=0;
            for(int i=0;i<node0->getLinksTo().count();i++){
                if(node0->getLinksTo().at(i)->getToNode()->getText()==astack.top().data().toString()){
                    node0=node0->getLinksTo().at(i)->getToNode();
                    astack.pop();
                    findfg=1;
                    break;
                }
            }
            if(findfg==0)break;
        }
        if(node0){
            changeTable(node0);
        }
    }
}
void MainWindow::loadLandscape_D(){
    m_node_red.clear();
    m_node_blue.clear();
    m_link.clear();
    T_item.clear();
    m_scene->clear();
    modelin.clear();
    model_display.clear();
    myviewmodel->Tablehead.clear();
    cupos=120;
    QString findcondition=nullptr;
    for(int k=0;k<idlist_r.count();k++){
      findcondition=findcondition+"("+"idtest1"+"="+QString::number(idlist_r.at(k))+")";
         if(k<idlist_r.count()-1){
            findcondition=findcondition+"OR";
         }
     }
    if(!idlist_r.isEmpty()){
        modelroot->setFilter(findcondition);
        modelroot->select();
        this->ruledsp(1);
        addtable(m_node_red.first(),1);
        addtable(m_node_red.first(),0);

    }

    modelroot->setTable(modelroot->tableName());
    modelroot->select();
    QString findconditionb=nullptr;
    for(int k=0;k<idlist_b.count();k++){
      findconditionb=findconditionb+"("+"idtest1"+"="+QString::number(idlist_b.at(k))+")";
        if(k<idlist_b.count()-1){
           findconditionb=findconditionb+"OR";
        }
    }
    if(!idlist_b.isEmpty()){
        modelroot->setFilter(findconditionb);
        modelroot->select();
        this->ruledsp(0);
        addtable(m_node_blue.first(),1);
        addtable(m_node_blue.first(),0);

    }
    ui->r_return->setDisabled(0);

    //qDebug()<<model_display.count()<<myviewmodel->Tablehead;
    myviewmodel->disflag=1;
    myviewmodel->setview(model_display);
    ui->rule_table->setModel(myviewmodel);

}
void MainWindow::findrulebase(){
    modelroot->select();
    //this->ui->stackedWidget->setCurrentIndex(1);
    idlist_r.clear();
    idlist_b.clear();
    for(int i=0;i<modelroot->rowCount();i++){
        for(int j=0;j<ui->treeWidget->topLevelItemCount();j++){
           QTreeWidgetItem *item=ui->treeWidget->topLevelItem(j);
            if(modelroot->record(i).value(1).toString()==item->text(0)){
                 checkchildnode(i,1,item,1);
             }
        }
        for(int j=0;j<ui->treeWidget_2->topLevelItemCount();j++){
            QTreeWidgetItem *item=ui->treeWidget_2->topLevelItem(j);
                  if(modelroot->record(i).value(1).toString()==item->text(0)){
                   checkchildnode(i,1,item,0);
                  }
             }
         }
    loadLandscape_D();
}

//    if(!m_node_red.isEmpty()){
//        for(int i=0;i<m_node_red.count();i++){
//            m_node_red.at(i)->isselect=0;
//            m_node_red.at(i)->setSelected(0);
//        }
//        flag_find=0;
//        Node* node=m_node_red.first();
//        for(int i=0;i<ui->treeWidget->topLevelItemCount();i++){
//            for(int j=0;j<node->getLinksTo().count();j++){
//                Node *node1=node->getLinksTo().at(j)->getToNode();
//                QTreeWidgetItem *item=ui->treeWidget->topLevelItem(i);
//                if(node1->getText()==item->text(0)){
//                    checkchildnode(node1,item);
//                }
//            }
//        }
//        for(int i=0;i<ui->treeWidget_2->topLevelItemCount();i++){
//            for(int j=0;j<node->getLinksTo().count();j++){
//                Node *node1=node->getLinksTo().at(j)->getToNode();
//                QTreeWidgetItem *item=ui->treeWidget_2->topLevelItem(i);
//                if(node1->getText()==item->text(0)){
//                    checkchildnode(node1,item);
//                }
//            }
//        }
//        if(flag_find){
//           this->chatables();
//           ui->rule_table->setModel(myviewmodel);
//           ui->rule_table->verticalHeader()->setDefaultSectionSize(50);
//           ui->rule_table->setColumnWidth(1,200);
//           ui->rule_table->setColumnWidth(2,200);
//        }
//        else{
//             QMessageBox::information(this,"提示！","无匹配项！");
//        }
//    }
//    else{
//        QMessageBox::critical(this,"错误！","未连接数据库！");
//    }
//}
void MainWindow::checkchildnode(int row,int cloum,QTreeWidgetItem *item,bool rbf){
    if(item->childCount()==0){
        if(rbf) idlist_r.append(modelroot->record(row).value(0).toInt());
        else idlist_b.append(modelroot->record(row).value(0).toInt());
    }
    else{
        for(int j=0;j<item->childCount();j++){
         if(modelroot->record(row).value(cloum+1).toString()==item->child(j)->text(0)){
            checkchildnode(row,cloum+1,item->child(j),rbf);
         }
    }
    }
}
//    if(item->childCount()==0||node->getLinksTo().isEmpty()){
//        node->isselect=1;
//        flag_find=1;
//        node->setSelected(true);
//        node->nodeselet();
//    }
//    else{
//        for(int i=0;i<node->getLinksTo().count();i++){
//            for(int j=0;j<item->childCount();j++){
//                if(node->getLinksTo().at(i)->getToNode()->getText()==item->child(j)->text(0)){
//                    checkchildnode(node->getLinksTo().at(i)->getToNode(),item->child(j));
//                }
//            }
//        }
//    }
//}
QTreeWidgetItem* MainWindow::findchilditem(QTreeWidgetItem *parent,QString text){
    if(parent->childCount()==0){
        QTreeWidgetItem *item0=new QTreeWidgetItem;
        item0->setText(0,text);
        parent->addChild(item0);
        return item0;
    }
    else{
        for(int i=0;i<parent->childCount();i++){
            if(parent->child(i)->text(0)==text)
                return parent->child(i);
        }
        QTreeWidgetItem *item0=new QTreeWidgetItem;
        item0->setText(0,text);
        parent->addChild(item0);
        return item0;
    }
}
void MainWindow::change_Wclicked() //修改权重
{
    int row=ui->rule_table->currentIndex().row();
    QSqlRecord record0=myviewmodel->getrecord(row);
    if(!record0.isEmpty()){
        m_chang_W->show();
        m_chang_W->set_wdata(record0.value(3).toInt());
    }
}
void MainWindow::change_W(int a){
    int row=ui->rule_table->currentIndex().row();
    QSqlRecord record0=myviewmodel->getrecord(row);
    myviewmodel->set_Wvalue(row,a);
    m_chang_W->close();
}
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    if(!this->pTitleBar->window()->isMaximized()){
    switch(msg->message)
        {
        case WM_NCHITTEST:
            int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
            int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
            if(xPos < boundaryWidth && yPos<boundaryWidth)                    //左上角
                *result = HTTOPLEFT;
            else if(xPos>=width()-boundaryWidth&&yPos<boundaryWidth)          //右上角
                *result = HTTOPRIGHT;
            else if(xPos<boundaryWidth&&yPos>=height()-boundaryWidth)         //左下角
                *result = HTBOTTOMLEFT;
            else if(xPos>=width()-boundaryWidth&&yPos>=height()-boundaryWidth)//右下角
                *result = HTBOTTOMRIGHT;
            else if(xPos < boundaryWidth)                                     //左边
                *result =  HTLEFT;
            else if(xPos>=width()-boundaryWidth)                              //右边
                *result = HTRIGHT;
            else if(yPos<boundaryWidth)                                       //上边
                *result = HTTOP;
            else if(yPos>=height()-boundaryWidth)                             //下边
                *result = HTBOTTOM;
            else              //其他部分不做处理，返回false，留给其他事件处理器处理
               return false;
            return true;
        }
    }
        return false;         //此处返回false，留给其他事件处理器处理
}
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
        clickPos=e->pos();
}

