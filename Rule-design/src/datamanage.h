#ifndef DATAMANAGE_H
#define DATAMANAGE_H
#include"connectionpool.h"

class datamanage
{
public:
    datamanage();

    static bool addtable(QSqlDatabase,QString);
    static bool deltable(QSqlDatabase,QString);
    //QSqlDatabase db;
//private:
    //QString inst="insert into";

};

#endif // DATAMANAGE_H
