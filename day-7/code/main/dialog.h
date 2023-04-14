#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include "./smarthome/serialdatahandle.h"
#include "./smarthome/tcpclientthread.h"
#include "serailportthread.h"
#include <QList>
#include <QMap>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QDateTime>
#include "ruanjianpan.h"
#include "huatu.h"
#include "rz.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private:
    Ui::Dialog *ui;
    serailportthread serial;
    SerialDataHandle handle;
    TcpClientThread client;
    QTimer readTimer,controlTimer,styleTimer,modeTimer;
    ruanjianpan board;
    int readNum;
    struct buttonObj{
        QString name;
        QString type;
        int id;
        QPushButton *button;
        int ch;
        bool state;
        bool nowState;
    };
    struct labelObj{
        int id;
        QString type;
        QLabel *label;
        QString primary;
    };
    QList<labelObj*> labelList;
    QMap<QString,buttonObj*> eleMap;
    enum MODE{NONE,GETUP,SLEEP,MOVIE,LINKAGE,AF}mode;
    QLabel *drawLabel;
private slots:
    void AndroidControl(uint id,QString type,uint cmd,uint cmdcode,uint ch);
    void serial_receive(QByteArray ba);
    void receive_data(QString id,QString type,QString asc,QString value);
    void readSlot();
    void addLabel(int id,QString type,QLabel* label);
    void addButton(QString name,QString type,int id,QPushButton *button,int ch=CHANNEL_ALL);
    void controlSlot();
    void styleSlot();
    void modeSlot();
    bool eventFilter(QObject *obj, QEvent *e);
    void receive_board(QString text);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_ws_bt_sd_clicked();
    void on_ws_bt_mj_clicked();
    void on_ws_bt_kt_clicked();
    void on_ws_bt_jsq_clicked();
    void on_kt_bt_sd_clicked();
    void on_kt_bt_ct_clicked();
    void on_ws_bt_sd_10_clicked();
    void on_ws_bt_sd_9_clicked();
    void on_kt_bt_ds_clicked();
    void on_kt_bt_dvd_clicked();
    void on_cf_bt_sd_clicked();
    void on_cf_bt_bjd_clicked();
    void on_cf_bt_fs_clicked();
    void on_ws_mode_getUp_clicked();
    void on_ws_mode_sleep_clicked();
    void on_kt_mode_movie_clicked();
    void on_kt_mode_switch_clicked();
    void on_cf_mode_af_clicked();
    void on_bt_log_clicked();
};

#endif // DIALOG_H
