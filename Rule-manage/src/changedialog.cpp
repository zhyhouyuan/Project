#include "changedialog.h"
#include "ui_changedialog.h"
#include "src/gcombox.h"
#include "checkdialog.h"
#include<QMessageBox>
changeDialog::changeDialog(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::changeDialog)
{
   ui->setupUi(this);
   setWindowTitle(tr("修改规则"));
   //datain_0 = new datain0(this);
   ifthenflag=0;
   init_fg=0;
   first_fg=0;
   ui->table_if->setColumnCount(6);
   ui->table_then->setColumnCount(6);
   //if_boxlist=new QList<Gcombox*> ;
   //ui->table_if->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
   ui->table_if->setContextMenuPolicy(Qt::CustomContextMenu);
   ui->table_then->setContextMenuPolicy(Qt::CustomContextMenu);
   ui->table_if->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
   ui->table_then->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

   QStringList strs = {"取反符号", "参数目录","变量名","符号关系","值","逻辑关系"};
   ui->table_if->setHorizontalHeaderLabels(strs);
   ui->table_then->setHorizontalHeaderLabels(strs);
  // ui->table_if->setHorizontalHeaderItem()
   connect(ui->push_ok,SIGNAL(clicked()),this,SLOT(send_ch()));
   //connect(ui->table_if,SIGNAL(itemClicked(QTableWidgetItem *)),this,SLOT(setvale_if(QTableWidgetItem *)));
   //connect(ui->table_then,SIGNAL(cellPressed(int,int)),this,SLOT(setvale_then(int,int)));
   connect(ui->table_if, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu(QPoint)));
   connect(ui->table_then, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onUpdateContextMenu2(QPoint)));
   //QObject::connect(datain_0,SIGNAL(send_flag(bool)),this,SLOT(setfhdata()));
   connect(ui->add,SIGNAL(clicked()),this,SLOT(add_if()));
   connect(ui->del,SIGNAL(clicked()),this,SLOT(del_if()));
   connect(ui->add_2,SIGNAL(clicked()),this,SLOT(add_then()));
   connect(ui->del_2,SIGNAL(clicked()),this,SLOT(del_then()));
   createActions();
   QRegExp regx("[0-9]+$");
   QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_w );
   ui->lineEdit_w->setValidator( validator );
   model = new QStandardItemModel();
   model_then=new QStandardItemModel();
}

changeDialog::~changeDialog()
{
   delete ui;
    delete  model;
    delete model_then;
}
void changeDialog::send_ch(){
   //if(ui->buttonBox->button(QDialogButtonBox::Ok)
   emit send_chflag(true);
}
void changeDialog::setRuleData(QSqlRecord* record0){
   if(!first_fg){
       first_fg=this->LoadClassifyFile();
   }
   if(first_fg){
  // model->clear();
   init_fg=0;
   this->ui->table_if->setRowCount(0);
   ui->table_if->clearContents();
   this->ui->table_then->setRowCount(0);
   ui->table_then->clearContents();
       RuleID=record0->value(0).toInt();
       QString data_if=record0->value(1).toString();
       QString data_then=record0->value(2).toString();
       QString data_w=record0->value(3).toString();
       QStringList list_if;
       QStringList list_if_andor;
       QStringList list_and = data_if.split("AND");
       for(int i=0;i<list_and.count();i++){
           QStringList list_or=list_and.at(i).split("OR");
           for(int j=0;j<list_or.count();j++){
                 list_if.append(list_or.at(j));
                 if(j+1<list_or.count()){
                     list_if_andor.append("OR");
                 }
           }
           if(i+1<list_and.count()){
               list_if_andor.append("AND");
           }
       }
       ui->table_if->setRowCount(list_if.count());
      // ui->table_if->setColumnCount(5);
       for(int i=0;i<list_if.count();i++){
           QStringList list0=this->StringSplit(list_if.at(i));

           QComboBox *comBox_not = new QComboBox(this);
           ui->table_if->setCellWidget(i,0,comBox_not);
           QStringList notlist;
           notlist<<"NOT"<<"";
           comBox_not->addItems(notlist);
           if(list0.at(0)=="NOT"){
               comBox_not->setCurrentIndex(0);
           }
           else{
               comBox_not->setCurrentIndex(1);
           }
           ui->table_if->setItem(i,1,new QTableWidgetItem(list0.at(1)));
           Gcombox *comBox = new Gcombox(this);
           comBox->setModel(model);
           comBox->setCText(list0.at(2));
          // qDebug()<<comBox->currentText();
           //comBox->setEditable(true);
           //comBox->setCurrentText(list0.at(1));
           //comBox->setEditText(list0.at(1));
           comBox->setflag(i,0);
           //this->set_value(i,0);
           //if_boxlist.append(comBox);
           //if_boxlist.append(comBox);
            ui->table_if->setCellWidget(i,2,comBox);
            QComboBox *comBox_1 = new QComboBox(this);

                   //comBox->addItem(data_if);
            ui->table_if->setCellWidget(i,3,comBox_1);
            QComboBox *comBox_2 = new QComboBox(this);

                   //comBox->addItem(data_if);
            ui->table_if->setCellWidget(i,4,comBox_2);
            this->set_value(i,0);
            //QString dw=model->data(comBox->myview->currentIndex().siblingAtColumn(2)).toString();
            comBox_1->setCurrentText(list0.at(3));
            comBox_2->setCurrentText(list0.at(4));


       }
       for(int i=0;i<list_if_andor.count();i++){
           QComboBox *comBox = new QComboBox(this);
           QStringList andor;
           andor<<"AND"<<"OR";
           comBox->addItems(andor);
           comBox->setCurrentIndex(comBox->findText(list_if_andor.at(i)));
           ui->table_if->setCellWidget(i,5,comBox);
       }
       QStringList list_then;
       QStringList list_then_andor;
       QStringList list_then_and = data_then.split("AND");
       for(int i=0;i<list_then_and.count();i++){
           QStringList list_then_or=list_then_and.at(i).split("OR");
           for(int j=0;j<list_then_or.count();j++){
                 list_then.append(list_then_or.at(j));
                 if(j+1<list_then_or.count()){
                     list_then_andor.append("OR");
                 }
           }
           if(i+1<list_then_and.count()){
               list_then_andor.append("AND");
           }
       }
       ui->table_then->setRowCount(list_then.count());
      // ui->table_then->setColumnCount(5);
       for(int i=0;i<list_then.count();i++){
           QStringList list0=this->StringSplit(list_then.at(i));

           QComboBox *comBox_not = new QComboBox(this);
           ui->table_then->setCellWidget(i,0,comBox_not);
           QStringList notlist;
           notlist<<"NOT"<<"";
           comBox_not->addItems(notlist);
           if(list0.at(0)=="NOT"){
               comBox_not->setCurrentIndex(0);
           }
           else{
               comBox_not->setCurrentIndex(1);
           }

           ui->table_then->setItem(i,1,new QTableWidgetItem(list0.at(1)));
           Gcombox *comBox = new Gcombox(this);
           comBox->setModel(model_then);
           comBox->setflag(i,1);
           comBox->setCText(list0.at(2));

           //comBox->addItem(list0.at(1));
            ui->table_then->setCellWidget(i,2,comBox);
            QComboBox *comBox_1 = new QComboBox(this);
            //comBox_1->setCurrentText(list0.at(2));
            //comBox->addItem(data_if);
            ui->table_then->setCellWidget(i,3,comBox_1);
            QComboBox *comBox_2 = new QComboBox(this);
            //comBox->addItem(data_if);
            ui->table_then->setCellWidget(i,4,comBox_2);
            this->set_value(i,1);
            comBox_1->setCurrentText(list0.at(3));
            comBox_2->setCurrentText(list0.at(4));
       }
       for(int i=0;i<list_then_andor.count();i++){
           QComboBox *comBox = new QComboBox(this);
           QStringList andor;
           andor<<"AND"<<"OR";
           comBox->addItems(andor);
           comBox->setCurrentIndex(comBox->findText(list_then_andor.at(i)));

           ui->table_then->setCellWidget(i,5,comBox);
       }
     ui->lineEdit_w->setText(data_w);
   }
}
bool changeDialog::getRuleData(QSqlRecord* record1){
   //QSqlField fildname;
  // bool chflag;
   int m=ui->table_if->rowCount();
   int n =ui->table_then->rowCount();
   for(int i=0;i<record1->count();i++){
       switch (i) {
          case 0:record1->setValue(0,RuleID);
          case 1 :{
                 QString dataout;
           //        item->setText(data_if);
                   for(int j=0;j<m;j++){
                       if(j+1<m){
                           QComboBox *combox_0;
                           Gcombox *combox_1;
                           QComboBox *combox_2;
                           QComboBox *combox_3;
                           QComboBox *combox_4;
                            QWidget *widget_0=ui->table_if->cellWidget(j,0);
                           QWidget *widget_1=ui->table_if->cellWidget(j,2);
                           QWidget *widget_2=ui->table_if->cellWidget(j,3);
                           QWidget *widget_3=ui->table_if->cellWidget(j,4);
                           QWidget *widget_4=ui->table_if->cellWidget(j,5);
                           combox_0=(QComboBox*)widget_0;
                           combox_1=(Gcombox*)widget_1;
                           combox_2=(QComboBox*)widget_2;
                           combox_3=(QComboBox*)widget_3;
                           combox_4=(QComboBox*)widget_4;
                           combox_1->setEditable(true);
                           QString dw=model->data(combox_1->myview->currentIndex().siblingAtColumn(2)).toString();
                           QString dataname=combox_1->currentText();
                           QString datatype=model->data(combox_1->myview->currentIndex().siblingAtColumn(1)).toString();
                           QString maxvalue=model->data(combox_1->myview->currentIndex().siblingAtColumn(3)).toString();
                           QString minvalue=model->data(combox_1->myview->currentIndex().siblingAtColumn(4)).toString();

                           QString invalue=combox_3->currentText().replace(dw,"");

                           bool checkflag=checkDialog::check_maxmin(datatype,maxvalue,minvalue,invalue);

                           if(checkflag){
                              // continue;
                           }
                           else{
                               QMessageBox::warning(this, tr("规则输入"),
                                                    tr("输入错误(错误位置：条件第%5行，数据名：%4，数据类型：%1，最大值：%2，最小值：%3)").arg(datatype).arg(maxvalue).arg(minvalue).arg(dataname).arg(j+1));
                               return 0;
                           }

                           dataout=dataout+combox_0->currentText()+ui->table_if->item(j,1)->text()+combox_1->currentText()+combox_2->currentText()+combox_3->currentText();
                           if(!combox_3->currentText().contains(dw)){
                                dataout=dataout+dw;
                           }
                           dataout=dataout+combox_4->currentText();
                       }
                       else{
                           QComboBox *combox_0;
                           Gcombox *combox_1;
                           QComboBox *combox_2;
                           QComboBox *combox_3;
                           QWidget *widget_0=ui->table_if->cellWidget(j,0);
                           QWidget *widget_1=ui->table_if->cellWidget(j,2);
                           QWidget *widget_2=ui->table_if->cellWidget(j,3);
                           QWidget *widget_3=ui->table_if->cellWidget(j,4);
                           combox_0=(QComboBox*)widget_0;
                           combox_1=(Gcombox*)widget_1;
                           combox_2=(QComboBox*)widget_2;
                           combox_3=(QComboBox*)widget_3;

                           QString dataname=combox_1->currentText();
                           QString datatype=model->data(combox_1->myview->currentIndex().siblingAtColumn(1)).toString();
                           QString maxvalue=model->data(combox_1->myview->currentIndex().siblingAtColumn(3)).toString();
                           QString minvalue=model->data(combox_1->myview->currentIndex().siblingAtColumn(4)).toString();


                           QString dw=model->data(combox_1->myview->currentIndex().siblingAtColumn(2)).toString();
                           QString invalue=combox_3->currentText().replace(dw,"");
                           bool checkflag=checkDialog::check_maxmin(datatype,maxvalue,minvalue,invalue);

                           if(checkflag){
                              // continue;
                           }
                           else{
                               QMessageBox::warning(this, tr("规则输入"),
                                                    tr("输入错误(错误位置：条件第%5行，数据名：%4，数据类型：%1，最大值：%2，最小值：%3)").arg(datatype).arg(maxvalue).arg(minvalue).arg(dataname).arg(j+1));
                               return 0;
                           }
                           dataout=dataout+combox_0->currentText()+ui->table_if->item(j,1)->text()+combox_1->currentText()+combox_2->currentText()+combox_3->currentText();
                           if(!combox_3->currentText().contains(dw)){
                                dataout=dataout+dw;
                           }
                       }


                       //QWidget *wid=ui->table_if->cellWidget(j,1);


                   }
                   record1->setValue(1,dataout);
         }
        case 2:{
                 QString dataout;
           //        item->setText(data_if);
                   for(int j=0;j<n;j++){
                       if(j+1<n){
                           QComboBox *combox_0;
                           Gcombox *combox_1;
                           QComboBox *combox_2;
                           QComboBox *combox_3;
                           QComboBox *combox_4;
                           QWidget *widget_0=ui->table_then->cellWidget(j,0);
                           QWidget *widget_1=ui->table_then->cellWidget(j,2);
                           QWidget *widget_2=ui->table_then->cellWidget(j,3);
                           QWidget *widget_3=ui->table_then->cellWidget(j,4);
                           QWidget *widget_4=ui->table_then->cellWidget(j,5);
                           combox_0=(QComboBox*)widget_0;
                           combox_1=(Gcombox*)widget_1;
                           combox_2=(QComboBox*)widget_2;
                           combox_3=(QComboBox*)widget_3;
                           combox_4=(QComboBox*)widget_4;
                           QString dw=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(2)).toString();
                           QString dataname=combox_1->currentText();
                           QString datatype=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(1)).toString();
                           QString maxvalue=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(3)).toString();
                           QString minvalue=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(4)).toString();
                           QString invalue=combox_3->currentText().replace(dw,"");

                           bool checkflag=checkDialog::check_maxmin(datatype,maxvalue,minvalue,invalue);

                           if(checkflag){
                              // continue;
                           }
                           else{
                               QMessageBox::warning(this, tr("规则输入"),
                                                    tr("输入错误(错误位置：条件第%5行，数据名：%4，数据类型：%1，最大值：%2，最小值：%3)").arg(datatype).arg(maxvalue).arg(minvalue).arg(dataname).arg(j+1));
                               return 0;
                           }
                           dataout=dataout+combox_0->currentText()+ui->table_then->item(j,1)->text()+combox_1->currentText()+combox_2->currentText()+combox_3->currentText();
                           if(!combox_3->currentText().contains(dw)){
                                dataout=dataout+dw;
                           }
                           dataout=dataout+combox_4->currentText();
                       }
                       else{
                           QComboBox *combox_0;
                           Gcombox *combox_1;
                           QComboBox *combox_2;
                           QComboBox *combox_3;
                           QWidget *widget_0=ui->table_then->cellWidget(j,0);
                           QWidget *widget_1=ui->table_then->cellWidget(j,2);
                           QWidget *widget_2=ui->table_then->cellWidget(j,3);
                           QWidget *widget_3=ui->table_then->cellWidget(j,4);
                           combox_0=(QComboBox*)widget_0;
                           combox_1=(Gcombox*)widget_1;
                           combox_2=(QComboBox*)widget_2;
                           combox_3=(QComboBox*)widget_3;
                           QString dataname=combox_1->currentText();
                           QString dw=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(2)).toString();
                           QString datatype=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(1)).toString();
                           QString maxvalue=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(3)).toString();
                           QString minvalue=model_then->data(combox_1->myview->currentIndex().siblingAtColumn(4)).toString();

                           QString invalue=combox_3->currentText().replace(dw,"");

                           bool checkflag=checkDialog::check_maxmin(datatype,maxvalue,minvalue,invalue);

                           if(checkflag){
                               //continue;
                           }
                           else{
                               QMessageBox::warning(this, tr("规则输入"),
                                                    tr("输入错误(错误位置：条件第%5行，数据名：%4，数据类型：%1，最大值：%2，最小值：%3)").arg(datatype).arg(maxvalue).arg(minvalue).arg(dataname).arg(j+1));
                               return 0;
                           }
                           dataout=dataout+combox_0->currentText()+ui->table_then->item(j,1)->text()+combox_1->currentText()+combox_2->currentText()+combox_3->currentText();
                           if(!combox_3->currentText().contains(dw)){
                                dataout=dataout+dw;
                           }

                       }
                   }
                   record1->setValue(2,dataout);
          }
       case 3: record1->setValue(3,ui->lineEdit_w->text());
       }
    }
   return 1;
}
QStringList changeDialog::StringSplit(QString datain0){
   QStringList listfuh;
   QString datain=datain0.simplified();
   listfuh<<">="<<"<="<<"="<<">"<<"<";
   QVector<int>pos;
   int pos_0=datain.indexOf(listfuh.at(0));
   int pos_1=datain.indexOf(listfuh.at(1));
   int pos_2=datain.indexOf(listfuh.at(2));
   pos.append(pos_0);
   pos.append(pos_1);
   pos.append(pos_2);
   int pos_3=datain.indexOf(listfuh.at(3));
   int pos_4=datain.indexOf(listfuh.at(4));
   pos.append(pos_3);
   pos.append(pos_4);

   for(int i=0;i<pos.count();i++){
       if(pos.at(i)<0){
           pos.operator[](i)=1000;
       }
   }
   auto min = std::min_element(std::begin(pos), std::end(pos));
        //直接赋值表示
  int smallest = *min;//最小值
        //最大值和最小值的位置的表示方式
  auto positionmin = std::distance(std::begin(pos),min);

  int posmin = positionmin;

  int ls=listfuh.at(posmin).count();//符号长度

   QString fuh=datain.mid(smallest,ls);//符号

   QString leftof=datain.left(smallest);//符合左边

   int lastpos=leftof.lastIndexOf(".");//前件

   QString last=leftof.right(leftof.count()-lastpos-1);//后

   QString NOTvalue;
   QString pre;
   if(datain.left(3)=="NOT"){
       NOTvalue="NOT";
       pre=leftof.right(datain.count()-3).left(lastpos+1);
   }
   else{
       NOTvalue="";
       pre=leftof.left(lastpos+1);
   }
   QString value=datain.right(datain.length()-smallest-ls);

   last=last.simplified();
   pre=pre.simplified();
   QStringList listout;

   listout<<NOTvalue<<pre<<last<<fuh<<value;

   return listout;
}
bool changeDialog::LoadClassifyFile(){
//   QString filePath = QFileDialog::getOpenFileName(this,tr("open file")," ", tr("XML files (*.xml);;ALL files (*.*)"));
//   //QDomDocument doc;
//  QList<QStandardItem*>aItemlist;
//   QFile file(filePath); //相对路径、绝对路径、资源路径都行
//   if(!file.open(QFile::ReadOnly))
//       return 0;
//   if(!doc.setContent(&file))
//   {
//       file.close();
//       return 0;
//   }
//   file.close();
   QDomElement root=doc.documentElement(); //返回根节点
   QDomNode node=root.firstChild().firstChild(); //获得第一个子节点
   while(!node.isNull())  //如果节点不空
   {
       if(node.isElement()) //如果节点是元素
       {
           QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
           if(e.tagName()=="实体信息"){
               for(int i=0;i<node.childNodes().count();i++){
                   QDomNode node1=node.childNodes().at(i);
                   QDomElement en=node1.toElement();
                   //QDomNodeList list=en.childNodes();
                   QStandardItem* item1 = new QStandardItem(en.tagName());
                   model->appendRow(item1);
                   additem(node1,item1);
               }
           }
           else if(e.tagName()=="交互信息"){
               QDomNode node1=node.firstChild();
               QDomElement en=node1.toElement();
               //QDomNodeList list=en.childNodes();
               QStandardItem* item1 = new QStandardItem(en.tagName());
               model_then->appendRow(item1);
               additem(node1,item1);
           }
       }
       node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
   }
   return 1;
}
void changeDialog::addfuhedataitem(QStandardItem *item){
    QStringList list0;
    list0<<"数据类型"<<"单位"<<"最大值"<<"最小值";
    QDomElement root=doc.documentElement(); //返回根节点
    QDomNode node=root.firstChild().firstChild(); //获得第一个子节点
    while(node.toElement().tagName()!="自定义数据类型"){
        node=node.nextSibling();
    }
    QDomNode node2=node.firstChild().nextSibling().firstChild();;//复合数据类型
    while(!node2.isNull())  //如果节点不空
    {
        if(node2.isElement()) //如果节点是元素
        {
            QDomElement e=node2.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
            if(e.attribute("中文名称")==item->text()){
                QDomNodeList list=e.childNodes();
                for(int i=0;i<list.count();i++){
                    QList<QStandardItem*>aItemlist0;
                     QStandardItem*item2 = new QStandardItem(list.at(i).toElement().attribute("中文名称"));
                     aItemlist0<<item2;
                     for(int ii=0;ii<list0.count();ii++)
                       {
                           QStandardItem* aItem=new QStandardItem(list.at(i).toElement().attribute(list0.at(ii))); //创建Item
                           aItemlist0<<aItem;   //添加到容器
                       }
                     item->appendRow(aItemlist0);
                }

            }
            break;
        }
        break;
        node2=node2.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }
}
void changeDialog::additem(QDomNode itemnode,QStandardItem *item0){
   QStringList list00;
   list00<<"数据类型"<<"单位"<<"最大值"<<"最小值";
   if(itemnode.isElement()) //如果节点是元素
   {
       QDomNodeList list=itemnode.childNodes();
       for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
       {
           QDomNode n=list.at(i);
           if(n.isElement()){
                QDomElement en=n.toElement();
                QStandardItem* item2;
               //QList<QStandardItem*> firstItems;
                if(en.tagName()=="状态变量"||en.tagName()=="参数"){
                    QList<QStandardItem*>aItemlist0;
                     item2 = new QStandardItem(en.attribute("中文名称"));
                     aItemlist0<<item2;
                     for(int ii=0;ii<list00.count();ii++)
                       {
                           QStandardItem* aItem=new QStandardItem(en.attribute(list00.at(ii))); //创建Item
                           aItemlist0<<aItem;   //添加到容器
                       }
                     item0->appendRow(aItemlist0);
                     if(aItemlist0.at(1)->text()!="int"&&aItemlist0.at(1)->text()!="double"&&aItemlist0.at(1)->text()!="string"){
                         this->addfuhedataitem(item2);
                     }
                }
                else if(en.tagName()=="本地实体"||en.tagName()=="异地实体"||en.tagName()=="事件"){
                   item2 = new QStandardItem(en.attribute("中文名称"));
                   item0->appendRow(item2);
                   additem(n,item2);
                }
                else{
                    additem(n,item0);
                }
           }
       }
   }
}


void changeDialog::set_value(int i, bool flag){
   Gcombox *combox_1;
   QComboBox *combox_2;
   QComboBox *combox_3;
   QTableWidgetItem *item;
   QWidget *widget_0,*widget_2,*widget_3;
   QStandardItemModel *model0;
   this->ifthenflag=flag;
   if(flag==0){
        widget_0=ui->table_if->cellWidget(i,2);
       combox_1=(Gcombox*)widget_0;
        widget_2=ui->table_if->cellWidget(i,3);
       combox_2=(QComboBox*)widget_2;
       widget_3=ui->table_if->cellWidget(i,4);
       combox_3=(QComboBox*)widget_3;
       item=ui->table_if->item(i,1);
       model0=model;
   }
   else{
       widget_0=ui->table_then->cellWidget(i,2);
       combox_1=(Gcombox*)widget_0;
       widget_2=ui->table_then->cellWidget(i,3);
       combox_2=(QComboBox*)widget_2;
       widget_3=ui->table_then->cellWidget(i,4);
       combox_3=(QComboBox*)widget_3;
       item=ui->table_then->item(i,1);
       model0=model_then;
   }
   combox_2->clear();
   combox_2->addItem("=");
   combox_3->clear();
   combox_3->clearEditText();
   QDomElement root=doc.documentElement(); //返回根节点
   QString text1=combox_1->getParent();
   item->setText(text1);
   QString name=combox_1->currentText();
   QString datatype=model0->data(combox_1->myview->currentIndex().siblingAtColumn(1)).toString();
   if(datatype=="string"||datatype=="double"||datatype=="int"){
       combox_2->addItem("<");
       combox_2->addItem(">");
       combox_2->addItem(">=");
       combox_2->addItem("=");
       combox_2->addItem("<=");
       combox_3->setEditable(true);
   }
   else{
       combox_3->setEditable(false);
       QDomNode node=root.firstChild().firstChild(); //获得第一个子节点
       while(node.toElement().tagName()!="自定义数据类型"){
           node=node.nextSibling();
       }
       QDomNode node1=node.firstChild().firstChild();//枚举数据类型
       while(!node1.isNull())  //如果节点不空
       {
           if(node1.isElement()) //如果节点是元素
           {
               QDomElement e=node1.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
               if(e.attribute("中文名称")==name){
                   QDomNodeList list=e.childNodes();
                   for(int i=0;i<list.count();i++){
                       combox_3->addItem(list.at(i).toElement().attribute("中文名称"));
                   }
               }
           }
           node1=node1.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
       }
//       QDomNode node2=node.firstChild().nextSibling().firstChild();//复合数据类型
//       while(!node2.isNull())  //如果节点不空
//       {
//           if(node2.isElement()) //如果节点是元素
//           {

//               QDomElement e=node2.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
//               if(e.attribute("中文名称")==name){
//                   QDomNodeList list=e.childNodes();
//                   if(init_fg==0){
//                       combox_3->setEditable(true);
//                   }
//                   else{
//                       datain_0->show();
//                       datain_0->settable(e);
//                   }
//                   //ui->comboBox_3->setCurrentText(datain_0->getalltext());
//               }
//           }
//          node2=node2.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
//       }
   }
}
void changeDialog::createActions()
{
   m_topMenu = new QMenu(this);
   m_actAdd = new QAction("添加(Ctrl+N)", this);
   m_actAdd->setShortcut(tr("Ctrl+N"));
   connect(m_actAdd, SIGNAL(triggered(bool)), this, SLOT(add_if()));
   m_topMenu->addAction(m_actAdd);
   m_actDel = new QAction("删除(Del)", this);
   m_actDel->setShortcut(tr("Del"));
   connect(m_actDel, SIGNAL(triggered(bool)), this, SLOT(del_if()));
   m_topMenu->addAction(m_actDel);
   QList<QAction *> acts = m_topMenu->actions();
   for (int i = 0; i < acts.count(); i++) {
       QAction *act = acts.at(i);
       if (act) {
           ui->table_if->addAction(act);
       }
   }
   m_topMenu_2 = new QMenu(this);
   m_actAdd_2 = new QAction("添加(Ctrl+N)", this);
   m_actAdd_2->setShortcut(tr("Ctrl+N"));
   connect(m_actAdd_2, SIGNAL(triggered(bool)), this, SLOT(add_then()));
   m_topMenu_2->addAction(m_actAdd_2);
   m_actDel_2 = new QAction("删除(Del)", this);
   m_actDel_2->setShortcut(tr("Del"));
   connect(m_actDel_2, SIGNAL(triggered(bool)), this, SLOT(del_then()));
   m_topMenu_2->addAction(m_actDel_2);
   QList<QAction *> acts2 = m_topMenu_2->actions();
   for (int i = 0; i < acts2.count(); i++) {
       QAction *act = acts2.at(i);
       if (act) {
           ui->table_then->addAction(act);
       }
   }
}
void changeDialog::onUpdateContextMenu(QPoint pos)
{
   QModelIndex index = ui->table_if->indexAt(pos);
   if (index.isValid())
   {
   m_topMenu->exec(QCursor::pos()); //
   }
}
void changeDialog::onUpdateContextMenu2(QPoint pos)
{
   QModelIndex index = ui->table_then->indexAt(pos);
   if (index.isValid())
   {
   m_topMenu_2->exec(QCursor::pos()); //
   }
}
void changeDialog::add_if(){
   int row = ui->table_if->rowCount();
   ui->table_if->insertRow(row);
   QComboBox *comBox_0 = new QComboBox(this);

          comBox_0->addItem("");
          comBox_0->addItem("NOT");
   ui->table_if->setCellWidget(row,0,comBox_0);


   ui->table_if->setItem(row,1,new QTableWidgetItem());
   Gcombox *comBox = new Gcombox(this);
   comBox->setModel(model);
   comBox->setflag(row,0);
    ui->table_if->setCellWidget(row,2,comBox);
    QComboBox *comBox_1 = new QComboBox(this);
           comBox_1->addItem("=");
    ui->table_if->setCellWidget(row,3,comBox_1);
    QComboBox *comBox_2 = new QComboBox(this);
           //comBox->addItem(data_if);
    ui->table_if->setCellWidget(row,4,comBox_2);
    QComboBox *comBox_3 = new QComboBox(this);
          comBox_3->addItem("AND");
          comBox_3->addItem("OR");
    ui->table_if->setCellWidget(row-1,5,comBox_3);
    connect(comBox,SIGNAL(send_flag(int,bool)),this,SLOT(set_value(int ,bool)));

}
void changeDialog::del_if(){
   int row = ui->table_if->rowCount();
   //ui->table_if->insertRow(row);
   ui->table_if->removeRow(row-1);
   //ui->table_if->cellWidget(row-1)
   if(row>=1){
       ui->table_if->removeCellWidget(row-2,5);
   }
}
void changeDialog::add_then(){
   int row = ui->table_then->rowCount();
   ui->table_then->insertRow(row);
   QComboBox *comBox_0 = new QComboBox(this);

          comBox_0->addItem("");
          comBox_0->addItem("NOT");
   ui->table_then->setCellWidget(row,0,comBox_0);

   ui->table_then->setItem(row,1,new QTableWidgetItem());
   Gcombox *comBox = new Gcombox(this);
   comBox->setModel(model_then);
   comBox->setflag(row,1);
    ui->table_then->setCellWidget(row,2,comBox);
    QComboBox *comBox_1 = new QComboBox(this);
           comBox_1->addItem("=");
    ui->table_then->setCellWidget(row,3,comBox_1);
    QComboBox *comBox_2 = new QComboBox(this);
           //comBox->addItem(data_if);
    ui->table_then->setCellWidget(row,4,comBox_2);
    QComboBox *comBox_3 = new QComboBox(this);
          comBox_3->addItem("AND");
          comBox_3->addItem("OR");
    ui->table_then->setCellWidget(row-1,5,comBox_3);
    connect(comBox,SIGNAL(send_flag(int,bool)),this,SLOT(set_value(int ,bool )));

}
void changeDialog::del_then(){
   int row = ui->table_then->rowCount();
   //ui->table_if->insertRow(row);
   ui->table_then->removeRow(row-1);
   //ui->table_if->cellWidget(row-1)
   if(row>=1){
       ui->table_then->removeCellWidget(row-2,5);
   }
}
//void changeDialog::setfhdata(){
//   if(!datain_0->getalltext().isNull()){
//       QWidget *widget;
//       if(ifthenflag==0){
//           int row =ui->table_if->currentRow();
//           widget=ui->table_if->cellWidget(row,4);
//         }
//       else{
//           int row =ui->table_then->currentRow();
//           widget=ui->table_then->cellWidget(row,4);
//       }
//       QComboBox* combox_3=(QComboBox*)widget;
//       combox_3->setEditable(true);
//       combox_3->setCurrentText(datain_0->getalltext());
//       datain_0->close();
//   }

//}
void changeDialog::combox_rn(){
   init_fg=1;
   for(int i=0;i<ui->table_if->rowCount();i++){
       Gcombox *combox_1;
       QWidget *widget_0=ui->table_if->cellWidget(i,2);
       combox_1=(Gcombox*)widget_0;
       connect(combox_1,SIGNAL(send_flag(int,bool)),this,SLOT(set_value(int,bool)));
   }
   for(int i=0;i<ui->table_then->rowCount();i++){
       Gcombox *combox_2;
       QWidget *widget_0=ui->table_then->cellWidget(i,2);
       combox_2=(Gcombox*)widget_0;
       connect(combox_2,SIGNAL(send_flag(int,bool)),this,SLOT(set_value(int ,bool )));
   }
}
