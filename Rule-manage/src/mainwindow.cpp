#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "srcsq/node.h"
#include"srcsq/link.h"
#include<QTextEdit>
#include<QStack>
#include <QSqlError>
#include <QMessageBox>
#include<QFileDialog>
#include "addruledialog.h"
#include "srcsq/datamanage.h"
#include<QGraphicsDropShadowEffect>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
      ui->setupUi(this);

     ui->splitter->setStretchFactor(1,1);
     ui->splitter->setStretchFactor(0,2);
              //->setStyleSheet("background-color:transparent");
      m_findwindow=new findDialog(this);
      m_logwindow=new logdialog(this);
      addwindow=new addruleDialog(this);
      changewindow=new changeDialog(this);
      add_table0=new addsqltable(this);
      boundaryWidth=4;
      setWindowFlags(Qt::FramelessWindowHint);
      //setWindowFlags(Qt::FramelessWindowHint | windowFlags());
      //setAttribute(Qt::WA_TranslucentBackground);
      pTitlebar = new TitleBar(this);
      pTitlebar->setObjectName("m_Titlebar");
     installEventFilter(pTitlebar);
      QVBoxLayout *pLayout = new QVBoxLayout();
        pLayout->addWidget(pTitlebar);
         pLayout->addStretch();
         pLayout->setSpacing(0);
         pLayout->setContentsMargins(0, 0, 0, 0);
      //pLayout->addLayout(ui->verticalLayout_9,1);
      ui->verticalLayout->insertLayout(0,pLayout);
      ui->verticalLayout->setContentsMargins(0,0,0,0);
      ui->verticalLayout->setStretch(1,1);
      ui->verticalLayout->setSpacing(1);
      setWindowTitle(tr("规则库管理工具"));
      QGraphicsDropShadowEffect *pEffect = new QGraphicsDropShadowEffect(this);
       pEffect->setOffset(0, 0);
      pEffect->setColor(QColor(QStringLiteral("black")));
      pEffect->setBlurRadius(30);
      this->setGraphicsEffect(pEffect);
      menuflag=1;
      ui->m_slider->setMinimum(-20);  // 最小值
      ui->m_slider->setMaximum(20);  // 最大值
      ui->m_slider->setSingleStep(1); // 步长
      ui->m_slider->setValue(0); // 步长
      adjust_n=0;//节点图大小参数
      rootflag=1;
      //ui->listView->(false);
      //ui->listWidget->setCo(QColor(32, 53, 74));
      //ui->listView->setColorBg(QColor(52, 73, 94), QColor(24, 189, 155), QColor(24, 189, 155, 150));
      //ui->listView->setColorText(QColor(254, 255, 255), QColor(252, 252, 252), QColor(0, 0, 0));
     ui->stackedWidget->setCurrentIndex(0);
     QObject::connect(ui->addputton, SIGNAL(clicked()), this, SLOT(addwindowshow()));
     QObject::connect(ui->findputton, SIGNAL(clicked()), this, SLOT(m_findshow()));
     QObject::connect(ui->submitputton, SIGNAL(clicked()), this, SLOT(m_submit_clicked()));
     QObject::connect(ui->repputton, SIGNAL(clicked()), this, SLOT(m_dismiss_clicked()));
     QObject::connect(ui->delputton, SIGNAL(clicked()), this, SLOT(m_remove_checked()));
     QObject::connect(ui->returnputton, SIGNAL(clicked()), this, SLOT(m_change_clicked()));
     QObject::connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(m_find_clicked()));
     //QObject::connect(m_findwindow, SIGNAL(sendflag(bool)), this, SLOT(m_find_clicked()));
     QObject::connect(ui->m_slider, SIGNAL(valueChanged(int)), this, SLOT(adjustscene(int)));
     QObject::connect(ui->addputton_2, SIGNAL(clicked()), this, SLOT(m_logshow()));
     QObject::connect(m_logwindow, SIGNAL(sendflag(bool)), this, SLOT(rulebaseload()));
     QObject::connect(m_logwindow, SIGNAL(sendclose_flag(bool)), this, SLOT(close()));
     QObject::connect(ui->outputfile, SIGNAL(clicked()), this, SLOT(m_out_clicked()));
     QObject::connect(ui->re_chose, SIGNAL(clicked()), this, SLOT(oncheck_clicked()));
     QObject::connect(ui->checkall, SIGNAL(clicked()), this, SLOT(oncheckall_clicked()));
     QObject::connect(ui->r_return, SIGNAL(clicked()), this, SLOT(Returnroottable()));
     QObject::connect(addwindow,SIGNAL(sendflag(bool)),this,SLOT(m_addrule()));
     QObject::connect(add_table0,SIGNAL(send_flag1(bool)),this,SLOT(updateID()));
     QObject::connect(changewindow,SIGNAL(send_chflag(bool)),this,SLOT(changerule()));

     connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->comboBox_4,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
     connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(hideheadname()));
     connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(open_close(int)));
     m_scene = new Scene(0,0,0,0,this);
     ui->groupBox->hide();
     ui->group_edit->hide();
     ui->checkall->hide();
     ui->re_chose->hide();
     ui->checkBox->hide();

     ui->graphicsView->setScene(m_scene);
     ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);

     ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
     ui->tableView_2->setContextMenuPolicy(Qt::CustomContextMenu);

     //connect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu(QPoint)));
     createActions();
     initViewActions();
     ui->addputton->setDisabled(true);
     ui->findputton->setDisabled(true);
     ui->submitputton->setDisabled(true);
     ui->repputton->setDisabled(true);
     ui->delputton->setDisabled(true);
     ui->returnputton->setDisabled(true);
     ui->r_return->setDisabled(true);
     ui->checkall->setDisabled(true);
     ui->re_chose->setDisabled(true);
     ui->outputfile->setDisabled(true);
     ui->checkBox_2->setDisabled(1);
     //ui->checkBox_2->setDisabled(1);
     //this->rulebaseload();

//     QFile file(":/style.qss");
//     file.open(QFile::ReadOnly);
//     QString styleSheet = QString(file.readAll());
//     this->setStyleSheet(styleSheet);
//     m_logwindow->show();



    // open_close(Qt::Unchecked);

}
void MainWindow::open_close(int flag){
    if(flag==Qt::Checked){
        ui->group_edit->show();
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
        ui->group_edit->hide();
        ui->checkall->hide();
        ui->re_chose->hide();
        ui->checkBox->hide();
        m_topMenu->setEnabled(0);
        m_topMenu->hideTearOffMenu();
        myviewmodel->open_close=0;
        ui->checkBox->setCheckState(Qt::Checked);
        disconnect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu(QPoint)));
        //ui->tableView_2->hideColumn(0);
        //ui->tableView_2->verticalHeader()->setVisible(1);
        //ui->tableView_2->verticalHeader()->show();
    }
}
void MainWindow::Returnroottable(){
    model_display.clear();
    modelroot->setTable("test1");
    modelroot->select();
    myviewmodel->Tablehead.clear();
    myviewmodel->disflag=0;
    model_display.append(modelroot);
    myviewmodel->setview(model_display);
    ui->addputton->setEnabled(0);
    ui->findputton->setEnabled(0);
    ui->submitputton->setEnabled(0);
    ui->repputton->setEnabled(0);
    ui->delputton->setEnabled(0);
    ui->returnputton->setEnabled(0);
    ui->outputfile->setDisabled(true);
    rootflag=1;
}
void MainWindow::rulebaseload(){
    ui->checkall->setEnabled(true);
    ui->re_chose->setEnabled(true);
    m_scene->clear();
    m_nodeQueue.clear();
    m_link.clear();
    this->T_item.clear();
    currentTablename="test1";

   // ui->checkBox_2->setCheckState(Qt::Unchecked);


    QString pssw=this->m_logwindow->getpassword();
    QString username=this->m_logwindow->getusername();
    //db=ConnectionPool::openConnection(username, pssw,name);
   //QString dirPath=QFileDialog::getSaveFileName(this,"保存配置文件","/1.ini","INI(.ini)");
   QString filePath = ":/1.ini";
    db=ConnectionPool::openConnection_2(filePath,username,pssw);
    if(!db.open()){
        QMessageBox::warning(this,QString("提示!"),QString("连接数据库错误"));
        //m_logwindow->show();
    }
    else{
        m_logwindow->close();
        modelroot=new QSqlTableModel(this,db);
        myviewmodel=new viewmodel(this);
        //disconnect(myviewmodel,SIGNAL(sendRowchanged(bool)),this,SLOT(hideheadname()));
        connect(myviewmodel,SIGNAL(sendRowchanged(bool)),this,SLOT(hideheadname()));
        myviewmodel->EntoCh=new QSqlTableModel(this,db);
        myviewmodel->EntoCh->setTable("en_ch");
        myviewmodel->EntoCh->select();
        myviewmodel->rulefact->model_fact=new QSqlTableModel(this,db);
        myviewmodel->rulefact->model_fact->setTable("rule_fact");
        myviewmodel->rulefact->model_fact->select();

        myviewmodel->rulefact->model_fact->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if(modelroot){
            modelin.clear();
            model_display.clear();
            modelroot->setTable("test1");
            modelroot->setEditStrategy(QSqlTableModel::OnManualSubmit);
            //modelin.at(0)->setEditStrategy(QSqlTableModel::OnManualSubmit);
            modelroot->select();
            modelin.append(modelroot);
            model_display.append(modelroot);
            myviewmodel->setview(model_display);
            ui->tableView_2->setModel(myviewmodel);
            this->ruledsp();
            ui->r_return->setDisabled(0);
            addtable(m_nodeQueue.first(),1);
        }
        LoadClassifyFile();
        if(!ui->checkBox_2->isEnabled()){
            ui->checkBox_2->setEnabled(1);
        }
        //if(ui->checkBox_2->setDisabled(0))
        open_close(ui->checkBox_2->checkState());
        this->ui->stackedWidget->setCurrentIndex(1);
    }

//    ui->addputton->setEnabled(true);
//    ui->findputton->setEnabled(true);
//    ui->submitputton->setEnabled(true);
//    ui->repputton->setEnabled(true);
//    ui->delputton->setEnabled(true);
//    ui->returnputton->setEnabled(true);
}
void MainWindow::LoadClassifyFile(){
    QString filePath = QFileDialog::getOpenFileName(this,tr("加载态势描述文件")," ", tr("XML files (*.xml);;ALL files (*.*)"));
    //QDomDocument doc;
    QList<QStandardItem*>aItemlist;
    QFile file(filePath); //相对路径、绝对路径、资源路径都行
    if(!file.open(QFile::ReadOnly))
        return;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();
    addwindow->doc=doc;
    changewindow->doc=doc;
    addwindow->LoadClassifyFile();

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
     //qDebug()<<"aa";
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
void MainWindow::oncheck_clicked(){
    for(int i=0;i<=myviewmodel->listnum.back();i++){
        myviewmodel->setData(myviewmodel->index(i,0),myviewmodel->data(myviewmodel->index(i,0),Qt::CheckStateRole)== Qt::Checked ? Qt::Unchecked : Qt::Checked,Qt::CheckStateRole);
        }
    myviewmodel->updata();
}
void MainWindow::oncheckall_clicked(){
    if(ui->checkall->isChecked()){
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
    dirPath=QFileDialog::getSaveFileName(this,"导出规则文件","/rule_out.xml","XMl(.xml)");
    QString XmlFilename=  "test.xml";
    myviewmodel->WriteXml(dirPath);
        //po->waitForStarted();
}
void MainWindow::ruledsp(){
    Node *node1 = new Node(this);
    node1->setText(QString("规则库"));//
     int rowNum = modelroot->rowCount();
     int colNum = modelroot->columnCount();
    m_scene->addItem(node1);
    m_nodeQueue.append(node1);
    node1->setPos(100, m_scene->height() / 2.0+100);
    node1->setBasePoint(node1->pos());
    node1->setcolornum(0);
    for(int i=0;i<rowNum;i++){
        Node*currentnode=node1;
        QList<Link *> linksTo = node1->getLinksTo();
        if (linksTo.isEmpty()){
            onAdd(node1,modelroot->index(i,1).data().toString());
            onAdd(m_nodeQueue.back(),modelroot->index(i,2).data().toString());
            onAdd(m_nodeQueue.back(),modelroot->index(i,3).data().toString());
            onAdd(m_nodeQueue.back(),modelroot->index(i,4).data().toString());
            onAdd(m_nodeQueue.back(),modelroot->index(i,5).data().toString());;
        }
        else{
            for(int j=1;j<colNum;j++){
            currentnode=findnextnode(currentnode,modelroot->index(i,j).data().toString());
            }
        }
    }
   adjustnode();
   tiltleItem *item1=new tiltleItem(node1);

   T_item.append(item1);
   m_scene->addItem(item1);
}
Node*MainWindow::findnextnode(Node*node,QString data0){
    QList<Link *> linksTo = node->getLinksTo();
    for(int i=0;i<linksTo.count();i++){
        if(data0==linksTo.at(i)->getToNode()->getText()){
            return linksTo.at(i)->getToNode();
        }
    }
    onAdd(node,data0);
    return m_nodeQueue.back();
}
Scene *MainWindow::getruleScene()
{
    return m_scene;
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::hideheadname(){
    int flag=ui->checkBox->checkState();
    if(myviewmodel->disflag){
        if(flag==Qt::Checked){
            ui->tableView_2->hideRow(0);
         //   qDebug()<<myviewmodel->listnum;
            for(int i=1;i<=myviewmodel->listnum.back();i++){
                if(myviewmodel->listnum.contains(i)){
                        ui->tableView_2->hideRow(i);
                }
                else{
                        ui->tableView_2->showRow(i);
                }
            }
        }
        else if(flag==Qt::Unchecked){
          //  qDebug()<<ui->tableView_2->isRowHidden(0)<<myviewmodel->rowcount;
            for(int i=0;i<=myviewmodel->listnum.back();i++){
                     ui->tableView_2->showRow(i);
            }
        }
    }
    else{
        for(int i=0;i<myviewmodel->listnum.back();i++){
                 ui->tableView_2->showRow(i);
        }
    }
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
            for(int i=0;i<m_nodeQueue.count();i++){
                if( m_nodeQueue.at(i)!=selectedNode){
                m_nodeQueue.at(i)->setBasePoint(QPointF(m_nodeQueue.at(i)->x() + moveX, m_nodeQueue.at(i)->y() + moveY));
                m_nodeQueue.at(i)->setPos(m_nodeQueue.at(i)->getBasePoint().x() , m_nodeQueue.at(i)->getBasePoint().y());
                }
            }
             for(int j=0;j<m_link.count();j++){
             m_link.at(j)->adjust();}
            }
}
void MainWindow::onAdd(Node*fromNode,QString name)
{
    Node *node = new Node(this);
    node->setText(name);
    m_nodeQueue.append(node);
    QList<QGraphicsItem *> items = m_scene->items();
    m_scene->addItem(node);
    node->setPos(100,100);
    node->setcolornum(fromNode->nodecolor+1);
    Link *newLink = new Link(fromNode, node);
    m_link.append(newLink);
    m_scene->addItem(newLink);
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
void MainWindow::adjustnode(){
    QList<Node*>nodelist;
    QList<Node*>nodelist2;
    int pos=120;
    Node*currentnode=m_nodeQueue.first();
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
}
void MainWindow::m_submit_clicked()//提交
{
    if(rootflag==1){
        modelroot->database().transaction(); //
        if (modelroot->submitAll()) {
            modelroot->database().commit(); //
                m_scene->clear();
            //qDeleteAll(m_nodeQueue);//.........................
                m_nodeQueue.clear();
                m_link.clear();
                this->ruledsp();


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
//    //            if(rootflag==1){
//    //                m_scene->clear();
//    //            //qDeleteAll(m_nodeQueue);//.........................
//    //                 m_nodeQueue.clear();
//    //                m_link.clear();
//    //                this->ruledsp();
//    //            }
//            } else {
//                modelin.at(i)->database().rollback(); //
//                QMessageBox::warning(this, tr("tableModel"),
//                                     tr("database error: %1").arg(modelin.at(i)->lastError().text()));
//            }
//        }
    }
}
void MainWindow::m_dismiss_clicked() //撤销
{
    for(int i=0;i<modelin.count();i++){
     modelin.at(i)->select();
    }
    myviewmodel->rulefact->model_fact->select();
    myviewmodel->setview(myviewmodel->modellist0);
}
void MainWindow::m_find_clicked() //查询
{
    if(findnode5){
        //findnode5->setSelected(1);
        this->changeTable(findnode5);
    }
//    int curRow = ui->tableView_2->currentIndex().row();
//    myviewmodel->getrecord(curRow);
//    //menuflag=0;
//    QList<QString> name = m_findwindow->getfindtext();
//    m_findwindow->close();
//    bool fa=myviewmodel->findrecord(name);
//    if(fa==0){
//        QMessageBox::warning(this, tr("result"),
//                             tr("can't find rule"));
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
   // changewindow->show();
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

            QMessageBox::warning(this,QString("提示!"),QString("修改成功！"));
        }
        else{
            QMessageBox::warning(this,QString("提示!"),QString("修改失败，规则重复或规则无改动"));
        }

    }
}
void MainWindow::m_remove_clicked() //删除
{
    int curRow = ui->tableView_2->currentIndex().row();
    int ok = QMessageBox::warning(this,QString("提示!"),QString("确定删除第"+QString::number(curRow+1)+"行？"),
                         QMessageBox::Yes,QMessageBox::No);

    if(ok == QMessageBox::No)
    {
       modelin.at(0)->revertAll(); //回退
    }
    else{
        if(rootflag==1){
            modelroot->removeRow(curRow-1);
            del_sqltable(modelroot->index(curRow-1,modelroot->columnCount()-1).data().toString());
            for(int i=0;i<modelroot->rowCount();i++){
                modelroot->setData(modelroot->index(i,0),i+1);
            }
            modelroot->submitAll();
        }
        else{
            myviewmodel->removeRow(curRow);
        }
    }
    myviewmodel->setview(myviewmodel->modellist0);
}
void MainWindow::m_remove_checked(){
    int ok = QMessageBox::warning(this,QString("提示!"),QString("确定删除选中行？"),
                         QMessageBox::Yes,QMessageBox::No);
    if(ok){
        myviewmodel->removeRow_checked();
        }
      myviewmodel->setview(myviewmodel->modellist0);

}
//void MainWindow::m_add_clicked() //添加
//{
//    //addruleDialog*addwindow=new addruleDialog(this);
//    addwindow->show();
//    //ui->stackedWidget->setCurrentIndex(3);
//    //int currow=ui->tableView_2->currentIndex().row();
//    //myviewmodel->insertRow(currow);
//    // myviewmodel->setview(myviewmodel->modellist0);
//    //int rowNum = modelroot->rowCount();
//    //int id = rowNum+1;
//    //modelroot->insertRow(rowNum);
//    //modelroot->setData(modelroot->index(rowNum,0),id,Qt ::DisplayRole);
//    //model->submitAll();
//}
void MainWindow::addwindowshow(){
    if(rootflag==0){
        addwindow->show();
        addwindow->cleartext();
    }
    else{
        int row=ui->tableView_2->currentIndex().row();
        //modelroot->insertRow(row);
        QList<QString>list_0;
        for(int i=0;i<modelroot->record(row).count();i++){
            list_0.append(modelroot->record(row).value(i).toString());
        }
        add_table0->datain(list_0);
        add_table0->show();

    }
}
void MainWindow::m_addrule(){
    QList<QString>addrule;
    int curRow = ui->tableView_2->currentIndex().row();
    if(curRow<0){
        curRow=0;
    }
    addrule.append(addwindow->getIf());
    addrule.append(addwindow->getThen());
    addrule.append(addwindow->getWeight());
    bool flag=myviewmodel->addrecord(addrule,curRow);
    if(flag){
        QMessageBox::warning(this,QString("提示!"),QString("添加成功"));
    }
    else{
        QMessageBox::warning(this,QString("提示!"),QString("规则重复，添加失败"));
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
    m_actDel = new QAction("删除(Del)", this);
    m_actDel->setShortcut(tr("Del"));
    connect(m_actDel, SIGNAL(triggered(bool)), this, SLOT(m_remove_clicked()));
    m_topMenu->addAction(m_actDel);
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
void MainWindow::onUpdateContextMenu(QPoint pos)
{
    m_actAdd->setEnabled(menuflag);
    m_actDel->setEnabled(menuflag);
    m_actDis->setEnabled(menuflag&&!rootflag);
    m_actSubmit->setEnabled(menuflag);
    //m_actFind->setEnabled(menuflag&&!rootflag);
    m_actBack->setEnabled(menuflag&&!rootflag);
    QModelIndex index = ui->tableView_2->indexAt(pos);
    if (index.isValid())
    {
    m_topMenu->exec(QCursor::pos()); //
    }
}
void MainWindow::addwindowshow_node(QStringList list_0){
        add_table0->datain(list_0);
        add_table0->show();

}
void MainWindow::m_findshow(){
    ui->comboBox->clear();
    findnode1=m_nodeQueue.first();
    for(int i=0;i<findnode1->getLinksTo().count();i++){

        ui->comboBox->addItem(findnode1->getLinksTo().at(i)->getToNode()->getText());
    }
}
void MainWindow::setcomboxitem(int index){
        if (sender() == ui->comboBox&&index!=-1)
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
//    if(node->getLinksTo().isEmpty()){
//        modelin.append(new QSqlTableModel(this,db));
//        modelin.back()->setEditStrategy(QSqlTableModel::OnManualSubmit);
//        modelin.back()->setTable(node->getText());
//        modelin.back()->select();
//        myviewmodel->Tablehead.append(node->getheadname());
//    }
//    else {
//        for(int i=0;i<node->getLinksTo().count();i++){
//            addtable(node->getLinksTo().at(i)->getToNode());
//        }
//    }
    if(flag){
        if(node->getLinksTo().isEmpty()){
            modelin.append(new QSqlTableModel(this,db));
            modelin.back()->setEditStrategy(QSqlTableModel::OnManualSubmit);
            modelin.back()->setTable(node->getText());
            modelin.back()->select();
            myviewmodel->Tablehead.append(node->getheadname());
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
                    model_display.append(modelin.at(i));
                    myviewmodel->Tablehead.append(node->getheadname());
                    break;
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

    myviewmodel->disflag=1;

    myviewmodel->setview(model_display);

//    myviewmodel->rulefact->model_fact->setTable("rule_fact");
//     myviewmodel->rulefact->model_fact->select();
    ui->addputton->setEnabled(true);
    ui->findputton->setEnabled(true);
    ui->submitputton->setEnabled(true);
    ui->repputton->setEnabled(true);
    ui->delputton->setEnabled(true);
    ui->returnputton->setEnabled(true);
    ui->outputfile->setEnabled(true);
    rootflag=0;


}
void MainWindow::chatables(){
    model_display.clear();
    myviewmodel->Tablehead.clear();

    QList<Node*>selectlist;
    myviewmodel->disflag=1;
//    for(int i=0;i<m_nodeQueue.count();i++){
//        if(m_nodeQueue.at(i)->getLinksTo().isEmpty()&&m_nodeQueue.at(i)->isselect==1){
//            selectlist.append(m_nodeQueue.at(i));
//            modelin.append(new QSqlTableModel(this,db));
//            modelin.back()->setTable(m_nodeQueue.at(i)->getText());
//            modelin.back()->setEditStrategy(QSqlTableModel::OnManualSubmit);
//            modelin.back()->select();
//            myviewmodel->Tablehead.append(m_nodeQueue.at(i)->getheadname());
//        }
//    }
    for(int i=0;i<m_nodeQueue.count();i++){
        if(m_nodeQueue.at(i)->getLinksTo().isEmpty()&&m_nodeQueue.at(i)->isselect==1){
            for(int j=0;j<modelin.count();j++){
                if(modelin.at(j)->tableName()==m_nodeQueue.at(i)->getText()){
                    model_display.append(modelin.at(j));
                }
            }
            myviewmodel->Tablehead.append(m_nodeQueue.at(i)->getheadname());
        }
    }
    //myviewmodel->rulefact->model_fact->setTable("rule_fact");
    //myviewmodel->rulefact->model_fact->select();
    myviewmodel->setview(model_display);
    ui->addputton->setEnabled(true);
    ui->findputton->setEnabled(true);
    ui->submitputton->setEnabled(true);
    ui->repputton->setEnabled(true);
    ui->delputton->setEnabled(true);
    ui->returnputton->setEnabled(true);
    ui->outputfile->setEnabled(true);
    rootflag=0;


}
//void MainWindow::on_listWidget_pressed()
//{
////    //QModelIndex index = ui->listWidget->currentIndex();
////    //QString text = index.data().toString();
////    if (text == "-首页") {
////        ui->stackedWidget->setCurrentIndex(0);
////    } else if (text == "规则管理") {
////        ui->stackedWidget->setCurrentIndex(1);
////    } /*else if (text == "状态选择") {
////        ui->stackedWidget->setCurrentIndex(2);
////    } else if (text == "规则管理") {
////        ui->stackedWidget->setCurrentIndex(3);
////    }*/
//}
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
void MainWindow::del_sqltable(QString name){
    bool flag=datamanage::deltable(db,name);
    if(flag){
            QMessageBox::about(this, "删除", " delete table success");
                  }
             else{

             QMessageBox::about(this, "删除", "error delete table");
    }
}
void MainWindow::updateID(){
    int row=modelroot->rowCount();
    QList<QString>list_out=add_table0->dataout();
    add_table0->close();

    int id=modelroot->rowCount();

    modelroot->insertRow(row);
    modelroot->setData(modelroot->index(row,0),id+1);

    for(int i=1;i<list_out.count();i++){
        modelroot->setData(modelroot->index(row,i),list_out.at(i));
    }
//    for(int i=0;i<modelroot->rowCount();i++){
//        modelroot->setData(modelroot->index(i,0),i+1);
//    }
    bool flag=add_sqltable(list_out.back());
    if(flag){
        this->m_submit_clicked();
    }
    else{
        modelroot->revertAll();
    }
    myviewmodel->setview(myviewmodel->modellist0);

    //modelroot->select();
   // modelroot->submitAll();
}



bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG* msg = (MSG*)message;
    if(!this->pTitlebar->window()->isMaximized()){
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
//void MainWindow::mouseMoveEvent(QMouseEvent *e)
//{
//    if(e->buttons()&Qt::LeftButton)
//        if(!this->pTitlebar->window()->isMaximized()){
//            move(e->pos()+pos()-clickPos);
//        }
//}


