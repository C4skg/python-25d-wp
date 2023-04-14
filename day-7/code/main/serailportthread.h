#ifndef SERAILPORTTHREAD_H
#define SERAILPORTTHREAD_H

#include <QThread>
#include "./smarthome/serialportreceive.h"
#include "./smarthome/qextserialport.h"
class serailportthread : public QThread
{
    Q_OBJECT
public:
    explicit serailportthread();
    
signals:
    void evt_serial_receive(QByteArray);
private:
    QextSerialPort *myCom;
    SerialPortReceive *porthandle;
public slots:
    void run();
    void onRead();
    void send(QByteArray ba);
    void mysleep(int a);
};

#endif // SERAILPORTTHREAD_H
