#include "gcombox.h"
#include <QStandardItem>
#include<QStandardItemModel>
Gcombox::Gcombox(QWidget *parent):QComboBox(parent)
{
   myview = new QTreeView(this);
   myview->setMinimumHeight(200);
   //myview->setSizePolicy();
   this->setView(myview);
    connect(this,SIGNAL(activated(int)),this,SLOT(send_0()));
   //this->
}
void Gcombox::mousePressEvent(QMouseEvent *e){
    if(e->button()==Qt::LeftButton){
        QComboBox::mousePressEvent(e);
    }
}
QString Gcombox::getParent(){
    QString text;
    QModelIndex index=myview->currentIndex().parent();
    while(index.isValid()&&index.parent().isValid()){
        text=index.data().toString()+"."+text;
        index=index.parent();
    }
    return text;
   // myview->currentIndex().parent().data().toString()+"."+myview->currentIndex().data().toString()
}
void Gcombox::setModel(QStandardItemModel *model_0){
    this->model=model_0;
    QComboBox::setModel(model_0);
    this->myview->expandAll();
   // this->setCurrentIndex(1);
}
void Gcombox::hidePopup(){
     //qDebug()<<this->itemData(this->currentIndex());

    QVariant n=this->currentData();


     if(!myview->currentIndex().child(0,0).isValid()){
         QComboBox::hidePopup();
     }
     //qDebug()<<myview->currentIndex().parent().data().toString();
     //this->setCurrentText(myview->currentIndex().parent().data().toString()+"."+myview->currentIndex().data().toString());
}
void Gcombox::setView(QTreeView *view){
   // this->myview=view;
   // this->myview->setModel(this->model());
    QComboBox::setView(view);
}
void Gcombox::send_0(){
    //if(ui->buttonBox->button(QDialogButtonBox::Ok)
    emit send_flag(num,if_thenflag);
}
void Gcombox::setflag(int i,bool flag){
    this->num=i;
    this->if_thenflag=flag;
}
void Gcombox::setCText(QString text){
//    for(int i = 0;i < this->model->rowCount() ;i++)
//    {
//        QStandardItem *item =  this->model->item(i);
//        if(item->text()==text){
//            this->myview->setCurrentIndex(item->index());
//        }
//        else{
//            GetItem(model->item(i),text);
//        }
//    }
    QAbstractItemModel *model = this->view()->model();
    QModelIndexList Items = model->match(model->index(0, 0),Qt::DisplayRole,QVariant::fromValue(text), 1, Qt::MatchRecursive); // look *
    for(QModelIndex index : Items){
    this->setRootModelIndex(index.parent());
    this->setModelColumn(index.column());
    this->setCurrentIndex(index.row());
    this->setRootModelIndex(QModelIndex());
    this->view()->setCurrentIndex(index);
    }
    //this->setCurrentIndex(this->myview->currentIndex().row());
    //this->findText(text);
}


