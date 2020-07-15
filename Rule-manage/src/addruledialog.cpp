 #include "addruledialog.h"
#include "ui_addruledialog.h"
#include<QFile>
#include<QFileDialog>
#include<QTreeView>
#include<QtDebug>
#include<QListView>
#include<QMessageBox>
#include"checkdialog.h"
addruleDialog::addruleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addruleDialog)
{
    ui->setupUi(this);
    //datain_0=new datain0(this);
    setWindowTitle(tr("添加规则"));
    model = new QStandardItemModel();
    model_then= new QStandardItemModel();
    //modelin =new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList("选择"));
    //ui->treeWidget->addTopLevelItem("3");
    //ui->comboBox->setModel(ui->treeWidget->model());
    ui->pp->setText("Read XML");
    //connect(ui->pp,SIGNAL(clicked()),this,SLOT(LoadClassifyFile()));
    connect(ui->addcondition,SIGNAL(clicked()),this,SLOT(addcondition()));
    connect(ui->addresult,SIGNAL(clicked()),this,SLOT(addresult()));
    connect(ui->NOT_1,SIGNAL(clicked()),this,SLOT(add_NOT1()));
    connect(ui->NOT_2,SIGNAL(clicked()),this,SLOT(add_NOT2()));
    connect(ui->AND_1,SIGNAL(clicked()),this,SLOT(add_AND1()));
    connect(ui->AND_2,SIGNAL(clicked()),this,SLOT(add_AND2()));
    connect(ui->OR_1,SIGNAL(clicked()),this,SLOT(add_OR1()));
    connect(ui->OR_2,SIGNAL(clicked()),this,SLOT(add_OR2()));
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(send()));
    connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(setLine_if()));
    connect(ui->comboBox_4,SIGNAL(currentTextChanged(QString)),this,SLOT(setLine_then()));
   // QObject::connect(datain_0,SIGNAL(send_flag(bool)),this,SLOT(setcbxdata()));
    connect(ui->kh_L0,SIGNAL(clicked()),this,SLOT(addkh_L0()));
    connect(ui->kh_R0,SIGNAL(clicked()),this,SLOT(addkh_R0()));
    connect(ui->kh_L1,SIGNAL(clicked()),this,SLOT(addkh_L1()));
    connect(ui->kh_R1,SIGNAL(clicked()),this,SLOT(addkh_R1()));
    //connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(this.close()));
    //treeView->setModel(model);
    //treeView2->setModel(model);
    ui->comboBox_4->setModel(model_then);
    //ui->comboBox_4->setView(treeView);
    ui->comboBox->setModel(model);
    //ui->comboBox->setView(treeView2);
    //ui->textEdit->setDisabled(1);
    //ui->textEdit->setReadOnly(1);
    //ui->textEdit_2->setReadOnly(1);
    ui->textEdit->setFocusPolicy(Qt::NoFocus );
    ui->textEdit_2->setFocusPolicy(Qt::NoFocus );
    ui->textEdit->setFontFamily("Consolas");
    ui->textEdit_2->setFontFamily("Consolas");
    ui->comboBox_3->setEditable(true);
    ui->comboBox_6->setEditable(true);
    ui->lineEdit_if->setDisabled(1);
    ui->lineEdit_then->setDisabled(1);
    //ui->comboBox_3->setCurrentText("aaa");
    //treeView->show();
    //this->model->
    //ui->comboBox_3->setEnabled(0);
   // LoadClassifyFile();
}
addruleDialog::~addruleDialog()
{
    delete ui;
    delete model;
    delete model_then;
}
void addruleDialog::LoadClassifyFile(){
    model->clear();
    model_then->clear();
//    QString filePath = QFileDialog::getOpenFileName(this,tr("open file")," ", tr("XML files (*.xml);;ALL files (*.*)"));
//    //QDomDocument doc;
//    qDebug()<<filePath;
//    QList<QStandardItem*>aItemlist;
//    QFile file(filePath); //相对路径、绝对路径、资源路径都行
//    if(!file.open(QFile::ReadOnly))
//        return;
//    if(!doc.setContent(&file))
//    {
//        file.close();
//        return;
//    }
//    file.close();
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
    //                for(int i=0;i<3;i++) //不包含最后1列
    //                  {
    //                     QStandardItem* aItem=new QStandardItem("这是什么"+QString::number(i)); //创建Item
    //                     aItemlist<<aItem;   //添加到容器
    //                  }
                    //QStandardItem *item2=new QStandardItem(e.tagName());
                    //item1->appendColumn(aItemlist);
                    //item1->appendRow(aItemlist);
                    //modelin->appendRow(item1);
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
            //item1->setData(v, Qt::UserRole -1);
        }
        node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }
    this->ui->comboBox->setCText("名称");
    this->ui->comboBox_4->setCText("接收ID");
    this->setLine_if();
    this->setLine_then();
}
void addruleDialog::additem(QDomNode itemnode,QStandardItem *item0){
    QStringList list0;
    list0<<"数据类型"<<"单位"<<"最大值"<<"最小值";
    if(itemnode.isElement()) //如果节点是元素
    {
       //QDomElement e=itemnode.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
        QDomNodeList list=itemnode.childNodes();
        for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
        {
            QDomNode n=list.at(i);
            if(n.isElement()){
                 QDomElement en=n.toElement();
                 QStandardItem* item2;
                 if(en.tagName()=="状态变量"||en.tagName()=="参数"){
                     QList<QStandardItem*>aItemlist0;
                      item2 = new QStandardItem(en.attribute("中文名称"));
                      aItemlist0<<item2;
                      for(int i=0;i<list0.count();i++)
                       {
                            QStandardItem* aItem=new QStandardItem(en.attribute(list0.at(i))); //创建Item
                            aItemlist0<<aItem;   //添加到容器
                       }
                      item0->appendRow(aItemlist0);
                      this->addfuhedataitem(item2);

                 }
                 else if(en.tagName()=="本地实体"||en.tagName()=="异地实体"||en.tagName()=="事件"){
                    item2 = new QStandardItem(en.attribute("中文名称"));
                    item0->appendRow(item2);
                    additem(n,item2);
                 }
                 else{
                     additem(n,item0);
                 }

                //if(en.childNodes().count()!=1){
//                    bool disable =true;
//                    QStandardItem* item = model->item(1);
//                    item2->setFlags(disable ? item->flags() & ~(Qt::ItemIsSelectable|Qt::ItemIsEnabled)
//                                                   : Qt::ItemIsSelectable|Qt::ItemIsEnabled);
//                            // visually disable by greying out - works only if combobox has been painted already and palette returns the wanted color
//                    item2->setData(disable ? ui->comboBox->palette().color(QPalette::Disabled, QPalette::Text)
//                                                  : QVariant(), // clear item data in order to use default color
//                                          Qt::TextColorRole);                //QVariant v(0);               // item2->setData(v, Qt::UserRole - 1);
//}
            }
        }
    }
}
void addruleDialog::addfuhedataitem(QStandardItem *item){
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
                     for(int i=0;i<list0.count();i++)
                       {
                           QStandardItem* aItem=new QStandardItem(list.at(i).toElement().attribute(list0.at(i))); //创建Item
                           aItemlist0<<aItem;   //添加到容器
                       }
                     item->appendRow(aItemlist0);
                }
                //ui->comboBox_3->setCurrentText(datain_0->getalltext());
            }
            break;
        }
        break;
        node2=node2.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }
}
void addruleDialog::cleartext(){
    ui->textEdit->clear();
    ui->textEdit_2->clear();
}

void addruleDialog::addcondition(){
    QString  danw=model->data(ui->comboBox->myview->currentIndex().siblingAtColumn(2)).toString();
    QString condition=ui->lineEdit_if->text()+ui->comboBox->currentText()+ui->comboBox_2->currentText()+ui->comboBox_3->currentText()+danw;
    this->appendMessage(condition,0);
    //ui->textEdit->append(condition);
    //i->AND_1->setEnabled(1);
    //ui->OR_1->setEnabled(1);
    //this->treeView->show();
}
void addruleDialog::addresult(){
    QString  danw=model->data(ui->comboBox_4->myview->currentIndex().siblingAtColumn(2)).toString();
    QString result=ui->lineEdit_then->text()+ui->comboBox_4->currentText()+ui->comboBox_5->currentText()+ui->comboBox_6->currentText()+danw;
    this->appendMessage(result,1);
    ui->AND_2->setEnabled(1);
    ui->OR_2->setEnabled(1);
}
//void addruleDialog::add_ANDOR(bool flag,bool CoRe){
//    if(flag==0&&CoRe==0){
//        ui->textEdit->append("AND");
//    }
//    if(flag==1&&CoRe==0){
//        ui->textEdit->append("OR");
//    }
//    if(flag==0&&CoRe==1){
//        ui->textEdit_2->append("AND");
//    }
//    if(flag==1&&CoRe==1){
//        ui->textEdit_2->append("OR");
//    }
//}
void addruleDialog::add_AND1(){
      //ui->textEdit->append("AND");
      this->appendMessage("AND",0);
}
void addruleDialog::add_AND2(){
      //ui->textEdit_2->append("AND");
    this->appendMessage("AND",1);
}
void addruleDialog::add_NOT1(){
      //ui->textEdit->append("AND");
      this->appendMessage("NOT",0);
}
void addruleDialog::add_NOT2(){
      //ui->textEdit_2->append("AND");
    this->appendMessage("NOT",1);
}
void addruleDialog::add_OR1(){
      this->appendMessage("OR",0);
}
void addruleDialog::add_OR2(){
      this->appendMessage("OR",1);
}
void addruleDialog::addkh_L0(){
     // ui->textEdit->insertPlainText("(");
      this->appendMessage("(",0);
}
void addruleDialog::addkh_L1(){
      //ui->textEdit_2->insertPlainText("(");
      this->appendMessage("(",1);
}
void addruleDialog::addkh_R0(){
      //ui->textEdit->insertPlainText(")");
      this->appendMessage(")",0);
}
void addruleDialog::addkh_R1(){
    //ui->textEdit_2->insertHtml("<p color='#0F0'>(</p>");
    //ui->textEdit_2->insertPlainText(")");
    this->appendMessage(")",1);
}
//void addruleDialog::redo_0(){
//    //ui->textEdit_2->insertHtml("<p color='#0F0'>(</p>");
//    ui->textEdit->redo();

//    //this->appendMessage(")",1);
//}
//void addruleDialog::redo_1(){
//    ui->textEdit_2->redo();
//}
//void addruleDialog::undo_0(){
//    ui->textEdit->moveCursor(QTextCursor::End);
//    ui->textEdit->textCursor().deletePreviousChar();
//}
//void addruleDialog::undo_1(){
//    ui->textEdit_2->moveCursor(QTextCursor::End);
//    ui->textEdit_2->textCursor().deletePreviousChar();
//}
QString addruleDialog::getIf(){
    QString str = this->qukuohao(this->ui->textEdit->toPlainText().simplified());//去换行符
    return str;
}
QString addruleDialog::getThen(){
    QString str_2 =this->qukuohao(this->ui->textEdit_2->toPlainText().simplified());
    return str_2;
}
QString addruleDialog::getWeight(){
    return this->ui->spinBox_w->text();
}
void addruleDialog::send(){
    //if(ui->buttonBox->button(QDialogButtonBox::Ok)
    emit sendflag(true);
}
void addruleDialog::setLine_if(){
    //ui->comboBox_2
   ifthenflag=0;
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("=");
    ui->comboBox_3->clear();
    ui->comboBox_3->clearEditText();
    QDomElement root=doc.documentElement(); //返回根节点
    QString text1=ui->comboBox->getParent();
    ui->lineEdit_if->setText(text1);
    QString name=ui->comboBox->currentText();
    QString datatype=model->data(ui->comboBox->myview->currentIndex().siblingAtColumn(1)).toString();
    if(datatype=="string"||datatype=="double"||datatype=="int"){
        ui->comboBox_2->addItem("<");
        ui->comboBox_2->addItem(">");
        ui->comboBox_3->setEditable(true);
    }
    else{
        //ui->comboBox_2->addItem("!=");
        ui->comboBox_3->setEditable(false);
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
                        ui->comboBox_3->addItem(list.at(i).toElement().attribute("中文名称"));
                    }
                }
            }
            node1=node1.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
        }
//        QDomNode node2=node.firstChild().nextSibling().firstChild();//复合数据类型
//        while(!node2.isNull())  //如果节点不空
//        {
//            if(node2.isElement()) //如果节点是元素
//            {
//                QDomElement e=node2.toElement(); //转换为元素，注意元素和节点是两个数据结构
//                if(e.attribute("中文名称")==name){

//                    QDomNodeList list=e.childNodes();
//                   // datain_0->show();
//                   // datain_0->settable(e);
//                    //ui->comboBox_3->setCurrentText(datain_0->getalltext());
//                }
//            }
//           node2=node2.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
//        }
    }
}
void addruleDialog::setLine_then(){
    ifthenflag=1;
    QString text1=ui->comboBox_4->getParent();
    ui->lineEdit_then->setText(text1);
    ui->comboBox_6->clear();
    ui->comboBox_6->clearEditText();
    QDomElement root=doc.documentElement(); //返回根节点
    QString name=ui->comboBox_4->currentText();
    QString datatype=model_then->data(ui->comboBox_4->myview->currentIndex().siblingAtColumn(1)).toString();
    if(datatype=="string"||datatype=="double"||datatype=="int"){
        ui->comboBox_5->addItem("<");
        ui->comboBox_5->addItem(">");
        ui->comboBox_6->setEditable(true);
    }
    else{
        ui->comboBox_6->setEditable(false);
        QDomNode node=root.firstChild().firstChild(); //获得第一个子节点
        while(node.toElement().tagName()!="自定义数据类型"){
            node=node.nextSibling();
        }
        QDomNode node1=node.firstChild().firstChild();
        while(!node1.isNull())  //如果节点不空
        {
            if(node1.isElement()) //如果节点是元素
            {
                QDomElement e=node1.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
                if(e.attribute("中文名称")==name){
                    QDomNodeList list=e.childNodes();
                    for(int i=0;i<list.count();i++){
                    ui->comboBox_6->addItem(list.at(i).toElement().attribute("中文名称"));
                    }
                }
            }
        node1=node1.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
        }
    }
//    QDomNode node2=node.firstChild().nextSibling().firstChild();//复合数据类型
//    while(!node2.isNull())  //如果节点不空
//    {
//        if(node2.isElement()) //如果节点是元素
//        {
//            QDomElement e=node2.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
//            if(e.attribute("中文名称")==name){
//                QDomNodeList list=e.childNodes();
//                datain_0->show();
//                datain_0->settable(e);
//                //ui->comboBox_3->setCurrentText(datain_0->getalltext());
//            }
//        }
//        node2=node2.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
//    }
}
//void addruleDialog::setcbxdata(){
//    if(!datain_0->getalltext().isNull()){
//        if(ifthenflag==0){
//            ui->comboBox_3->setEditable(true);
//            ui->comboBox_3->setCurrentText(datain_0->getalltext());
//        }
//        else{
//            ui->comboBox_6->setEditable(true);
//            ui->comboBox_6->setCurrentText(datain_0->getalltext());
//        }
//        datain_0->close();
//    }
//}
void addruleDialog::appendMessage(const QString &message,int flag)
{
    if(flag==0){
        QString datatype=model->data(ui->comboBox->myview->currentIndex().siblingAtColumn(1)).toString();
        QString maxvalue=model->data(ui->comboBox->myview->currentIndex().siblingAtColumn(3)).toString();
        QString minvalue=model->data(ui->comboBox->myview->currentIndex().siblingAtColumn(4)).toString();
        QString invalue=ui->comboBox_3->currentText();
        bool checkflag=checkDialog::check_maxmin(datatype,maxvalue,minvalue,invalue);
        if(checkflag){
            //ui->textEdit->moveCursor(QTextCursor::EndOfLine);
            ui->textEdit->insertPlainText(message);
//            ui->textEdit->moveCursor(QTextCursor::End);
//            ui->textEdit->textCursor().deletePreviousChar();
        }
        else{
            QMessageBox::warning(this, tr("规则输入"),
                                 tr("输入值错误(数据类型：%1，最大值：%2，最小值：%3)").arg(datatype).arg(maxvalue).arg(minvalue));
        }
    }
    else{
        QString datatype=model->data(ui->comboBox_4->myview->currentIndex().siblingAtColumn(1)).toString();
        QString maxvalue=model->data(ui->comboBox_4->myview->currentIndex().siblingAtColumn(3)).toString();
        QString minvalue=model->data(ui->comboBox_4->myview->currentIndex().siblingAtColumn(4)).toString();
        QString invalue=ui->comboBox_6->currentData().toString();
        bool checkflag=checkDialog::check_maxmin(datatype,maxvalue,minvalue,invalue);
        if(checkflag){
            //ui->textEdit_2->moveCursor(QTextCursor::EndOfLine);
            ui->textEdit_2->insertPlainText(message);
        }
        else{
            QMessageBox::warning(this, tr("规则输入"),
                                 tr("输入值错误(数据类型：%1，最大值：%2，最小值：%3").arg(datatype).arg(maxvalue).arg(minvalue));
        }
    }
}
QString addruleDialog::qukuohao(QString text){
    int index_1=text.indexOf(")");
    QString outtext=text;
    if(index_1!=-1){
        QString text0=text.left(index_1);
        int index_0=text0.lastIndexOf("(");
        QString intext=text0.right(text0.count()-index_0-1);
        QString Rtext=text.right(text.count()-index_1-1);
        QString Ltext=text0.left(index_0);
        QString Ltext0=Ltext.right(Ltext.count()-Ltext.indexOf("(")-1);
        int pos1,pos2;
        pos1=Ltext.count()-Ltext0.count();
        QString Rtext0;
        int findR=1;
        for(int j=0;j<Rtext.count();j++){
            if(Rtext.at(j)==")"){
                findR=findR-1;
            }
            else if(Rtext.at(j)=="("){
                findR=findR+1;
            }
            if(findR==0){
                Rtext0=Rtext.left(j);
                //pos2=index_1+j;
                break;
            }
            else{
                Rtext0=Rtext;
            }
        }
        pos2=Ltext0.count()+intext.count()+Rtext0.count()+2;
        QString outtext0,leftpre,rightpre;
        QString outtext1;
        if(Ltext0.count()>=3){
            if(Ltext0.back()=="T"&&Ltext0.at(Ltext0.count()-2)=="O"&&Ltext0.at(Ltext0.count()-3)=="N"){
                QString out="("+qufan(intext)+")";
                outtext.replace(Ltext.count()-3,3+intext.count()+2,out);
                return qukuohao(outtext);
              }
            if(Ltext0.back()=="D"&&Ltext0.at(Ltext0.count()-2)=="N"&&Ltext0.at(Ltext0.count()-3)=="A"){
                QStringList inlist0=intext.split("OR");
                QStringList Ltextlist0=Ltext0.split("OR");
                for(int i=0;i<inlist0.count();i++){
                   QString Ltext_1=Ltextlist0.back().left(Ltextlist0.back().count()-3);
                   if(Ltext_1==inlist0.at(i)){
                       if(i<inlist0.count()-1){
                           outtext0=outtext0+inlist0.at(i)+"OR";
                       }
                       else{
                           outtext0=outtext0+inlist0.at(i);
                       }
                   }
                   else if(Ltext_1==qufan(inlist0.at(i))){
                        outtext0=outtext0;
                   }
                   else{
                       if(i<inlist0.count()-1){
                           outtext0=outtext0+Ltextlist0.back()+inlist0.at(i)+"OR";
                       }
                       else{
                           outtext0=outtext0+Ltextlist0.back()+inlist0.at(i);
                       }
                   }
                }
                leftpre=Ltext0.left(Ltext0.count()-Ltextlist0.back().count());
            }
            else{
                outtext0=intext;
                leftpre="";
            }
        }
        else{
            outtext0=intext;
            leftpre="";
        }
        if(Rtext0.count()>=3){
            if(Rtext0.at(0)=="A"&&Rtext0.at(1)=="N"&&Rtext0.at(2)=="D"){
                QStringList inlist0=outtext0.split("OR");
                QString Rtextfirst=Rtext0;
                int findR2=1;
                for(int jj=0;jj<Rtext0.count();jj++){
                    if(Rtext0.at(jj)=="("){
                        findR2++;
                    }
                    else if(Rtext0.at(jj)==")"){
                        findR2--;
                    }
                    else if(Rtext0.at(jj)=="R"&&jj>1){
                        if(Rtext0.at(jj-1)=="O"&&findR2==1){
                             Rtextfirst=Rtext0.left(jj-1);
                             break;
                        }
                    }
                }
                 for(int i=0;i<inlist0.count();i++){
                     QString Rtext_1=Rtextfirst.right(Rtextfirst.count()-3);

                     if(Rtext_1==inlist0.at(i)){
                         if(i<inlist0.count()-1){
                             outtext1=outtext1+inlist0.at(i)+"OR";
                         }
                         else{
                             outtext1=outtext1+inlist0.at(i);
                         }
                     }
                     else if(Rtext_1==qufan(inlist0.at(i))){
                          outtext1=outtext1;
                     }
                     else{
                         if(i<inlist0.count()-1){
                                outtext1=outtext1+inlist0.at(i)+Rtextfirst+"OR";
                           }
                        else{
                             outtext1=outtext1+inlist0.at(i)+Rtextfirst;
                            }
                     }
                    }
                 rightpre=Rtext0.right(Rtext0.count()-Rtextfirst.count());
                }
            else{
                outtext1=outtext0;
                rightpre="";
            }
        }
        else{
            rightpre="";
            outtext1=outtext0;
        }
        outtext1=leftpre+outtext1+rightpre;
        if(Ltext0.count()>=2){
            if(Ltext0.back()=="R"&&Ltext0.at(Ltext0.count()-2)=="O"){
                 outtext1=Ltext0+outtext1;
            }
        }
        if(Rtext0.count()>=2){
            if(Rtext0.at(0)=="O"&&Rtext0.at(1)=="R"){
                outtext1=outtext1+Rtext0;
            }
        }
        outtext.replace(pos1,pos2,outtext1);
        return qukuohao(outtext);
    }
   return outtext;
}
QString addruleDialog::qufan(QString text1){
    QString textout;
    if(text1.contains("OR")){
        QStringList inlist0=text1.split("OR");
        for(int i=0;i<inlist0.count();i++){
            if(i<inlist0.count()-1){
                textout=textout+ qufan(inlist0.at(i))+"AND";
            }
            else{
                textout=textout+ qufan(inlist0.at(i));
            }
        }
    }
    else if(text1.contains("AND")){
       textout="(";
        QStringList inlist0=text1.split("AND");
        for(int i=0;i<inlist0.count();i++){
            if(i<inlist0.count()-1){
                textout=textout+ qufan(inlist0.at(i))+"OR";
            }
            else{
                textout=textout+ qufan(inlist0.at(i))+")";
            }
        }
    }
    else{
        if(text1.left(3)=="NOT"){
            textout=text1.remove(0,3);
        }
        else{
            textout="NOT"+text1;
        }
    }
    return textout;
}
