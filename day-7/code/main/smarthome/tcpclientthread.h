#ifndef TCPCLIENTTHREAD_H
#define TCPCLIENTTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include "sql.h"
#include <QTimer>


class TcpClientThread : public QThread
{
    Q_OBJECT
public:
    explicit TcpClientThread(QObject *parent = 0);
public:
  /*函数功能：数据发送，接受到配置命令后，返回执行状态
    函数参数：ba:Success成功，Failure失败;clientIp:接收时收到的clientIp,表示需要返回的客户端
    函数返回：无*/
    void backState(QString state,QString & clientIp);
  /*函数功能：传感器数据主动上传
    函数参数：key:json字段的key值；value:json字段的value值
    函数返回：无*/
    void upload(QString boardId,QString type,QString cmdCode,QString value);
   //void upload(QString & key,QString & value,QString & nextValue);
signals:
  /*函数功能：接收服务端数据处理后，若数据处理后为设备控制，则向主线程发出信号
    函数参数：type:传感器类型，详情见传感器字段定义；command:控制命令，详情见协议字段表
    函数返回：无*/
    void evt_socket_receive(unsigned int boardId,QString type,unsigned int command,unsigned int cmdCode,unsigned int channel);
public slots:
  /*函数功能：断开socket链接，并退出客户端线程
    函数参数：无
    函数返回：无*/
    void slot_threadQuit();
public:
     QString serverIP; //链接服务器的ip，默认从数据库获取，也可在主线程中对其进行设置
     bool getTcpClientFlag(){return tcpClientFlag;}
     void setTcpClentFlag(bool b){tcpClientFlag =b;}
private://私有对象
     QTcpSocket *tcpSocket;
     bool tcpClientFlag;
     QTimer *heatBeatTimer;
private://私有函数
     void run();

private slots: //私有槽函数
     void slot_receive();
     void slot_breakoff(QAbstractSocket::SocketError);
     void slot_heatBeat();


};
#endif // TCPCLIENTTHREAD_H
