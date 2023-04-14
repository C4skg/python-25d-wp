#ifndef SERIALDATAHANDLE_H
#define SERIALDATAHANDLE_H

#include <QObject>
#include <QMap>
#include <QList>
#include "sql.h"
#include <QTime>
#include "VariableDefinition.h"


class SerialDataHandle : public QObject
{
    Q_OBJECT
public:
    explicit SerialDataHandle(QObject *parent = 0);
/*****************************外部接口**********************************************/
    QByteArray sendingDataHandle(unsigned char opcodes, unsigned boardId, unsigned int *pCommand,int len); // 串口发送数据处理
    void cmdArryHandle(unsigned int *pCmd,unsigned int type,unsigned int cmd,unsigned int channel); //数组处理
    void init(); //初始化设备信;
/*****************属性*************************/
    QMap<QString ,unsigned int> sensorTypeToBoardIdMap; //传感器类型对应板号

    typedef struct{
        QString shortAddress;
        QString deviceType;
        QString mac;
    }deviceInfoStruct;
    deviceInfoStruct devInfoStruct;
    QMap<unsigned int,deviceInfoStruct> deviceInfoMap; // 设备信息map
private:
/****************************************方法*************************************************************/
    unsigned short CalculateCrc(unsigned char *pData,unsigned long Len);
    QString deviceInfoToString(int i);
    void deviceInfoHandle();       //设备信息处理
    void deviceStateHandle();      //设备状态数据处理
    void dataHandle(unsigned int boardId, int type=0); // 设备状态处理
    void boardIdSensorTypeHandle(unsigned int boardId, unsigned int deviceType);
    QString selectSensorType(unsigned int deviceType);
private:
    typedef struct{
        unsigned int dataHead[2];                //帧首
        unsigned int frameLength[2];		    //帧长
        unsigned int statusCode[2];			 	//状态码
        unsigned int shortAddress[2];			//短地址
        unsigned int RSSI;						//RSSI值
        unsigned int LQI;						//LQI值
        unsigned int dataLength[2];				//数据长度
        unsigned int data[512];					//数据内容
        unsigned int socketId[2];               //通信id
        unsigned int crc[2];                    //校验位
    }receiveDataStruct;
    receiveDataStruct receiveData;
/*****************属性*************************/

    QMap<QString,unsigned int> addressToBoardIdMap;  //设备短地址对应板号

    typedef struct{
        QString value;
        QString valueNext;
    }deviceStateStruct;
    deviceStateStruct devStateStruct;
    QMap<unsigned int,deviceStateStruct> devStateMap; // 设备状态map

    QMap<unsigned int,QString> BoardIdTosensorTypeMap; //板号对应传感器类型

signals:
    void evt_deviceState(const QString &,const QString &,const QString & ,const QString & ); //传感器类型，状态上传

public slots:
/*****************************外部接口**********************************************/
   void receive(const QByteArray & str);
};

#endif // SERIALDATAHANDLE_H
