#include "viewmodel.h"
#include<QColor>
#include <QMessageBox>
#include <QCoreApplication>
#include<QFileDialog>
#include <QtXml>
#include<QSqlRecord>
#include"uisrc/changedialog.h"
#include"uisrc/checkdialog.h"
#include<QtConcurrent>
#include<QApplication>
viewmodel::viewmodel(QObject * parent):QAbstractTableModel(parent)
{
    this->disflag=1;
    this->open_close=0;
    this->rulefact=new Rule_fact();
    currentf=0;
    //QObject::connect(&m_futureWatcher, &QFutureWatcher<double>::finished, this, &QtConcurrentTestWidget::threadFinished);
//  this->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//  this->setHeaderData(1, Qt::Horizontal, QStringLiteral("条件"));
//  this->setHeaderData(2, Qt::Horizontal, QStringLiteral("结果"));
//  this->setHeaderData(3, Qt::Horizontal, QStringLiteral("权重"));
}

void viewmodel::setview(QList<QSqlTableModel*>modellist){
    if(currentf==0){
        future =QtConcurrent::run(this,&viewmodel::setview_0,modellist);
        currentf=1;
        QApplication::processEvents();
        future.waitForFinished();
        //future.cancel();
        //future.begin();
        m_futureWatcher.setFuture(future);

    }
//    if(future.isFinished()){
//        qDebug()<<"进程结束";
//        currentf=0;
//       emit sendRowchanged(true);
//    }
}
QVariant viewmodel::setview_0(QList<QSqlTableModel*>modellist){
    this->check_state_map.clear();
    //beginResetModel();
    //QThread::sleep(5);
    int rownum=0;
    listnum.clear();
    modellist0=modellist;
    if(!modellist.isEmpty()){
        for(int i=0;i<modellist.count();i++){
            //for(int j=0;j<modellist.at(i)->rowCount();j++){
              //for(int k=0;j<modellist.at(i)->columnCount();k++)
              //this->datalist.at(rownum+j)->append(modellist.at(i)->index(j,k).data());
              //this->setData(index(rownum+j,k),modellist.at(i)->index(j,k).data());
            //}
            rownum=rownum+modellist.at(i)->rowCount()+1;
            listnum.append(rownum);
        }
        this->updata();
        //emit sendRowchanged(true);
        currentf=0;
        emit sendRowchanged(true);
        return QVariant();
    }

    else currentf=0;
        return QVariant();
}
void viewmodel::updata(){
    beginResetModel();
    endResetModel();
}
int viewmodel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    if (disflag) return 5;
    else
      return 6;
}

int viewmodel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent)
    if(disflag)
        //this->rowcount=listnum.back();
        return listnum.back();
    else return listnum.back()-1;
}
bool viewmodel::setData( const QModelIndex &index, const QVariant &value, int role ){
    if(!index.isValid())
            return false;
    if (role == Qt::CheckStateRole && index.column() == 0) {
        check_state_map[index.row()] = (value == Qt::Checked ? Qt::Checked : Qt::Unchecked);
        //this->checkout();
        return true;
    }
    else
       //QAbstractTableModel::setData( index, value,role );
    return true;
}
QVariant viewmodel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    switch(role){
    case Qt::DisplayRole:
    {
        if(this->disflag){
            int num=0;
            if(!modellist0.isEmpty()){
                //显示表内数据
              for(int i=0;i<listnum.count();i++){
                  if(index.row()<listnum.at(i)&&index.row()>0){
                          if(i>=1){
                              num=listnum.at(i-1)+1;
                          }
                          else {num=1;}
                          if(index.column()>0&&index.column()<3){
                              QString rule=this->EnltoCh(this->transRule(modellist0.at(i)->index(index.row()-num,index.column()).data().toString(),1));
                          return rule;
                          }
                          else if(index.column()==0) return index.row()-i;
                       else return modellist0.at(i)->index(index.row()-num,index.column()).data();
                       //return this->EnltoCh(modellist0.at(i)->index(index.row()-num,index.column()).data().toString());
                  }
                  //显示第一个表前缀
                  if(index.row()==0){
                          if(!Tablehead.isEmpty()){
                              if(index.column()<=4){
                                  return this->Tablehead.at(0).at(4-index.column());
                              }
                          }
                      }

                  //显示后续表前缀
                  if (index.row()==listnum.at(i)){
                      if(!Tablehead.isEmpty()&&i<Tablehead.count()){
                      if(index.column()<=4){
                          return this->Tablehead.at(i+1).at(4-index.column());
                      }
                  }
                  }
              }
          }
        }
        else{
            if(!modellist0.isEmpty()){
                return modellist0.at(0)->index(index.row(),index.column()).data();
            }
        }


        return QVariant();
    }
        //复选框
    case Qt::CheckStateRole:
    {
        if(disflag&&open_close){
            bool flag=(index.row()!=0);
            for(int i=0;i<listnum.count();i++){
                flag=flag&&(index.row()!=listnum.at(i));
            }
            if(flag&&index.column()==0){
                if (check_state_map.contains(index.row()))
                    return check_state_map[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;
                return Qt::Unchecked;
            }
         return QVariant();
        }
        return  QVariant();
      }

    case Qt::BackgroundRole:
        if(disflag){
            if(index.row()==0){
                //QColor(187, 212, 238);
                return QColor(230,240,240);
            }
            else{
                for(int i=0;i<listnum.count();i++){
                    if(index.row()==listnum.at(i)){
                        return QColor(230,240,240);
                    }
                }
              return QColor(255,255,255);
            }
        }
        return QColor(255,255,255);

    default:
        return QVariant();
    }
    //return QVariant();
}
bool viewmodel::set_Wvalue(int row,int a){
    if(row<listnum.at(0)&&row>0){
            modellist0.at(0)->setData(modellist0.at(0)->index(row-1,3),a);
            //modellist0.at(0)->submitAll();
            return 1;
    }
    else{
        for(int i=1;i<listnum.count();i++){
            if(row<listnum.at(i)&&row>listnum.at(i-1)){
                modellist0.at(i)->setData(modellist0.at(i)->index(row-listnum.at(i-1)-1,3),a);
                //modellist0.at(i)->submitAll();
                return 1;
            }
        }
        return 0;
    }
}
bool viewmodel::submit_W(){
    QMap<int, Qt::CheckState>::iterator it;
    for ( it = this->check_state_map.begin(); it != this->check_state_map.end(); ++it )
    {
        if(it.value()==Qt::Checked){
            int k=it.key();
            int ik=0;
            int num=0;
            bool flag_c=0;
            if(k<listnum.at(0)&&k>0){
                ik=0;
                num=k-1;
                flag_c=1;
            }
            else{
                  for(int i=1;i<listnum.count();i++){
                    if(k<listnum.at(i)&&k>listnum.at(i-1)){
                        ik=i;
                        flag_c=1;
                        num=k-listnum.at(i-1)-1;
                        break;
                    }
                  }
            }
            if(flag_c){
                QSqlTableModel* modelout=new QSqlTableModel(this,modellist0.at(ik)->database());
                modelout->setTable(modellist0.at(ik)->tableName());
                modelout->select();
                modelout->setData(modelout->index(num,3),modellist0.at(ik)->record(num).value(3).toInt());
                modelout->submitAll();
             }
         }
    }
    this->setview(this->modellist0);
    return 1;
}
QVariant viewmodel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role==Qt::DisplayRole&&this->disflag==1){
        if (orientation == Qt::Horizontal)
                switch (section)
                {
                    case 0:
                        return     QVariant(QString("序号"));
                    case 1:
                        return     QVariant(QString("条件"));
                    case 2:
                        return     QVariant(QString("结果"));
                    case 3:
                        return     QVariant(QString("权重"));
                    default:
                        return     QVariant(QString(""));
                }
        if (orientation == Qt::Vertical){
            return QVariant(QString(""));
        }
    }
    else if(role==Qt::DisplayRole&&this->disflag==0){
        if (orientation == Qt::Horizontal){
            switch (section)
            {
                case 0:
                    return     QVariant(QString("ID"));
                case 1:
                    return     QVariant(QString("类型"));
                case 2:
                    return     QVariant(QString("型号"));
                case 3:
                    return     QVariant(QString("模式"));
                case 4:
                    return QVariant(QString("任务"));
                case 5:
                    return QVariant(QString("规则数据"));
                default:
                    return     QVariant(QString(""));
            }
        }
        if (orientation == Qt::Vertical){
            return QVariant(QString(""));
        }

    }
    return QAbstractTableModel::headerData(section,orientation,role);

}
Qt::ItemFlags viewmodel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
             return 0;
    if (index.column() == 0)
           return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
     return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QSqlRecord viewmodel::getrecord(int row){
    QSqlRecord record0;
    if(row<=listnum.at(0)&&row>0){
         record0=modellist0.at(0)->record(row-1);
         for(int j=0;j<record0.count();j++){
             if(!record0.value(j).isNull()){
                 if(j==1||j==2){
                     record0.setValue(j,this->EnltoCh(this->transRule(record0.value(j).toString(),1)));
                 }
                 else{
                     record0.setValue(j,record0.value(j).toString());
                 }
             }
         }
        return record0;
    }
    else{
        for(int i=1;i<listnum.count();i++){
            if(row<=listnum.at(i)&&row>listnum.at(i-1)){
                record0=modellist0.at(i)->record(row-listnum.at(i-1)-1);
                for(int j=0;j<record0.count();j++){
                    if(!record0.value(j).isNull()){
                        if(j==1||j==2){
                            record0.setValue(j,this->EnltoCh(this->transRule(record0.value(j).toString(),1)));
                        }
                        else{
                            record0.setValue(j,record0.value(j).toString());
                        }

                    }

                }
                return record0;
        }
        }
    }
    return record0;
}
//bool viewmodel::findrecord(QList<QString> name0){

//}
//bool viewmodel::findrecord(QList<QString> name0){
//    QList<QSqlTableModel*> findmodellist;
//    QList<QList<QString>>Tablehead_find;
//    QString name_0=name0.first();
//    QString name_2=name0.at(1);
//    QString name_3=name0.back();
//    for(int i=0;i<listnum.count();i++){
//        QList<QString>idlist;
//        QString  findcondition=nullptr;
//        for(int j=0;j<modellist0.at(i)->rowCount();j++){
//           QSqlRecord record=modellist0.at(i)->record(j);
//           if(this->EnltoCh(this->transRule(record.value(1).toString(),1)).contains(name_0)&&this->EnltoCh(this->transRule(record.value(1).toString(),1)).contains(name_2)&&record.value(2).toString().contains(name_3)){
//               idlist.append(record.value(0).toString());
//               if(!findmodellist.contains(modellist0.at(i))){
//                   findmodellist.append(modellist0.at(i));
//                   Tablehead_find.append(Tablehead.at(i));
//               }
//           }
//        }
//        QString headname=modellist0.at(i)->headerData(0,Qt::Orientation::Horizontal).toString();
//        for(int k=0;k<idlist.count();k++){
//            findcondition=findcondition+"("+"id"+"="+idlist.at(k)+")";
//               if(k<idlist.count()-1){
//                  findcondition=findcondition+"OR";
//             }
//        }
//        //
//        modellist0.at(i)->setFilter(findcondition);
//        modellist0.at(i)->select();
//    }
//    if(findmodellist.isEmpty()){
//        return false;
//    }
//    else{
//        this->Tablehead.clear();
//        this->Tablehead=Tablehead_find;
//        this->setview(findmodellist);
//        return true;
//    }

bool viewmodel::addrecord(QList<QString>recordlist0,int row){
    QList<QString>recordlist;
    recordlist.append(this->transRule(this->ChtoEnl(recordlist0.at(0)),2));
    recordlist.append(this->transRule(this->ChtoEnl(recordlist0.at(1)),2));
    recordlist.append(recordlist0.at(2));
    if(row<listnum.at(0)&&row>=0){
        int aarow;
        if(row==0){
            aarow=0;
        }
        else{
            aarow=row-1;
        }
        if(checkrecord(recordlist.at(0),recordlist.at(1),modellist0.at(0))==-1){
            int id=modellist0.at(0)->rowCount();
            modellist0.at(0)->insertRow(id);
            modellist0.at(0)->setData(modellist0.at(0)->index(id,0),id+1);
            for(int i=0;i<recordlist.count();i++){
                 modellist0.at(0)->setData(modellist0.at(0)->index(id,i+1),this->ChtoEnl(recordlist.at(i)));
            }
            this->setview(modellist0);
            return 1;
        }
        else{
            this->transRule(recordlist.at(0),3);
            this->transRule(recordlist.at(1),3);
            return 0;
        }
    }
    else{
        for(int i=1;i<listnum.count();i++){
            if(row<listnum.at(i)&&row>=listnum.at(i-1)){
                int aarow2;
                if(row==listnum.at(i-1)){
                    aarow2=0;
                }
                else{
                    aarow2=row-listnum.at(i-1)-1;
                }
                if(checkrecord(recordlist.at(0),recordlist.at(1),modellist0.at(i))==-1){
                    int id=modellist0.at(i)->rowCount();
                    modellist0.at(i)->insertRow(id);
                    modellist0.at(i)->setData(modellist0.at(i)->index(id,0),id+1,Qt::EditRole);
                    for(int j=0;j<recordlist.count();j++){
                         modellist0.at(i)->setData(modellist0.at(i)->index(id,j+1),recordlist.at(j),Qt::EditRole);
                    }
                    this->setview(modellist0);
                    return 1;
                }
                else{
                    //this->transRule(recordlist.at(0),3);
                    //this->transRule(recordlist.at(1),3);
                   return 0;
                }
                //modellist0.at(i)->setData(modellist0.at(i)->index(row-1,0),"aaa");
            }
        }
    }
    return 0;
}
bool viewmodel::setrecord(QSqlRecord record0,int row){
    record0.setValue(1,this->transRule(this->ChtoEnl(record0.value(1).toString()),2));
    record0.setValue(2,this->transRule(this->ChtoEnl(record0.value(2).toString()),2));
    if(row<listnum.at(0)&&row>0){
        //QSqlRecord record1;
        if(checkrecord(record0.value(1).toString(),record0.value(2).toString(),modellist0.at(0))==-1){
            modellist0.at(0)->setRecord(row-1,record0);
            return 1;
        }
        else if(checkrecord(record0.value(1).toString(),record0.value(2).toString(),modellist0.at(0))==row-1){
            if(record0.value(3).toInt()!=modellist0.at(0)->record(row-1).value(3).toInt()){
                modellist0.at(0)->setRecord(row-1,record0);
                return 1;
            }

                return 0;
        }
        else{
            return 0;
        }
    }
    else{
        for(int i=1;i<listnum.count();i++){
            if(row<listnum.at(i)&&row>listnum.at(i-1)){
                if(checkrecord(record0.value(1).toString(),record0.value(2).toString(),modellist0.at(i))==-1){
                    modellist0.at(i)->setRecord(row-listnum.at(i-1)-1,record0);
                    return 1;
                }
                else if(checkrecord(record0.value(1).toString(),record0.value(2).toString(),modellist0.at(i))==row-listnum.at(i-1)-1){
                    if(record0.value(3).toInt()!=modellist0.at(i)->record(row-listnum.at(i-1)-1).value(3).toInt()){
                        modellist0.at(i)->setRecord(row-listnum.at(i-1)-1,record0);
                        //qDebug()<<record0.value(3).toInt()<<checkrecord(record0.value(1).toString(),record0.value(2).toString(),modellist0.at(i))<<row-listnum.at(i-1)-1;
                        return 1;
                    }
                     return 0;
                }
                else{
                    return 0;
                }
            }
        }
    }
    return 0;
}
bool viewmodel::submit_checked(){
    QMap<int, Qt::CheckState>::iterator it; //遍历map
    qDebug()<<this->check_state_map;
    for ( it = this->check_state_map.begin(); it != this->check_state_map.end(); ++it )
    {
        if(it.value()==Qt::Checked){
            int k=it.key();
            int ik=0;
            int num=0;
            bool flag_c=0;
            if(k<listnum.at(0)&&k>0){
                ik=0;
                num=k-1;
                flag_c=1;
            }
            else{
                  for(int i=1;i<listnum.count();i++){
                    if(k<listnum.at(i)&&k>listnum.at(i-1)){
                        ik=i;
                        flag_c=1;
                        num=k-listnum.at(i-1)-1;
                        break;
                    }
                   //return 0;
                  }
            }
            //qDebug()<<flag_c;
            if(flag_c){
                QSqlTableModel* modelout=new QSqlTableModel(this,modellist0.at(ik)->database());
                modelout->setTable(modellist0.at(ik)->tableName());
                modelout->select();
               // int id=modellist0.at(ik)->record(num).value(0).toInt();
                if(num<modelout->rowCount()){
                    this->sub_fact(modelout->record(num).value(1).toString(),0);
                    this->sub_fact(modelout->record(num).value(2).toString(),0);
                    modelout->setRecord(num,modellist0.at(ik)->record(num));
                    this->sub_fact(modellist0.at(ik)->record(num).value(1).toString(),1);
                    this->sub_fact(modellist0.at(ik)->record(num).value(2).toString(),1);
                }
                else{
                    this->sub_fact(modellist0.at(ik)->record(num).value(1).toString(),1);
                    this->sub_fact(modellist0.at(ik)->record(num).value(2).toString(),1);

                    QSqlRecord recored0=modellist0.at(ik)->record(num);
                    //qDebug()<<recored0.value(1);
                    for(int j=num;j>modelout->rowCount();j--){
                        modellist0.at(ik)->setRecord(j, modellist0.at(ik)->record(j-1));
                        modellist0.at(ik)->setData(modellist0.at(ik)->index(j,0),j+1);
                    }
                    modellist0.at(ik)->setRecord(modelout->rowCount(),recored0);
                    modellist0.at(ik)->setData(modellist0.at(ik)->index(modelout->rowCount(),0),modelout->rowCount()+1);
                    //modellist0.at(ik)->setData(modelout->index(j,0),j+1);
                    //check_state_map.
                    check_state_map[k] = Qt::Unchecked;
                    //qDebug()<<recored0.value(1);
                    //bool flag0=modellist0.at(ik)->moveRow(modelout->rowCount(),num);
                    bool flag=modelout->insertRecord(modelout->rowCount(),recored0);
                    bool flag2=modelout->setData(modelout->index(modelout->rowCount()-1,0),modelout->rowCount());

                    qDebug()<<flag<<flag2<<num;
                }
                modelout->submitAll();
             }
            }
    }
    this->setview(this->modellist0);
    return 1;
}
void viewmodel::sub_fact(QString ch,bool ad_de){
    Rule_fact *subfact=new Rule_fact();
    subfact->model_fact=new QSqlTableModel(this,this->rulefact->model_fact->database());
    subfact->model_fact->setTable(this->rulefact->model_fact->tableName());
    subfact->model_fact->setEditStrategy(QSqlTableModel::OnManualSubmit);
    subfact->model_fact->select();
    QStringList list1;
   // QStringList list_andor;
    //QString ch1=re0.value(1).toString();
    QStringList list_and = ch.split("AND");
    for(int i=0;i<list_and.count();i++){
        QStringList list_or=list_and.at(i).split("OR");
        for(int j=0;j<list_or.count();j++){
              list1.append(list_or.at(j).simplified());
        }
    }
    if(ad_de){
        for(int i=0;i<list1.count();i++){
            int rownum=subfact->findfactIndex(list1.at(i).toInt());
            qDebug()<<rownum<<"aaa";
            if(rownum==-1){
                int num1=subfact->model_fact->rowCount();
                subfact->model_fact->insertRow(num1);
                int lastID=list1.at(i).toInt();
                subfact->model_fact->setData(subfact->model_fact->index(num1,0),lastID);
                int index0=rulefact->findfactIndex(list1.at(i).toInt());

//                subfact->model_fact->setData(subfact->model_fact->index(num1,1),rulefact->findfactID(list1.at(i).toInt()));
//                subfact->model_fact->setData(subfact->model_fact->index(num1,2),1);
                 subfact->model_fact->setData(subfact->model_fact->index(num1,1),rulefact->model_fact->index(index0,1).data());
                 subfact->model_fact->setData(subfact->model_fact->index(num1,2),rulefact->model_fact->index(index0,2).data());
                 subfact->model_fact->setData(subfact->model_fact->index(num1,3),rulefact->model_fact->index(index0,3).data());
                 subfact->model_fact->setData(subfact->model_fact->index(num1,4),1);
            }
            else{
                int num=subfact->model_fact->index(rownum,4).data().toInt();
                subfact->model_fact->setData(subfact->model_fact->index(rownum,4),num+1);
            }
            subfact->submit();
            subfact->model_fact->select();
        }

    }
    else{
        //int rownum=subfact->findfactIndex(list1.at(0).toInt());
        //if(rownum!=-1){
        for(int i=0;i<list1.count();i++){
            subfact->removefact(list1.at(i).toInt());
       // }
            subfact->submit();
            subfact->model_fact->select();
        }
    }
    delete subfact;
}
void viewmodel::settransmodel(QString est,QSqlDatabase db){
    this->EntoCh=new QSqlTableModel(this,db);
    this->EntoCh->setTable(est);
    this->EntoCh->select();
}

QString viewmodel::EnltoCh(QString Enl)const{
    QString ch=Enl;
    ch.replace("AND","&");
    ch.replace("OR","|");
    ch.replace("NOT","~");
      if(!Enl.isEmpty()){
        QStringList chlist=ch.split(QRegExp("[.=&|<>]"));
        int num0=0;
        int postion=0;
        while(num0<chlist.count()){
            if(!chlist.at(num0).isEmpty()){
                int len=chlist.at(num0).count();
                for(int i=0;i<EntoCh->rowCount();i++){
                    QSqlRecord record0=EntoCh->record(i);
                    if(chlist.at(num0)==record0.value(1).toString()){
                        ch.replace(postion,chlist.at(num0).count(),record0.value(2).toString());
                        len=record0.value(2).toString().count();
                        break;
                    }
                }
            postion=len+postion+1;
            }
            num0++;
      }
      }
      ch.replace("&","AND");
      ch.replace("|","OR");
      ch.replace("~","NOT");
    return ch;
}
QString viewmodel::ChtoEnl(QString ch)const{
    QString Enl=ch;
    ch.replace("NOT","~");
    ch.replace("AND","&");
    ch.replace("OR","|");
    if(!ch.isEmpty()){
        QStringList enlist=ch.split(QRegExp("[.=&|><]"));
        int num0=0;
        int postion=0;
        while(num0<enlist.count()){
            if(!enlist.at(num0).isEmpty()){
                int len=enlist.at(num0).count();
                for(int i=0;i<EntoCh->rowCount();i++){
                    QSqlRecord record0=EntoCh->record(i);
                    if(enlist.at(num0)==record0.value(2).toString()){
                        //ch.replace(record0.value(2).toString(),record0.value(1).toString());
                        //qDebug()<<enlist.at(num0)
                        ch.replace(postion,enlist.at(num0).count(),record0.value(1).toString());
                        len=record0.value(1).toString().count();
                        break;
                    }
                }
            postion=postion+len+1;
            }

            num0++;
        }
    }
    ch.replace("&","AND");
    ch.replace("|","OR");
    ch.replace("~","NOT");
    return ch;
}
//QString viewmodel::EnltoCh(QString Enl)const{
//    QString ch=Enl;
//      if(!Enl.isEmpty()){
//        QStringList chlist=Enl.split(QRegExp("[.=]"));
//        int num0=0;
//        while(num0<chlist.count()){
//            if(!chlist.at(num0).isEmpty()){
//                for(int i=0;i<EntoCh->rowCount();i++){
//                    QSqlRecord record0=EntoCh->record(i);
//                    if(chlist.at(num0)==record0.value(1).toString()){
//                        ch.replace(record0.value(1).toString(),record0.value(2).toString());
//                        break;
//                    }
//                }
//            }
//            num0++;
//        }
//        }
//    return ch;
//}

//QString viewmodel::ChtoEnl(QString ch)const{
//    QString Enl=ch;
//    if(!ch.isEmpty()){
//        QStringList enlist=ch.split(QRegExp("[.=]"));
//        int num0=0;
//        while(num0<enlist.count()){
//            if(!enlist.at(num0).isEmpty()){
//                for(int i=0;i<EntoCh->rowCount();i++){
//                    QSqlRecord record0=EntoCh->record(i);
//                    if(enlist.at(num0)==record0.value(2).toString()){
//                        ch.replace(record0.value(2).toString(),record0.value(1).toString());
//                        break;
//                    }
//                }
//            }
//            num0++;
//        }
////        for(int i=0;i<EntoCh->rowCount();i++){
////            QSqlRecord record0=EntoCh->record(i);
////            if(Enl.contains(record0.value(2).toString())){
////                Enl.replace(record0.value(2).toString(),record0.value(1).toString());
////            }
////        }
//    }
//    return ch;
//}
QString viewmodel::transRule(QString ch,int flag)const{
    QString Rule_out;
    QStringList list;
    QStringList list_andor;
    QStringList list_and = ch.split("AND");
    for(int i=0;i<list_and.count();i++){
        QStringList list_or=list_and.at(i).split("OR");
        for(int j=0;j<list_or.count();j++){
              list.append(list_or.at(j).simplified());
              if(j+1<list_or.count()){
                  list_andor.append("OR");
              }
        }
        if(i+1<list_and.count()){
            list_andor.append("AND");
        }
    }
    switch (flag) {
    case 0:{
        for(int i=0;i<list.count();i++){
            Rule_out=Rule_out+QString::number(rulefact->findfact(list.at(i)));
            if(i<list_andor.count()){
                Rule_out=Rule_out+list_andor.at(i);
            }
        }
       return Rule_out;
    }
    case 1:{
        for(int i=0;i<list.count();i++){
            Rule_out=Rule_out+rulefact->findfactID(list.at(i).toInt());
            if(i<list_andor.count()){
                Rule_out=Rule_out+list_andor.at(i);
            }
        }
       return Rule_out;
    }
    case 2:{
        for(int i=0;i<list.count();i++){
            rulefact->addfact(list.at(i));
            Rule_out=Rule_out+QString::number(rulefact->findfact(list.at(i)));
            if(i<list_andor.count()){
                Rule_out=Rule_out+list_andor.at(i);
            }
        }
       return Rule_out;
    }
    case 3:{
        for(int i=0;i<list.count();i++){
            rulefact->removefact(list.at(i).toInt());
         }
        return nullptr;
    }
    default:return nullptr;
    }
}
void viewmodel::WriteXml(QString dirPath){
     QDateTime time2 = QDateTime::currentDateTime();//获取系统现在的时间
     QString str = time2.toString("yyyyMMdd_hhmmss"); //设置显示格式
    QFile file(dirPath); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
        return;
    QDomDocument doc;
    QDomProcessingInstruction instruction; //添加处理命令
    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    //添加根节点
    QDomElement root=doc.createElement("rulebase");
    doc.appendChild(root);
    QList<int>list_num;
    QList<QDomElement>list_Element;
    QMap<int, Qt::CheckState>::iterator it; //遍历map
    for ( it = this->check_state_map.begin(); it != this->check_state_map.end(); ++it )
    {
        if(it.value()==Qt::Checked){
            int k=it.key();
            if(k<=listnum.at(0)&&k>0){
                QDomElement rulesubbase;
                  if(!list_num.contains(0)){
                      list_num.append(0);
                       rulesubbase=doc.createElement("rulesubbase");
                      QString headdata0;
                      for(int ii=0;ii<Tablehead.at(0).count();ii++){
                          headdata0=Tablehead.at(0).at(ii)+" "+headdata0;
                      }
                      rulesubbase.setAttribute("id",0);
                      rulesubbase.setAttribute("规则表所属",headdata0);
                      list_Element.append(rulesubbase);
                      root.appendChild(rulesubbase);
                  }
                  else{
                      rulesubbase=list_Element.at(list_num.indexOf(0));
                  }
                  //QDomElement rule=doc.createElement("rule");
                  QSqlRecord  record_out=modellist0.at(0)->record(k-1);
                  this->add_div_rule(doc,record_out,rulesubbase);
        }
          else{
                int hn=0;
                for(int i=1;i<listnum.count();i++){
                  if(k<=listnum.at(i)&&k>listnum.at(i-1)){
                      hn=i;
                  }
                }
                if(hn>0){
                    QDomElement rulesubbase;
                    int hnum;
                    if(!list_num.contains(hn)){
                         list_num.append(hn);
                         rulesubbase=doc.createElement("rulesubbase");
                         QString headdata0;
                         for(int ii=0;ii<Tablehead.at(hn).count();ii++){
                             headdata0=Tablehead.at(hn).at(ii)+" "+headdata0;
                         }
                         rulesubbase.setAttribute("id",hn);
                         rulesubbase.setAttribute("规则表所属",headdata0);
                         list_Element.append(rulesubbase);
                         root.appendChild(rulesubbase);
                         hnum=list_Element.count()-1;
                    }
                    else{
                        hnum=list_num.indexOf(hn);
                        rulesubbase=list_Element.at(hnum);
                    }
                     QSqlRecord  record_out=modellist0.at(hn)->record(k-listnum.at(hn-1)-1);
                    this->add_div_rule(doc,record_out,rulesubbase);
                   }
                }
              }
    }
    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}
int viewmodel::checkrecord(QString if_text,QString then_text,QSqlTableModel*checkmodel){
    for(int i=0;i<checkmodel->rowCount();i++){
        if(if_text==checkmodel->record(i).value(1).toString()&&then_text==checkmodel->record(i).value(2).toString()){
        return i;
        }
    }
    return -1;
}
void viewmodel::addxmlnode(QDomDocument doc,QDomElement node,QString data_0,QString noname){
    QStringList list_if;
    QStringList list_if_andor;
    QStringList list_and = data_0.split("AND");
    for(int ii=0;ii<list_and.count();ii++){
        QStringList list_or=list_and.at(ii).split("OR");
        for(int j=0;j<list_or.count();j++){
              list_if.append(list_or.at(j));
              if(j+1<list_or.count()){
                  list_if_andor.append("OR");
              }
        }
        if(ii+1<list_and.count()){
            list_if_andor.append("AND");
        }
    }
    for(int iii=0;iii<list_if.count();iii++){
        QStringList list0=changeDialog::StringSplit(list_if.at(iii));
        QDomElement condition=doc.createElement(noname); //创建子元素
        node.appendChild(condition);
        condition.setAttribute("NOT_flag",list0.at(0));
        condition.setAttribute("value",list0.at(4));
        condition.setAttribute("relation",list0.at(3));
        condition.setAttribute("id",iii);
        int index=list0.at(1).indexOf(".");
        condition.setAttribute("val",list0.at(1).left(index));
        condition.setAttribute("res",list0.at(1).right(list0.at(1).length()-index)+list0.at(2));
    }
}
void viewmodel::add_div_rule(QDomDocument doc, QSqlRecord record_out,QDomElement node){
    QStringList list_or = record_out.value(1).toString().split("OR");
    QStringList list_or2 = record_out.value(2).toString().split("OR");
    int nn=0;
    for(int i=0;i<list_or.count();i++){
        for(int j=0;j<list_or2.count();j++){
            QDomElement rule=doc.createElement("rule");
            nn++;
            rule.setAttribute("id",record_out.value(0).toString()+"_"+QString::number(nn));
            QDomElement Rule_if=doc.createElement("lhs"); //创建子元素
            this->addxmlnode(doc,Rule_if,this->transRule(list_or.at(i),1),"condition");
            rule.appendChild(Rule_if);
            QDomElement Rule_then=doc.createElement("rhs"); //创建子元素
            this->addxmlnode(doc,Rule_then,this->transRule(list_or2.at(j),1),"action");
            rule.appendChild(Rule_then);
            QDomElement Rule_W=doc.createElement("wight"); //创建子元素
            QDomText text2;
            text2=doc.createTextNode(record_out.value(3).toString());
            Rule_W.appendChild(text2);
            rule.appendChild(Rule_W);
            node.appendChild(rule);
        }
    }
}
//void viewmodel::WriteXml(QString dirPath){
//     //QString saveName="mydb.sql";//保存图片名字
//     QDateTime time2 = QDateTime::currentDateTime();//获取系统现在的时间
//     QString str = time2.toString("yyyyMMdd_hhmmss"); //设置显示格式
//    //filePath = QFileDialog::getExistingDirectory("");//获取文件夹路径
//    QFile file(dirPath); //相对路径、绝对路径、资源路径都可以
//    if(!file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
//        return;
//    QDomDocument doc;
//    //写入xml头部
//    QDomProcessingInstruction instruction; //添加处理命令
//    instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
//    doc.appendChild(instruction);
//    //添加根节点
//    QDomElement root=doc.createElement("rulebase");
//    doc.appendChild(root);
//    QList<int>list_num;
//    QList<QDomElement>list_Element;
//    QMap<int, Qt::CheckState>::iterator it; //遍历map
//    for ( it = this->check_state_map.begin(); it != this->check_state_map.end(); ++it )
//    {
//        if(it.value()==Qt::Checked){
//            int k=it.key();
//            if(k<=listnum.at(0)&&k>0){
//                QDomElement rulesubbase;
//                  if(!list_num.contains(0)){
//                      list_num.append(0);
//                       rulesubbase=doc.createElement("rulesubbase");
//                      QString headdata0;
//                      for(int ii=0;ii<Tablehead.at(0).count();ii++){
//                          headdata0=Tablehead.at(0).at(ii)+" "+headdata0;
//                      }
//                      rulesubbase.setAttribute("id",0);
//                      rulesubbase.setAttribute("规则表所属",headdata0);
//                      list_Element.append(rulesubbase);
//                      root.appendChild(rulesubbase);
//                  }
//                  else{
//                      rulesubbase=list_Element.at(list_num.indexOf(0));
//                  }
//                  QDomElement rule=doc.createElement("rule");
//                  QSqlRecord  record_out=modellist0.at(0)->record(k-1);
//                  rule.setAttribute("id",record_out.value(0).toString()); //方式一：创建属性  其中键值对的值可以是各种类型
//                  QDomElement Rule_if=doc.createElement("lhs"); //创建子元素
//                  QDomText text; //设置括号标签中间的值
//                  this->addxmlnode(doc,Rule_if,this->transRule(record_out.value(1).toString(),1),"condition");
//                  //text=doc.createTextNode(record_out.value(1).toString());
//                  rule.appendChild(Rule_if);
//                  //Rule_if.appendChild(text);
//                  QDomElement Rule_then=doc.createElement("rhs"); //创建子元素
//                  this->addxmlnode(doc,Rule_then,this->transRule(record_out.value(2).toString(),1),"action");
//                  //text=doc.createTextNode(record_out.value(2).toString());
//                  //Rule_then.appendChild(text);
//                  rule.appendChild(Rule_then);
//                  QDomElement Rule_W=doc.createElement("wight"); //创建子元素
//                  text=doc.createTextNode(record_out.value(3).toString());
//                  Rule_W.appendChild(text);
//                  rule.appendChild(Rule_W);
//                  rulesubbase.appendChild(rule);
//                  //list_Element.at(0).appendChild(rule);
//        }
//          else{
//                int hn=0;
//                for(int i=1;i<listnum.count();i++){
//                  if(k<=listnum.at(i)&&k>listnum.at(i-1)){
//                      hn=i;
//                  }
//                }
//                if(hn>0){
//                    QDomElement rulesubbase;
//                    int hnum;
//                    if(!list_num.contains(hn)){
//                         list_num.append(hn);
//                         rulesubbase=doc.createElement("rulesubbase");
//                         QString headdata0;
//                         for(int ii=0;ii<Tablehead.at(hn).count();ii++){
//                             headdata0=Tablehead.at(hn).at(ii)+" "+headdata0;
//                         }
//                         rulesubbase.setAttribute("id",hn);
//                         rulesubbase.setAttribute("规则表所属",headdata0);
//                         list_Element.append(rulesubbase);
//                         root.appendChild(rulesubbase);
//                         hnum=list_Element.count()-1;
//                     }
//                    else{
//                        hnum=list_num.indexOf(hn);

//                        rulesubbase=list_Element.at(hnum);
//                    }
//                     QDomElement rule=doc.createElement("rule");
//                     QSqlRecord  record_out=modellist0.at(hn)->record(k-listnum.at(hn-1)-1);

//                     rule.setAttribute("id",record_out.value(0).toString()); //方式一：创建属性  其中键值对的值可以是各种类型

//                     QDomElement Rule_if=doc.createElement("lhs"); //创建子元素
//                     //QDomText text; //设置括号标签中间的值
//                     this->addxmlnode(doc,Rule_if,this->transRule(record_out.value(1).toString(),1),"condition");
//                     rule.appendChild(Rule_if);
//                     //Rule_if.appendChild(text);
//                     QDomElement Rule_then=doc.createElement("rhs"); //创建子元素
//                     //text=doc.createTextNode(record_out.value(2).toString());
//                     this->addxmlnode(doc,Rule_then,this->transRule(record_out.value(2).toString(),1),"action");
//                     //Rule_then.appendChild(text);
//                     rule.appendChild(Rule_then);
//                     QDomElement Rule_W=doc.createElement("wight"); //创建子元素
//                     QDomText text2;
//                     text2=doc.createTextNode(record_out.value(3).toString());
//                     Rule_W.appendChild(text2);
//                     rule.appendChild(Rule_W);
//                     rulesubbase.appendChild(rule);
//                     //list_Element.at(0)->appendChild(rule);
//                   }
//                }

//              }
//    }

//    //输出到文件
//    QTextStream out_stream(&file);
//    doc.save(out_stream,4); //缩进4格
//    file.close();
//}
//int viewmodel::checkrecord(QString if_text,QString then_text,QSqlTableModel*checkmodel){
//    for(int i=0;i<checkmodel->rowCount();i++){
//       // qDebug()<<checkmodel->record(i).value(1)<<checkmodel->rowCount();
//        if(if_text==checkmodel->record(i).value(1).toString()&&then_text==checkmodel->record(i).value(2).toString()){

//        return i;
//        }
//    }
//    // qDebug()<<"b"<<if_text<<then_text;
//    return -1;
//}
//void viewmodel::addxmlnode(QDomDocument doc,QDomElement node,QString data_0,QString noname){
//    QStringList list_if;
//    QStringList list_if_andor;
//    QStringList list_and = data_0.split("AND");
//    for(int ii=0;ii<list_and.count();ii++){
//        QStringList list_or=list_and.at(ii).split("OR");
//        for(int j=0;j<list_or.count();j++){
//              list_if.append(list_or.at(j));
//              if(j+1<list_or.count()){
//                  list_if_andor.append("OR");
//              }
//        }
//        if(ii+1<list_and.count()){
//            list_if_andor.append("AND");
//        }
//    }
//    for(int iii=0;iii<list_if.count();iii++){
//        QStringList list0=changeDialog::StringSplit(list_if.at(iii));
//        QDomElement condition=doc.createElement(noname); //创建子元素
//        node.appendChild(condition);
//        condition.setAttribute("ANDOR","");
//        condition.setAttribute("NOT_flag",list0.at(0));
//        condition.setAttribute("value",list0.at(4));
//        condition.setAttribute("relation",list0.at(3));
//        condition.setAttribute("id",iii);
//        int index=list0.at(1).indexOf(".");
//        condition.setAttribute("val",list0.at(1).left(index));
//        condition.setAttribute("res",list0.at(1).right(list0.at(1).length()-index)+list0.at(2));
//        //condition.setAttribute("res",list0.at(1)+list0.at(2));
//    }
//}
