#ifndef SERIALPORTRECEIVE_H
#define SERIALPORTRECEIVE_H

#include <QObject>

class SerialPortReceive : public QObject
{
    Q_OBJECT
public:
    explicit SerialPortReceive(QObject *parent = 0);
    void dataHandle(QByteArray temp);
    int dataHandleFlag;
private:
    QByteArray data;
    int dataLength,frameLength;
    int flag;
signals:
    void byteFinish(const QByteArray &);
signals:
    
public slots:
    
};

#endif // SERIALPORTRECEIVE_H
