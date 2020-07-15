#include "connectionpool.h"
#include<iostream>
#include<QFile>
#include<QFileDialog>
QMutex ConnectionPool::mutex;
QWaitCondition ConnectionPool::waitConnection;
ConnectionPool* ConnectionPool::instance = NULL;
ConnectionPool::ConnectionPool(){
    //创建数据库连接的信息
    hostName = "127.0.0.1";
    databaseName = "zhy";
    username = "root";
    password = "zhanghouyuan";
    databaseType = "QMYSQL";
    testOnBorrow = true;
    testOnBorrowSql = "select 1";
    maxWaitTime = 1000;
    waitInterval = 200;
    maxConnectionCount = 5;
}

//读取配置文件
void ConnectionPool::getini(QString iniFilePath)
{
    //QString filePath = QFileDialog::getOpenFileName(this,QString("open file")," ", QString("ini files (*.ini);;ALL files (*.*)"));
    //QString iniFilePath = "F:/QT_Project_201508/TestConfigFile/config_files/MyINI.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    this->hostName=settings.value("hostName").toString();
    this->databaseName=settings.value("databaseName").toString();
     this->databaseType=settings.value("databaseType").toString();
    qDebug()<<settings.value("hostName").toString();

}
//写入配置文件
void ConnectionPool::setini(QString iniFilePath)
{
    //QString iniFilePath = "F:/QT_Project_201508/TestConfigFile/config_files/MyINI.ini";
    QSettings settings(iniFilePath,QSettings::IniFormat);
    settings.setValue("hostName","127.0.0.1");
    settings.setValue("databaseName","zhy");
    settings.setValue("databaseType","QMYSQL");
}

void ConnectionPool::setnamepssw(QString name,QString pssw,QString rulename){

    username=name;
    password=pssw;
    databaseName=rulename;
}
ConnectionPool::~ConnectionPool(){
    //销毁连接池的时候删除所有连接
    foreach(QString connectionName, usedConnectionNames){
        QSqlDatabase::removeDatabase(connectionName);
    }
    foreach(QString connectionName, unusedConnectionNames){
        QSqlDatabase::removeDatabase(connectionName);
    }
}
ConnectionPool* ConnectionPool::getInstance(){
    if(NULL == instance){
        QMutexLocker locker(&mutex);

        if(NULL == instance){
            instance = new ConnectionPool;
        }
    }

    return instance;
}

void ConnectionPool::release(){
    QMutexLocker locker(&mutex);
    delete instance;
    instance = NULL;
}

QSqlDatabase ConnectionPool::openConnection(QString username,QString passw,QString name){
    ConnectionPool *pool;

    pool = ConnectionPool::getInstance();
    QString connectionName;
    QMutexLocker locker(&mutex);

    if(name.isEmpty()||passw.isEmpty()||username.isEmpty()){
    }
    else{
        pool->setnamepssw(username,passw,name);
    }
    //pool->getini(infilepath);
    //已创建连接数
    int connectionCount = pool->unusedConnectionNames.size() +
                          pool->usedConnectionNames.size();

    //连接已经用完 ,等待 waitInterval毫秒,最长等待maxWaitTime
    for(int i = 0; i < pool->maxWaitTime && pool->unusedConnectionNames.size()==0
        && connectionCount == pool->maxConnectionCount; i += pool->waitInterval){
        waitConnection.wait(&mutex, pool->waitInterval);

        //重新计算已经创建的连接数
        connectionCount = pool->unusedConnectionNames.size() +
                          pool->usedConnectionNames.size();
    }

    if(pool->unusedConnectionNames.size() >0 ){
        //有已经回收的连接进行复用
        connectionName = pool->unusedConnectionNames.dequeue();
    }else if(connectionCount < pool->maxConnectionCount){
        //没有已经回收的连接,但是连接数还未达到最大,则创建新的连接
        connectionName = QString("Connection-%1").arg(connectionCount + 1);
    }else{
        //已经达到最大连接数
         qDebug()<<"Cannot create more connections";
        return QSqlDatabase();
    }

    //创建连接
    QSqlDatabase db = pool->createConnection(connectionName);

    //将有效的连接放入usedConnectionNames中
    if(db.isOpen()){
        pool->usedConnectionNames.enqueue(connectionName);
    }
    return db;
}

QSqlDatabase ConnectionPool::openConnection_2(QString infilepath,QString username,QString passw){
    ConnectionPool *pool;
    pool = ConnectionPool::getInstance();
    QString connectionName;
    QMutexLocker locker(&mutex);

    pool->getini(infilepath);
    if(passw.isEmpty()||username.isEmpty()){
    }
    else{
        pool->username=username;
        pool->password=passw;
    }
  //  qDebug()<<pool->hostName<<pool->databaseName;
    //已创建连接数
    int connectionCount = pool->unusedConnectionNames.size() +
                          pool->usedConnectionNames.size();

    //连接已经用完 ,等待 waitInterval毫秒,最长等待maxWaitTime
    for(int i = 0; i < pool->maxWaitTime && pool->unusedConnectionNames.size()==0
        && connectionCount == pool->maxConnectionCount; i += pool->waitInterval){
        waitConnection.wait(&mutex, pool->waitInterval);

        //重新计算已经创建的连接数
        connectionCount = pool->unusedConnectionNames.size() +
                          pool->usedConnectionNames.size();
    }

    if(pool->unusedConnectionNames.size() >0 ){
        //有已经回收的连接进行复用
        connectionName = pool->unusedConnectionNames.dequeue();
    }else if(connectionCount < pool->maxConnectionCount){
        //没有已经回收的连接,但是连接数还未达到最大,则创建新的连接
        connectionName = QString("Connection-%1").arg(connectionCount + 1);
    }else{
        //已经达到最大连接数
        // qDebug()<<"Cannot create more connections";
        return QSqlDatabase();
    }

    //创建连接
    QSqlDatabase db = pool->createConnection(connectionName);

    //将有效的连接放入usedConnectionNames中
    if(db.isOpen()){
        pool->usedConnectionNames.enqueue(connectionName);
    }
    return db;
}

void ConnectionPool::closeConnection(QSqlDatabase connection){
    ConnectionPool* pool = ConnectionPool::getInstance();
    QString connectionName = connection.connectionName();

    //如果是我们创建的连接,从used中删除,加入unused中
    if(pool->usedConnectionNames.contains(connectionName)){
        QMutexLocker loscker(&mutex);
        pool->usedConnectionNames.removeOne(connectionName);
        pool->unusedConnectionNames.enqueue(connectionName);
        waitConnection.wakeOne();
    }
}

QSqlDatabase ConnectionPool::createConnection(const QString &connectionName){
    //连接已经创建过了,复用它
    if(QSqlDatabase::contains(connectionName)){
        QSqlDatabase db1 = QSqlDatabase::database(connectionName);

        //重新连接数据库
        if(testOnBorrow){
            //返回连接前访问数据库,如果断开连接,则需要重新连接
            qDebug()<<"Test connection on borrow,excute:" <<testOnBorrowSql
                   <<", for"<< connectionName;
            QSqlQuery query(testOnBorrowSql, db1);

            if(query.lastError().type() != QSqlError::NoError && !db1.open()){
                qDebug()<<"Open database error:"<<db1.lastError().text();
                return QSqlDatabase();
            }
        }
        return db1;
    }
    //创建一个新的连接
    QSqlDatabase db = QSqlDatabase::addDatabase(databaseType,connectionName);
    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(username);
    db.setPassword(password);

    if(!db.open()){
        qDebug()<<"Open database error:"<<db.lastError().text();
        return QSqlDatabase();
    }

    return db;
}
