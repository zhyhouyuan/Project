#include "datamanage.h"

datamanage::datamanage()
{
   //this->db=ConnectionPool::openConnection();
}
//void datamanage::insertdata(QString *datestr,QString *timestr){
//        QSqlQuery query(db);
////           QString datestr = ui->dateEdit->dateTime().toString("dd-MM-yyyy");
////           QString timestr = ui->dateEdit->time().toString("hh:mm:ss");
//        QString sql=QString("select *from hang1");
//        query.exec(sql);
//        //qDebug()<<"zzzz";
//        if(query.numRowsAffected())
//        {
//        QString savesql = QString("insert into hang1(hight,wight)");
//        savesql += QString(" values('%1','%2');").arg(*datestr)
//                .arg(*timestr);
//        qDebug()<<savesql;
//        bool ok=query.exec(savesql);
//        if(ok){
////              QMessageBox::about(NULL, "Save", "save new database success");
//             qDebug()<<" save success";
//              }
//          else{
////               QMessageBox::about(NULL, "Save", "error save new database");
//             qDebug()<<"save error";
//              }
//        }
//}
//void datamanage::deletedata(QString*date){
//    QSqlQuery query(db);
//    QString sql=QString("select *from hang1");
//    query.exec(sql);
//    if(query.numRowsAffected())
//    {
//    QString savesql = QString("delete from hang1");
//    savesql += QString("where id=%1").arg(*date);
//    qDebug()<<savesql;
//    bool ok=query.exec(savesql);
//    if(ok){
//         qDebug()<<" del success";
//          }
//      else{
//         qDebug()<<"del error";
//          }
//    }
//}
//void datamanage::updata(QString ID){
//    QSqlQuery query(db);
//    QString sql=QString("select *from hang1");
//    query.exec(sql);
//    if(query.numRowsAffected())
//    {
//    QString savesql = QString("delete from hang1");
//    savesql += QString("where id=%1").arg(ID);
//    qDebug()<<savesql;
//    bool ok=query.exec(savesql);
//    if(ok){
//         qDebug()<<" del success";
//          }
//      else{
//         qDebug()<<"del error";
//          }
//    }
//}

bool datamanage::addtable(QSqlDatabase db,QString name){
    QSqlQuery query(db);
    QString creattable=QString("CREATE TABLE %1(id int not null primary key,if_1 char(255),then_1 char(255),weight_1 char(30));").arg(name);


    bool flag=query.exec(creattable);

    //qDebug()<<flag;

    return flag;
}
bool datamanage::deltable(QSqlDatabase db,QString name){
    QSqlQuery query(db);
    QString deletetable=QString("DROP TABLE %1").arg(name);
    bool flag=query.exec(deletetable);
    return flag;
}
