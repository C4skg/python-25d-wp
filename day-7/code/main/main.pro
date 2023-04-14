#-------------------------------------------------
#
# Project created by QtCreator 2021-11-20T21:09:25
#
#-------------------------------------------------

QT       += core gui sql network script
LIBS +=./lib-SmartHomeGateway-X86-V5.so

TARGET = main
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    smarthome/qextserialport.cpp \
    smarthome/qextserialport_unix.cpp \
    serailportthread.cpp \
    login.cpp \
    ruanjianpan.cpp \
    sign.cpp \
    zhuce.cpp \
    huatu.cpp \
    rz.cpp

HEADERS  += dialog.h \
    smarthome/cjson.h \
    smarthome/jsonreceivehandle.h \
    smarthome/jsonsendhandle.h \
    smarthome/qextserialport.h \
    smarthome/qextserialport_global.h \
    smarthome/qextserialport_p.h \
    smarthome/serialdatahandle.h \
    smarthome/serialportreceive.h \
    smarthome/sql.h \
    smarthome/systemConfig.h \
    smarthome/tcpclientthread.h \
    smarthome/tcpserver.h \
    smarthome/VariableDefinition.h \
    serailportthread.h \
    login.h \
    ruanjianpan.h \
    sign.h \
    zhuce.h \
    huatu.h \
    rz.h

FORMS    += dialog.ui \
    login.ui \
    ruanjianpan.ui \
    sign.ui \
    zhuce.ui \
    huatu.ui \
    rz.ui

RESOURCES += \
    image.qrc
