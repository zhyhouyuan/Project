#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/node.h"
#include"src/link.h"
#include<QTextEdit>
#include<QStack>
#include <QSqlError>
#include <QMessageBox>
#include<QFileDialog>
#include "uisrc/addruledialog.h"
#include "src/datamanage.h"
#include<QtConcurrent>
#include<QGraphicsDropShadowEffect>
#include"uisrc/titlebar.h"
#include <stack>
#include<QThread>
#include<QGraphicsProxyWidget>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose);
    currentTablename="rulebase";
    //m_findwindow=new findDialog(this);
    m_logwindow=new logdialog(this);
    addwindow=new addruleDialog(this);
    changewindow=new changeDialog(this);
    //add_table0=new addsqltable(this);
    m_chang_W=new Change_WDialog(this);
    cupos=120;
    this->loadfile=0;
    //屏蔽默认框
    // setWindowFlags(Qt::FramelessWindowHint);
    // setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // setWindowFlags(Qt::CustomizeWindowHint);
    //setAttribute(Qt::WA_TranslucentBackground);
    //    pTitleBar = new TitleBar(this);
    //      pTitleBar->setObjectName("m_Titlebar");
    //      installEventFilter(pTitleBar);
    //      QVBoxLayout *pLayout = new QVBoxLayout();
    //      pLayout->addWidget(pTitleBar);
    //      pLayout->addStretch();
    //      pLayout->setSpacing(0);
    //      pLayout->setContentsMargins(0, 0, 0, 0);
    //     //pLayout->addLayout(ui->verticalLayout_9,1);
    //      ui->verticalLayout_7->insertLayout(0,pLayout);
    ui->verticalLayout_7->setContentsMargins(0,0,0,0);

    ui->verticalLayout_7->setStretch(1,1);

    setWindowTitle(tr("  规则设计与优化工具"));
    //      QGraphicsDropShadowEffect *pEffect = new QGraphicsDropShadowEffect(this);
    //      pEffect->setOffset(20, 20);
    //      pEffect->setColor(QColor(QStringLiteral("black")));
    //      pEffect->setBlurRadius(30);
    //      this->setGraphicsEffect(pEffect);
    ui->groupBox_4->hide();
    ui->groupBox_land->show();
    ui->graphicsView->hide();
    //menuflag=1;
   // QGroupBox *sliderbox=new QGroupBox;
    //sliderbox->setLayout()
    m_slider=new QSlider(Qt::Horizontal,ui->graphicsView);
    //m_slider->setWindowFlag(Qt::WindowStaysOnTopHint);
    //m_slider->setTickPosition()
    //m_slider->s
    m_slider->setMinimum(-20);  // 最小值
    m_slider->setMaximum(20);  // 最大值
    m_slider->setSingleStep(1); // 步长
    m_slider->setValue(0); // 步长
    //m_scene->addWidget(m_slider);
    adjust_n=0;//节点图大小参数
    rootflag=0;
    dis_flag0=0;

    ui->stackedWidget->setCurrentIndex(0);
    //ui->splitter->setStretchFactor(0,1);
   // ui->splitter->setStretchFactor(1,1);
    ui->splitter->setSizes(QList<int>()<<200<<500);
    ui->splitter_2->setStretchFactor(0,1);
    ui->splitter_2->setStretchFactor(1,3);
    // ui->treeView_r->setHorizontalScrollBarPolicy()
    QObject::connect(ui->addputton, SIGNAL(clicked()), this, SLOT(addwindowshow()));
    QObject::connect(ui->findputton, SIGNAL(clicked()), this, SLOT(m_findshow()));
    QObject::connect(ui->submitputton, SIGNAL(clicked()), this, SLOT(m_submit_clicked()));
    QObject::connect(ui->repputton, SIGNAL(clicked()), this, SLOT(m_dismiss_clicked()));
    QObject::connect(ui->returnputton, SIGNAL(clicked()), this, SLOT(m_change_clicked()));
    //QObject::connect(m_findwindow, SIGNAL(sendflag(bool)), this, SLOT(m_find_clicked()));
    QObject::connect(ui->find_s, SIGNAL(clicked()), this, SLOT(m_find_clicked()));
    QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(adjustscene(int)));

    QObject::connect(ui->loadscape, SIGNAL(clicked()), this, SLOT(loadLandscape()));
    QObject::connect(ui->loadfile, SIGNAL(clicked()), this, SLOT(LoadClassifyFile()));
    QObject::connect(m_logwindow, SIGNAL(sendflag(bool)), this, SLOT(rulebaseload()));
    QObject::connect(m_logwindow, SIGNAL(send_closeflag(bool)), this, SLOT(close()));

    QObject::connect(ui->outputfile, SIGNAL(clicked()), this, SLOT(m_out_clicked()));
    QObject::connect(ui->re_chose, SIGNAL(clicked()), this, SLOT(oncheck_clicked()));
    QObject::connect(ui->checkall, SIGNAL(stateChanged(int)), this, SLOT(oncheckall_clicked(int)));

    QObject::connect(ui->re_chose_W, SIGNAL(clicked()), this, SLOT(oncheck_clicked()));
    QObject::connect(ui->checkall_W, SIGNAL(stateChanged(int)), this, SLOT(oncheckall_clicked(int)));

    QObject::connect(ui->r_return, SIGNAL(clicked()), this, SLOT(Returnroottable()));
    QObject::connect(addwindow,SIGNAL(sendflag(bool)),this,SLOT(m_addrule()));
    //QObject::connect(add_table0,SIGNAL(send_flag1(bool)),this,SLOT(updateID()));
    QObject::connect(changewindow,SIGNAL(send_chflag(bool)),this,SLOT(changerule()));
    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(loadLandscape()));
    QObject::connect(m_chang_W, SIGNAL(send_chflag(int)), this, SLOT(change_W(int)));
    QObject::connect(ui->change_w,SIGNAL(clicked()),this,SLOT(change_Wclicked()));
    // QObject::connect(ui->load_rule,SIGNAL(clicked()),this,SLOT(findrulebase()));

    QObject::connect(ui->repputton_W, SIGNAL(clicked()), this, SLOT(m_dismiss_clicked()));
    QObject::connect(ui->submitputton_W, SIGNAL(clicked()), this, SLOT(m_submit_W()));
    connect(ui->treeView_r,SIGNAL(sendChange(bool)),this,SLOT(item_upcheck()));
    //connect(ui->treeView,SIGNAL(sendChange(bool)),this,SLOT(item_upcheck()));
    //     ui->comboBox->blockSignals(true);
    //     ui->comboBox_2->blockSignals(true);
    //     ui->comboBox_3->blockSignals(true);
    //     ui->comboBox_4->blockSignals(true);
    //     ui->comboBox_5->blockSignals(true);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
    connect(ui->comboBox_2,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
    connect(ui->comboBox_3,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
    connect(ui->comboBox_4,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
    connect(ui->comboBox_5,SIGNAL(currentIndexChanged(int)),this,SLOT(setcomboxitem(int)));
    connect(ui->checkBox,SIGNAL(stateChanged(int)),this,SLOT(hideheadname()));
    connect(ui->checkBox_2,SIGNAL(stateChanged(int)),this,SLOT(hideheadname()));

    connect(ui->Editmode,SIGNAL(stateChanged(int)),this,SLOT(open_close(int)));
    //ui->treeView=ui->treeView_r;
    ui->treeView->setModel(ui->treeView_r->model);
    QObject::connect(ui->treeView->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));
    QObject::connect(ui->treeView_r->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(changeTable_item(QModelIndex)));

    //QObject::connect(ui->graphicsView,SIGNAL(si));

    m_scene = new Scene(0,0,0,0,this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->tableView_2->setContextMenuPolicy(Qt::CustomContextMenu);
    m_slider->resize(100,30);
    //sliderbox->resize(20,100);
    m_slider->move(10,10);

    //m_slider->setStyleSheet("QSlider::groove:horizontal {height: 6px;background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71));}QSlider::handle:horizontal {width: 16px; background: rgb(0, 160, 230); margin: -6px 0px -6px 0px;border-radius: 8px;}");
    //QGraphicsProxyWidget *sl=m_scene->addWidget(sliderbox);
    //sliderbox->setStyleSheet("background:rgb(0,0,0)");
    //sl->setPos(ui->graphicsView->width()-m_slider->width(),ui->graphicsView->height()-m_slider->height());



    //connect(ui->tableView_2, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu(QPoint)));
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
void MainWindow::item_upcheck(){
    model_display.clear();
    myviewmodel->Tablehead.clear();

    auto&&it=ui->treeView_r->CheckList.begin();
    while(it!=ui->treeView_r->CheckList.end()){
        if(it.value()>0 && it.key()!=-1){
            for(int i=0;i<modelin.count();i++){
                if(modelin.at(i)->tableName()==ui->treeView_r->item_tablename[it.key()]){
                    model_display.append(modelin.at(i));
                    myviewmodel->Tablehead.append(ui->treeView_r->headnamelist[it.key()]);
                }
               //qDebug()<<modelin.at(i)->tableName()<<ui->treeView_r->item_tablename[it.key()];
            }
        }
        it++;
    }
    myviewmodel->setview(model_display);
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
    file.close();
    QDomElement root=doc.documentElement(); //返回根节点
    QDomNode node=root.firstChild(); //获得第一个子节点
    if(root.tagName()=="模型描述"&&!node.isNull()){
        changewindow->doc=this->doc;
        addwindow->doc=this->doc;
        addwindow->LoadClassifyFile();
        addCHtoEN(node.toElement());
        this->loadfile=1;
    }
    else{
        QMessageBox::warning(this,QString("提示，文件内容不符"),QString("请加载正确的态势文件"));
    }
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
        m_slider->hide();
        QList<int>listsize;
        listsize<<200<<500;
        ui->splitter->setSizes(listsize);
    }
    else{
        ui->groupBox_land->hide();
        ui->graphicsView->show();
        m_slider->show();
        QList<int>listsize;
        listsize<<400<<400;
        ui->splitter->setSizes(listsize);
    }
    dis_flag0=!dis_flag0;

}
void MainWindow::rulebaseload(){
    m_node_red.clear();
    m_link.clear();
    T_item.clear();
    m_scene->clearitems();

    QString pssw=this->m_logwindow->getpassword();
    QString username=this->m_logwindow->getusername();

    QString filePath2=":/1.ini";
    // qDebug()<<qApp->applicationDirPath()<<"a";
    //ConnectionPool::closeConnection(db);
    db=ConnectionPool::openConnection_2(filePath2,username,pssw);

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
            modelroot->setTable(this->currentTablename);
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
            //LoadClassifyFile();
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
    //QString XmlFilename=  "test.xml";
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
        node1->setcolornum(6);
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
            delete T_item.first();
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
    }
    else{
        currentnode=m_node_blue.first();
    }
    nodelist=findlastnode(currentnode,nodelist);

    while(!nodelist.isEmpty()){
        Node*cnode=nodelist.first()->getLinkFrom()->getFromNode();
        QList<Link*>link_list1=cnode->getLinksTo();
        for(int j=0;j<link_list1.count();j++){
            pos=pos+40;
            nodelist.removeOne(link_list1.at(j)->getToNode());
            link_list1.at(j)->getToNode()->setPos(750,pos);
            link_list1.at(j)->getToNode()->setBasePoint(link_list1.at(j)->getToNode()->pos());
        }
        nodelist2.append(cnode);
        cnode->setPos(600,(cnode->getLinksTo().first()->getToNode()->y()+cnode->getLinksTo().last()->getToNode()->y())/2);
    }
    while(!nodelist2.isEmpty()){
        if(nodelist2.first()->getLinkFrom()){
            Node*cnode2=nodelist2.first()->getLinkFrom()->getFromNode();
            if(cnode2){
                cnode2->setPos(cnode2->getLinksTo().first()->getToNode()->x()-150,(cnode2->getLinksTo().first()->getToNode()->y()+cnode2->getLinksTo().last()->getToNode()->y())/2);
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
//    if(rootflag==1){
//        modelroot->database().transaction(); //
//        if (modelroot->submitAll()) {
//            modelroot->database().commit(); //
//            m_scene->clearitems();
//            //qDeleteAll(m_node_red);//.........................
//            m_node_red.clear();
//            m_link.clear();
//            qDebug()<<"提交到数据库：sucess";

//        } else {
//            modelroot->database().rollback(); //
//            QMessageBox::warning(this, tr("tableModel"),
//                                 tr("database error: %1").arg(modelroot->lastError().text()));
//            qWarning()<<tr("提交到数据库：error %1").arg(modelroot->lastError().text());
//        }
//    }
   // else{
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
   // }
}
void MainWindow::m_submit_W()//提交
{
    myviewmodel->submit_W();
}
void MainWindow::m_dismiss_clicked() //撤销
{
    //    for(int i=0;i<modelin.count();i++){
    //     modelin.at(i)->setTable(modelin.at(i)->tableName());
    //     modelin.at(i)->select();
    //    }
    //    myviewmodel->rulefact->model_fact->setTable("rule_fact_1");
    //    myviewmodel->rulefact->model_fact->select();
    //    myviewmodel->setview(model_display);
    for(int i=0;i<modelin.count();i++){
        modelin.at(i)->select();
    }
    myviewmodel->rulefact->model_fact->select();
    myviewmodel->setview(myviewmodel->modellist0);
    qDebug()<<tr("撤销未保存到数据库的修改");
    // this->hideheadname(ui->checkBox->checkState());
}

void MainWindow::m_change_clicked() //修改
{
    int row=ui->tableView_2->currentIndex().row();
    QSqlRecord record0=myviewmodel->getrecord(row);
    if(loadfile==0){
        this->LoadClassifyFile();
        return;
    }
    if(!record0.isEmpty()){
        changewindow->show();
        changewindow->setRuleData(&record0);
        changewindow->combox_rn();
    }
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
            qDebug()<<QString("修改成功!")<<QString("修改的记录：")<<record0;
        }
        else{
            QMessageBox::warning(this,QString("提示!"),QString("修改失败，规则重复或规则无改动"));
            qWarning()<<QString("修改失败，规则重复或规则无修改");
        }
    }
}
void MainWindow::addwindowshow(){
     if(loadfile){
    addwindow->show();
    addwindow->cleartext();
      }
     else{
         this->LoadClassifyFile();
     }
}
void MainWindow::m_addrule(){
    QList<QString>addrule;
    int curRow = ui->tableView_2->currentIndex().row();
    if(curRow<0) curRow=0;
    QString if_value=addwindow->getIf();
    QString then_value=addwindow->getThen();
    QString  W_value=addwindow->getWeight();
    if(if_value!=""&&then_value!="" && W_value!=""){
        addrule.append(if_value);
        addrule.append(then_value);
        addrule.append(W_value);
        bool flag=myviewmodel->addrecord(addrule,curRow);
        if(flag){
            QMessageBox::warning(this,QString("提示!"),QString("添加成功"));
            qDebug()<<QString("添加规则成功")<<QString("条件：")<<if_value<<QString("结果：")<<then_value<<QString("权重：")<<W_value;
        }
        else{
            QMessageBox::warning(this,QString("提示!"),QString("规则重复，添加失败"));
            qDebug()<<QString("添加规则失败");
        }
    }
    else{
        QMessageBox::warning(this,QString("提示!"),QString("规则缺少内容，添加失败"));
        qDebug()<<QString("添加规则失败");
    }
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
                    // if(!ui->tableView_2->isRowHidden(i))
                    ui->tableView_2->hideRow(i);
                }
                else{
                    // if(ui->tableView_2->isRowHidden(i))
                    ui->tableView_2->showRow(i);
                }
            }
        }
        else if(flag==Qt::Unchecked){
            for(int i=0;i<myviewmodel->listnum.back();i++){
                // if(ui->tableView_2->isRowHidden(i))
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
                    //  if(!ui->rule_table->isRowHidden(i))
                    ui->rule_table->hideRow(i);
                }
                else{
                    //  if(ui->rule_table->isRowHidden(i))
                    ui->rule_table->showRow(i);
                }
            }
        }
        else if(flag==Qt::Unchecked){
            for(int i=0;i<myviewmodel->listnum.back();i++){
                // if(ui->rule_table->isRowHidden(i))
                ui->rule_table->showRow(i);
            }
        }
    }
}
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
    ui->comboBox->blockSignals(true);
    ui->comboBox_2->blockSignals(true);
    ui->comboBox_3->blockSignals(true);
    ui->comboBox_4->blockSignals(true);
    ui->comboBox_5->blockSignals(true);
    if(ui->comboBox_5->count()<=0){
        ui->comboBox_5->addItem(" ");
        ui->comboBox->addItem(" ");
        ui->comboBox_2->addItem(" ");
        ui->comboBox_3->addItem(" ");
        ui->comboBox_4->addItem(" ");
        ui->comboBox_5->addItem("红方");
        ui->comboBox_5->addItem("蓝方");
    }
    ui->comboBox_5->setCurrentIndex(-1);
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_3->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->comboBox->blockSignals(false);
    ui->comboBox_2->blockSignals(false);
    ui->comboBox_3->blockSignals(false);
    ui->comboBox_4->blockSignals(false);
    ui->comboBox_5->blockSignals(false);
    ui->comboBox_5->setCurrentIndex(0);
    //findnode1=m_node_red.first();

}
void MainWindow::setItemList(QComboBox*a,QComboBox*prea,QList<Node*>&list0,QList<Node*>&listnext,int index){
    if(list0.isEmpty()){
        return;
    }
    else{
        listnext.clear();
        for(int i=1;i<a->count();i++){
            a->removeItem(i);
        }
        if(index==0){
            for(auto&findnode:list0){//list0上一级选择的节点集
                for(int i=0;i<findnode->getLinksTo().count();i++){//遍历下一级节点
                    listnext.append(findnode->getLinksTo().at(i)->getToNode());
                    for(int j=0;j<listnext.back()->getLinksTo().count();j++){
                        int row=a->findText(listnext.back()->getLinksTo().at(j)->getToNode()->getText());
                        qDebug()<<listnext.back()->getText();
                        if(row<0){
                            a->addItem(listnext.back()->getLinksTo().at(j)->getToNode()->getText());
                        }
                    }
                }
            }
        }
        else{
            for(auto&findnode:list0){
                for(int i=0;i<findnode->getLinksTo().count();i++){

                    if(findnode->getLinksTo().at(i)->getToNode()->getText()==prea->currentText()){
                        listnext.append(findnode->getLinksTo().at(i)->getToNode());
                        for(int j=0;j<listnext.back()->getLinksTo().count();j++){
                            int row=a->findText(listnext.back()->getLinksTo().at(j)->getToNode()->getText());

                            if(row<0){
                                a->addItem(listnext.back()->getLinksTo().at(j)->getToNode()->getText());
                            }
                        }
                    }
                }
            }
        }
    }
    if(a->currentIndex()==0){
        a->setCurrentIndex(-1);
    }
    a->setCurrentIndex(0);
}
void MainWindow::setcomboxitem(int index){
    if(sender() == ui->comboBox_5&&index!=-1){
        findlist1.clear();
        if(index==0){
            if(!m_node_red.isEmpty()){
                findlist1.append(m_node_red.first());
            }
            if(!m_node_blue.isEmpty()){
                findlist1.append(m_node_blue.first());
            }
        }
        else if(index==1){
            if(!m_node_red.isEmpty()){
                findlist1.append(m_node_red.first());
            }
        }
        else{
            if(!m_node_blue.isEmpty()){
                findlist1.append(m_node_blue.first());
            }
        }
        for(int i=1;i<ui->comboBox->count();i++){
            ui->comboBox->removeItem(i);
        }
        for(auto&findnode:findlist1){
            for(int i=0;i<findnode->getLinksTo().count();i++){
                int row=ui->comboBox->findText(findnode->getLinksTo().at(i)->getToNode()->getText());
                if(row<0){
                    ui->comboBox->addItem(findnode->getLinksTo().at(i)->getToNode()->getText());
                }
            }
        }
        if(ui->comboBox->currentIndex()==0){
            ui->comboBox->setCurrentIndex(-1);
        }
        ui->comboBox->setCurrentIndex(0);
    }
    else if (sender() == ui->comboBox&&index!=-1)
    {
        setItemList(ui->comboBox_2,ui->comboBox,findlist1,findlist2,index);
    }
    else if (sender() == ui->comboBox_2&&index!=-1)
    {
        setItemList(ui->comboBox_3,ui->comboBox_2,findlist2,findlist3,index);
    }
    else if (sender() == ui->comboBox_3&&index!=-1)
    {
        setItemList(ui->comboBox_4,ui->comboBox_3,findlist3,findlist4,index);
    }
    else if (sender() == ui->comboBox_4&&index!=-1){
        findlist5.clear();
        if(index==0){
            for(auto&findnode:findlist4){
                for(int i=0;i<findnode->getLinksTo().count();i++){
                    findlist5.append(findnode->getLinksTo().at(i)->getToNode());
                }
            }
        }
        else{
            for(auto&findnode:findlist4){
                for(int i=0;i<findnode->getLinksTo().count();i++){
                    if(findnode->getLinksTo().at(i)->getToNode()->getText()==ui->comboBox_4->currentText()){
                        findlist5.append(findnode->getLinksTo().at(i)->getToNode());
                    }
                }
            }
        }
    }
}
void MainWindow::m_find_clicked() //查询
{
    if(!findlist5.isEmpty()){
        model_display.clear();
        myviewmodel->Tablehead.clear();
        for(auto&&node0:findlist5){
            for(int i=0;i<node0->getLinksTo().count();i++){
                Node* node1=node0->getLinksTo().at(i)->getToNode();
                for(int j=0;j<modelin.count();j++){
                    if(modelin.at(j)->tableName()==node1->getText()){
                        if(!model_display.contains(modelin.at(j))){
                            model_display.append(modelin.at(j));
                            myviewmodel->Tablehead.append(node1->getheadname());
                        }
                        break;
                    }
                }
            }

        }
        myviewmodel->setview(model_display);
    }
    else{
        QMessageBox::warning(this, tr("结果:"),
                             tr("找不到对应的结果!"));
        qWarning()<<QString("查找失败");
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
    ui->tableView_2->setColumnWidth(1, 400);//设置固定宽度
    ui->tableView_2->setColumnWidth(2, 400);
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
    if (text == "首页") {
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


void MainWindow::loadLandscape(){
    // ui->treeView_r->clealmodel();
    /*** 加载场景文件****/
    ui->treeView_r->LoadScape(modelroot);
    // Returnroottable();

    modelroot->select();
    //this->ui->stackedWidget->setCurrentIndex(1);
    idlist_r.clear();
    idlist_b.clear();
    auto&&it=ui->treeView_r->IDlist_red.begin();
    while(it!=ui->treeView_r->IDlist_red.end()){

        if(it.key()!=-1){
            idlist_r.append(it.key());
        }

        it++;
    }
    it=ui->treeView_r->IDlist_blue.begin();
    while(it!=ui->treeView_r->IDlist_blue.end()){
        if(it.key()!=-1){
            idlist_b.append(it.key());
        }
        it++;
    }

    ui->treeView_r->expandAll();
    ui->treeView->expandAll();
    Pushbuttonable(1);
    if(idlist_b.isEmpty()&&idlist_r.isEmpty()){
        QMessageBox::warning(this,"提示","数据库中无匹配该场景的规则");
        qWarning("数据库中没有匹配的规则");
    }
    else {
        loadLandscape_D();
    }
}
void MainWindow::changeTable_item(QModelIndex a){
    model_display.clear();
    myviewmodel->Tablehead.clear();
    QStandardItem*slt_item= ui->treeView_r->model->itemFromIndex(a);
    QList<QStandardItem*>list_item;
    QList<int>SelectID;
    list_item.append(slt_item);
    while (!list_item.isEmpty()){
        if(list_item.front()->rowCount() <= 0){
            SelectID.append(ui->treeView_r->item_table[list_item.front()]);
        }
        else{
            for(int i=0;i<list_item.front()->rowCount();i++){
                list_item.push_back(list_item.front()->child(i));
            }
        }
        list_item.pop_front();
    }
    while (!SelectID.isEmpty()) {
        for(int i=0;i<modelin.count();i++){
            if(modelin.at(i)->tableName()==ui->treeView_r->item_tablename[SelectID.back()]){
                if(!model_display.contains(modelin.at(i))){
                    model_display.append(modelin.at(i));
                    myviewmodel->Tablehead.append(ui->treeView_r->headnamelist[SelectID.back()]);
                }
            }
        }
        SelectID.pop_back();
    }
    myviewmodel->setview(model_display);
}
void MainWindow::loadLandscape_D(){
    m_node_red.clear();
    m_node_blue.clear();
    m_link.clear();
    T_item.clear();
    m_scene->clearitems();
    modelin.clear();
    model_display.clear();
    myviewmodel->Tablehead.clear();
    cupos=120;
    modelroot->setTable(modelroot->tableName());
    modelroot->select();
    QString findcondition=nullptr;
    if(!idlist_r.isEmpty()){
        for(int k=0;k<idlist_r.count();k++){
            findcondition=findcondition+"("+"idtest1"+"="+QString::number(idlist_r.at(k))+")";
            if(k<idlist_r.count()-1){
                findcondition=findcondition+"OR";
            }
        }
        modelroot->setFilter(findcondition);
        modelroot->select();
        this->ruledsp(1);
        addtable(m_node_red.first(),1);
        addtable(m_node_red.first(),0);
    }
    modelroot->setTable(modelroot->tableName());
    modelroot->select();

    if(!idlist_b.isEmpty()){
        QString findconditionb=nullptr;
        for(int k=0;k<idlist_b.count();k++){
            findconditionb=findconditionb+"("+"idtest1"+"="+QString::number(idlist_b.at(k))+")";
            if(k<idlist_b.count()-1){
                findconditionb=findconditionb+"OR";
            }
        }
        modelroot->setFilter(findconditionb);
        modelroot->select();
        this->ruledsp(0);
        addtable(m_node_blue.first(),1);
        addtable(m_node_blue.first(),0);
    }
    ui->r_return->setDisabled(0);
    myviewmodel->disflag=1;
    myviewmodel->setview(model_display);
    ui->rule_table->setModel(myviewmodel);
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
//bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    MSG* msg = (MSG*)message;
//    if(!this->pTitleBar->window()->isMaximized()){
//    switch(msg->message)
//        {
//        case WM_NCHITTEST:
//            int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
//            int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
//            if(xPos < boundaryWidth && yPos<boundaryWidth)                    //左上角
//                *result = HTTOPLEFT;
//            else if(xPos>=width()-boundaryWidth&&yPos<boundaryWidth)          //右上角
//                *result = HTTOPRIGHT;
//            else if(xPos<boundaryWidth&&yPos>=height()-boundaryWidth)         //左下角
//                *result = HTBOTTOMLEFT;
//            else if(xPos>=width()-boundaryWidth&&yPos>=height()-boundaryWidth)//右下角
//                *result = HTBOTTOMRIGHT;
//            else if(xPos < boundaryWidth)                                     //左边
//                *result =  HTLEFT;
//            else if(xPos>=width()-boundaryWidth)                              //右边
//                *result = HTRIGHT;
//            else if(yPos<boundaryWidth)                                       //上边
//                *result = HTTOP;
//            else if(yPos>=height()-boundaryWidth)                             //下边
//                *result = HTBOTTOM;
//            else              //其他部分不做处理，返回false，留给其他事件处理器处理
//               return false;
//            return true;
//        }
//    }
//        return false;         //此处返回false，留给其他事件处理器处理
//}
//void MainWindow::mousePressEvent(QMouseEvent *e)
//{
//    if(e->button()==Qt::LeftButton)
//        clickPos=e->pos();
//}

