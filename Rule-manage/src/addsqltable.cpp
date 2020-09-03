//#include "addsqltable.h"
//#include "ui_addsqltable.h"
//#include<QtDebug>
//addsqltable::addsqltable(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::addsqltable)
//{
//    ui->setupUi(this);
//    setWindowTitle("添加规则表");
//    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(send_1()));
//    //Table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
//    //表行随着表格变化而自适应变化    Table->verticalHeader()->setResizeMode(QHeaderView::Stretch);

//}

//addsqltable::~addsqltable()
//{
//    delete ui;
//}
//void addsqltable::datain(QList<QString>list0){
//    ui->tableWidget->clearContents();
//    for(int i=0;i<list0.count();i++){
//        //ui->tableWidget->item(0,i)->setText("aaaa");
//        ui->tableWidget->setItem(0, i, new QTableWidgetItem(list0.at(i)));
//    }
//}
//QList<QString> addsqltable::dataout(){
//    QList<QString>list1;
//    for(int i=0;i<ui->tableWidget->columnCount();i++){
//        list1.append(ui->tableWidget->item(0,i)->text());
//    }

//    return list1;
//}
//void addsqltable::send_1(){
//    emit send_flag1(true);
//}
#include "addsqltable.h"
#include "ui_addsqltable.h"
#include<QtDebug>
#include <QMessageBox>
addsqltable::addsqltable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsqltable)
{
    ui->setupUi(this);
    setWindowTitle("添加规则表");
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(send_1()));
    connect(ui->pushButton_1,SIGNAL(clicked()),this,SLOT(close()));
    ui->lineEdit->hide();
    ui->label->hide();
    //Table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //表行随着表格变化而自适应变化    Table->verticalHeader()->setResizeMode(QHeaderView::Stretch);

}

addsqltable::~addsqltable()
{
    delete ui;
}
void addsqltable::datain(QList<QString>list0){
    //ui->lineEdit->setEnabled(1);
    ui->lineEdit->clear();
    ui->lineEdit_1->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_1->setEnabled(1);
    ui->lineEdit_2->setEnabled(1);
    ui->lineEdit_3->setEnabled(1);
    ui->lineEdit_4->setEnabled(1);
    ui->lineEdit_5->setEnabled(1);
    for(int i=0;i<list0.count();i++){
        //ui->tableWidget->item(0,i)->setText("aaaa");
        switch(i){
          case 0:
            ui->lineEdit->setText(list0.at(i));
            //ui->lineEdit->setEnabled(0);
            break;
          case 1:
            ui->lineEdit_1->setText(list0.at(i));
            //ui->lineEdit_1->setEnabled(0);
            break;
          case 2:
            ui->lineEdit_2->setText(list0.at(i));
            //ui->lineEdit_2->setEnabled(0);
            break;
          case 3:ui->lineEdit_3->setText(list0.at(i));
            //ui->lineEdit_2->setEnabled(0);
            break;
          case 4:ui->lineEdit_4->setText(list0.at(i));
            //ui->lineEdit_2->setEnabled(0);
            break;
          case 5:ui->lineEdit_5->setText(list0.at(i));break;
        }
    }
}
QList<QString> addsqltable::dataout(){
    QList<QString>list1;
    //QString input = ui->lineEdit->text();

     list1.append(ui->lineEdit->text());
     list1.append(ui->lineEdit_1->text());
     list1.append(ui->lineEdit_2->text());
     list1.append(ui->lineEdit_3->text());
     list1.append(ui->lineEdit_4->text());
     list1.append(ui->lineEdit_5->text());
    return list1;
}
void addsqltable::send_1(){

    if (ui->lineEdit_1->text().isEmpty()||ui->lineEdit_2->text().isEmpty()||ui->lineEdit_3->text().isEmpty()||ui->lineEdit_4->text().isEmpty()||ui->lineEdit_5->text().isEmpty())
    {
        QMessageBox::warning(this,QString("提示!"),QString("输入不可为空"));
    }
    else{
        emit send_flag1(true);
    }

}
