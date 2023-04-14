#include "serailportthread.h"

serailportthread::serailportthread()
{
    moveToThread(this);
}

void serailportthread::run()
{
    PortSettings set = {BAUD115200,DATA_8,PAR_NONE,STOP_1,FLOW_OFF};
    myCom = new QextSerialPort("/dev/ttyUSB1",set);
    if(myCom->open(QIODevice::ReadWrite)){
        connect(myCom,SIGNAL(readyRead()),this,SLOT(onRead()));
        porthandle = new SerialPortReceive(this);
        connect(porthandle,SIGNAL(byteFinish(QByteArray)),this,SIGNAL(evt_serial_receive(QByteArray)));
        qDebug("ok");
    }else qDebug("no");
    this->exec();
}

void serailportthread::onRead()
{
    QByteArray ba = myCom->readAll();
    porthandle->dataHandle(ba);
}

void serailportthread::send(QByteArray ba)
{
    myCom->flush();
    myCom->write(ba);
}

void serailportthread::mysleep(int a)
{
    msleep(a);
}
