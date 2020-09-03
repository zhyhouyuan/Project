#include "datain0.h"
#include "ui_datain0.h"
#include<QMessageBox>
#include"checkdialog.h"
datain0::datain0(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::datain0)
{
    ui->setupUi(this);
    ui->data_table->setRowCount(3);
    connect(ui->dinbutton,SIGNAL(clicked()),this,SLOT(send_0()));
}

datain0::~datain0()
{
    delete ui;
}
void datain0::settable(QDomElement e){
    ui->data_table->clear();
    CBox_list.clear();
    DBox_list.clear();
    datatypelist.clear();
    maxvalue.clear();
    minvalue.clear();
    dwlist.clear();
    QDomNodeList list=e.childNodes();
    ui->data_table->setColumnCount(list.count());
    for(int i=0;i<list.count();i++){
        ui->data_table->setItem(i,0,new QTableWidgetItem(list.at(i).toElement().attribute("中文名称")));
        QComboBox *combox_1 = new QComboBox(); // 下拉选择框控件
        QString datatype=list.at(i).toElement().attribute("数据类型");
        datatypelist.append(datatype);
        dwlist.append(list.at(i).toElement().attribute("单位"));
        maxvalue.append(list.at(i).toElement().attribute("最大值"));
        minvalue.append(list.at(i).toElement().attribute("最小值"));
        QComboBox *combox_2 =new QComboBox();

        if(datatype=="double"||datatype=="int"||datatype=="string"){
            combox_1->addItem("=");
            combox_1->addItem(">");
            combox_1->addItem("<");
            combox_1->addItem("<=");
            combox_1->addItem(">=");
            combox_2->setEditable(1);
        }
        else{
            QDomNode mnode=e.parentNode().previousSibling();//返回到枚举数据类型节点
            combox_1->addItem("=");
            QDomNode node1=mnode.firstChild();
            while(!node1.isNull())  //如果节点不空
            {
                if(node1.isElement()) //如果节点是元素
                {
                    QDomElement e=node1.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
                    if(e.attribute("名称")==datatype){
                        QDomNodeList list=e.childNodes();
                        for(int i=0;i<list.count();i++){
                            combox_2->addItem(list.at(i).toElement().attribute("中文名称"));
                        }
                    }
                }
                node1=node1.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
            }

        }
        ui->data_table->setCellWidget(i, 1, (QWidget*)combox_1);
        ui->data_table->setCellWidget(i,2,(QWidget*)combox_2);
        CBox_list.append(combox_1);
        DBox_list.append(combox_2);
        ui->data_table->setItem(i,2,new QTableWidgetItem(list.at(i).toElement().attribute("单位")));
    }
}
QString datain0::getalltext(){
    int m =ui->data_table->rowCount();
    int n = ui->data_table->columnCount();
    QString text0="{";
    for(int i=0;i<m;i++){
        if(!DBox_list.at(i)->currentText().isEmpty()){
            bool flag=checkDialog::check_maxmin(datatypelist.at(i),maxvalue.at(i),minvalue.at(i),DBox_list.at(i)->currentText());
            if(flag){
                text0=text0+ui->data_table->item(i,0)->text()+CBox_list.at(i)->currentText()+DBox_list.at(i)->currentText();
//                for(int j=0;j<n;j++){
//                   if(j==1){
//                       text0=text0+CBox_list.at(i)->currentText();
//                       }
//                   else if(j==0){
//                       text0=text0+ui->data_table->item(i,j)->text();
//                  }
//                }
            }
            else{
                QMessageBox::warning(this, tr("输入提示！"),
                                     tr("输入值错误(错误位置：第%4行，数据类型：%1，最大值：%2，最小值：%3)").arg(datatypelist.at(i)).arg(maxvalue.at(i)).arg(minvalue.at(i)).arg(i+1));
                return nullptr;
            }

            if(i<m-1){
                if(!DBox_list.at(i+1)->currentText().isEmpty()){
                     text0=text0+"&";
                }
            }
        }  
    }
    text0=text0+"}";
    return text0;
}
void datain0::send_0(){
    //if(ui->buttonBox->button(QDialogButtonBox::Ok)
    emit send_flag(true);
}
