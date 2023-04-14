#ifndef CJSON_H
#define CJSON_H

#include <QMap>
#include <QVariant>
#include <stdint.h>

class CJSon
{
public:
    enum ValueTypeFlag { vtfObject=0, vtfString=1,vtfInt=2, vtfDouble=3, vtfBool=4, vtfDateTime=5, vtfNull=6,vtfNo=7, vtfArray=99 };
    CJSon();
    ~CJSon();
    static QString quote(const QString& Text);
public:
    void add(const QString &key, const QString &value ,int type= vtfString);
    QString toJsonString();
    QString jsonKey(const QString & key);
    QString jsonValue(const QString & value,int type);
    void toArraryChild();
    QString addArrary();
    QByteArray serialize(QString str);
    QByteArray encryptionToHex(QByteArray out);
protected:

    typedef struct{
        QString m_value;
        int m_type;
    }jsonValueStruct;

    QMap <QString ,jsonValueStruct> m_jsonMap;

    QList<QString> m_jsonList;

signals:
    
public slots:
    
};

#endif // CJSON_H
