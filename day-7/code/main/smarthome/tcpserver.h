#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);
private:
  /*函数功能：数据发送，接受到配置命令后，返回执行状态
    函数参数：ba:Success成功，Failure失败
    函数返回：无*/
    void socket_back_state(QString type,QString state);
private://私有对象
    QTcpSocket * socket_client;
private slots://私有槽函数
    void new_client_recieved();
    void client_closed();
    void new_data_recieved();
    void displayError(QAbstractSocket::SocketError socketError);
signals:
    void evt_configBoardId();
};

#endif // TCPSERVER_H
