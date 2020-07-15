#include "addsqltable.h"
#include "ui_addsqltable.h"
#include<QtDebug>
addsqltable::addsqltable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsqltable)
{
    ui->setupUi(this);
    setWindowTitle("添加规则表");
    //ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(ui->pushButton_0,SIGNAL(clicked()),this,SLOT(send_1()));
    //Table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    //表行随着表格变化而自适应变化    Table->verticalHeader()->setResizeMode(QHeaderView::Stretch);

}

addsqltable::~addsqltable()
{
    delete ui;
}
void addsqltable::datain(QList<QString>list0){
    ui->tableWidget->clearContents();
    for(int i=0;i<list0.count();i++){
        //ui->tableWidget->item(0,i)->setText("aaaa");
        ui->tableWidget->setItem(0, i, new QTableWidgetItem(list0.at(i)));
    }
}
QList<QString> addsqltable::dataout(){
    QList<QString>list1;
    for(int i=0;i<ui->tableWidget->columnCount();i++){
        list1.append(ui->tableWidget->item(0,i)->text());
    }

    return list1;
}
void addsqltable::send_1(){
    emit send_flag1(true);
}
