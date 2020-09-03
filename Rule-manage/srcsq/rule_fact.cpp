#include "rule_fact.h"
#include <QtDebug>
#include"src/changedialog.h"
#include<QtDebug>
Rule_fact::Rule_fact()
{

}
Rule_fact::~Rule_fact(){

}
//QStringList Rule_fact::StringSplit(QString datain0){
//   QStringList listfuh;
//   QString datain=datain0.simplified();
//   listfuh<<"="<<">"<<"<"<<">="<<"<=";
//   QVector<int>pos;
//   int pos_0=datain.indexOf(listfuh.at(0));
//   int pos_1=datain.indexOf(listfuh.at(1));
//   int pos_2=datain.indexOf(listfuh.at(2));
//   pos.append(pos_0);
//   pos.append(pos_1);
//   pos.append(pos_2);
//   for(int i=0;i<pos.count();i++){
//       if(pos.at(i)<0){
//           pos.operator[](i)=1000;
//       }
//   }
//   auto min = std::min_element(std::begin(pos), std::end(pos));
//        //直接赋值表示
//   int smallest = *min;
//        //最大值和最小值的位置的表示方式
//   auto positionmin = std::distance(std::begin(pos),min);
//   int posmin = positionmin;
//   int ls=listfuh.at(posmin).count();
//   QString fuh=datain.mid(smallest,ls);
//   int lastpos=datain.lastIndexOf(".");
//   QString last=datain.mid(lastpos+ls,smallest-lastpos-ls);
//   QString NOTvalue;
//   QString pre;
//   if(datain.left(3)=="NOT"){
//       NOTvalue="NOT";
//       pre=datain.right(datain.count()-3).left(lastpos+1);
//   }
//   else{
//       NOTvalue="";
//       pre=datain.left(lastpos+ls);
//   }
//   QString value=datain.right(datain.length()-smallest-ls);
//   last=last.simplified();
//   pre=pre.simplified();
//   QStringList listout;
//   listout<<NOTvalue<<pre<<last<<fuh<<value;
//   return listout;
//}

void Rule_fact::addfact(QString name){
    int row=findfactIndex(findfact(name));
    if(row!=-1)
    {
//        int num=model_fact->index(row,2).data().toInt();
//        this->model_fact->setData(model_fact->index(row,2),num+1);
        int num=model_fact->index(row,4).data().toInt();
        this->model_fact->setData(model_fact->index(row,4),num+1);
    }
    else{
        int num1=model_fact->rowCount();
        model_fact->insertRow(num1);
        int lastID=model_fact->data(model_fact->index(num1-1,0)).toInt()+1;
        model_fact->setData(model_fact->index(num1,0),lastID);

        QStringList list1=changeDialog::StringSplit(name);
       // qDebug()<<list1<<name;
        model_fact->setData(model_fact->index(num1,1),list1.at(0)+list1.at(1)+list1.at(2));
        model_fact->setData(model_fact->index(num1,2),list1.at(3));
        model_fact->setData(model_fact->index(num1,3),list1.at(4));

        model_fact->setData(model_fact->index(num1,4),1);

    }
   // model_fact->submitAll();
}
int Rule_fact::findfact(QString fact_name){
    for(int i=0;i<model_fact->rowCount();i++){
//        if(model_fact->data(model_fact->index(i,1)).toString()==fact_name){
//            return model_fact->data(model_fact->index(i,0)).toInt();
//        }
        if(model_fact->data(model_fact->index(i,1)).toString()+model_fact->data(model_fact->index(i,2)).toString()+model_fact->data(model_fact->index(i,3)).toString()==fact_name){
                    return model_fact->data(model_fact->index(i,0)).toInt();
          }
    }
    return -1;
}
QString Rule_fact::findfactID(int ID){
    for(int i=0;i<model_fact->rowCount();i++){
        if(model_fact->data(model_fact->index(i,0)).toInt()==ID){
//            return model_fact->data(model_fact->index(i,1)).toString();
            return model_fact->data(model_fact->index(i,1)).toString()+model_fact->data(model_fact->index(i,2)).toString()+model_fact->data(model_fact->index(i,3)).toString();
        }
    }
    return nullptr;
}
int Rule_fact::findfactIndex(int ID){
    for(int i=0;i<model_fact->rowCount();i++){
        if(model_fact->data(model_fact->index(i,0)).toInt()==ID){
            return i;
        }
    }
    return -1;
}
void Rule_fact::removefact(int Id){
    int row=findfactIndex(Id);
    if(row!=-1)
    {
        int num=model_fact->index(row,2).data().toInt();
        if(num>1){
            //this->model_fact->setData(model_fact->index(row,2),num-1);
            this->model_fact->setData(model_fact->index(row,4),num-1);
        }
        else{
            bool flag=model_fact->removeRow(row);
        }
       // model_fact->submitAll();
    }
}
void Rule_fact::submit(){
    bool flag=model_fact->submitAll();
   // qDebug()<<flag<<"提交";
}
