#ifndef SQL_H
#define SQL_H

#include <QObject>
#include <QSqlDatabase>
#include <QtSql>
#include "systemConfig.h"

class Sql : public QObject
{
    Q_OBJECT
public:
    explicit Sql(QObject *parent = 0);

  /*函数功能：链接数据库，若数据库存在则打开数据库，否则新建数据库并打开
    函数参数：dbame：数据库名
    函数返回：若操作成功则返回ture，否则返回false*/
    bool sqlConnect(QString dbName);
  /*函数功能：执行数据库的增，删，改操作
    函数参数：sql：sql语句
    函数返回：若操作成功则返回ture，否则返回false*/
    bool sqlExec(QString sql);
  /*函数功能：执行数据库的查询操作
    函数参数：sql：sql语句
    函数返回：若操作成功则返回QVariant类型数据，可将其转为需要的类型*/
    QVariant sqlQuery(QString sql);
  /*函数功能：执行数据库的查询整张表，并将表存入临时
    函数参数：tb：表名
    函数返回：若操作成功则返回tb表*/
    QSqlTableModel* sqlTableMode(QString tb);
  /*函数功能：执行删除数据表
    函数参数：tb：表名
    函数返回：若操作成功则返回ture，否则返回false*/
    bool sqlDeleteTable(QString tb);
  /*函数功能：执行清空数据表，并将自增长字段重新置0
    函数参数：tb：表名
    函数返回：若操作成功则返回ture，否则返回false*/
    bool sqlClearTable(QString tb);
  /*函数功能：查询数据表是否在数据库中存在
    函数参数：tb：表名
    函数返回：若操作成功则返回ture，否则返回false*/
    bool sqlQueryTable(QString tb);
  /*函数功能：关闭数据库
    函数参数：无
    函数返回：若操作成功则返回ture，否则返回false*/
    void sqlDisconnect();
    /**************************************************************/
private:
    QSqlDatabase db;
signals:
    
public slots:
    
};

#endif // SQL_H
