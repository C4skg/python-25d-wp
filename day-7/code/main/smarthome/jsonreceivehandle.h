#ifndef JSONRECEIVEHANDLE_H
#define JSONRECEIVEHANDLE_H

#include <QObject>
#include <QtScript>
#include "sql.h"

class JsonReceiveHandle : public QObject
{
    Q_OBJECT
public:
    explicit JsonReceiveHandle(QObject *parent = 0);
public:
  /*函数功能：接收数据处理
    函数参数：ba:接受的数据
    函数返回：返回处理结果*/
    int json_receive_handle(QByteArray ba);
private:
     //QByteArray decryptToStr(QByteArray in);
public:
     QString sensorType;//传感器类型，json字段SenSorType的值
     unsigned int command;//命令，json字段Command值
     unsigned int cmdCode ; //命令码
     unsigned int channel;//通道
     unsigned int boardId;//板号
     QString clientIp;//ClientIP字段的值
     QString types; //命令类型
     QString sysTime;//系统时间
signals:
    
public slots:
    
};

#endif // JSONRECEIVEHANDLE_H
