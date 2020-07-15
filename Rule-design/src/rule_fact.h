#ifndef RULE_FACT_H
#define RULE_FACT_H
#include<QSqlTableModel>
#include<QString>
class Rule_fact
{
public:
    Rule_fact();
    ~Rule_fact();
    //void setfactmodel();
    void addfact(QString);
    int findfact(QString);
    QString findfactID(int);
    int findfactIndex(int);
    void removefact(int);
    QSqlTableModel *model_fact;
    void submit();
    //int lastID;
};
#endif // RULE_FACT_H
