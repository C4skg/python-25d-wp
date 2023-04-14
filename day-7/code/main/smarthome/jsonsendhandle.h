#ifndef JSONSENDHANDLE_H
#define JSONSENDHANDLE_H

#include <QObject>
#include "cjson.h"
#include "sql.h"
#include <QNetworkInterface>

class JsonSendHandle : public QObject
{
    Q_OBJECT
public:
    explicit JsonSendHandle(QObject *parent = 0);
public:
  /*函数功能：发送数据处理函数，将需要发送的数据变为json格式，并用aes加密
    函数参数：state:包括Success返回成功，Failure返回失败;clientIp:接收时收到的clientIp,表示需要返回的客户端
    函数返回：aes加密后的json格式数据*/
    QByteArray sendHandle(QString type,QString & state,QString clientIp="");
  /*函数功能：所有传感器数据主动上传
    函数参数：key:json字段的key值；value:json字段的value值
    函数返回：aes加密后的json格式数据*/
    QByteArray uploadHandle(QString & boardId,QString & type,QString & cmdCode,QString & value);
  /*函数功能：向客户端返回网关信息
    函数参数：无
    函数返回：aes加密后的json格式数据*/
    QByteArray gatewayInfo();
  /*函数功能：向客户端返回zigbee节点板号信息
    函数参数：无
    函数返回：aes加密后的json格式数据*/
    QByteArray zigbeeInfo();
private:
    void getAdapterInfoWithQt() ;
};

#endif // JSONSENDHANDLE_H
