#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H
#include <QtSql>
#include <QQueue>
#include <QString>
#include <QMutex>
#include <QMutexLocker>
#include <QSettings>

class ConnectionPool
{
public:
    //ConnectionPool();
    void release();//关闭所有的数据库连接
    static QSqlDatabase openConnection(QString name,QString passw,QString username);//获取数据库连接
    static QSqlDatabase openConnection_2(QString,QString,QString);
    static void closeConnection(QSqlDatabase connection);//释放数据库连接回连接池
    void setnamepssw(QString name,QString pssw,QString rulename);
    void getini(QString);
    static void setini(QString);
    ~ConnectionPool();
private:
    static ConnectionPool* getInstance();
    ConnectionPool();
    ConnectionPool(const ConnectionPool &other);
    ConnectionPool& operator=(const ConnectionPool &other);
    QSqlDatabase createConnection(const QString &connectionName);//创建数据库连接

    QQueue<QString> usedConnectionNames;//已使用的数据库连接名
    QQueue<QString> unusedConnectionNames;//未使用的数据库连接名

    //数据库信息
    QString hostName;
    QString databaseName;
    QString username;
    QString password;
    QString databaseType;

    bool testOnBorrow;//取得连接的时候验证连接是否有效
    QString testOnBorrowSql;//测试访问数据库的SQL

    int maxWaitTime;//获取连接的最大等待时间
    int waitInterval;//尝试获取连接时的等待时间
    int maxConnectionCount;//最大连接数

    static QMutex mutex;
    static QWaitCondition waitConnection;
    static ConnectionPool *instance;
};

#endif // CONNENTIONPOOL_H
