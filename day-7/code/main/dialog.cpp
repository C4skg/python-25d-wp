#include "dialog.h"
#include "ui_dialog.h"
//huatu
QString name;
float char_value;

extern QStringList logList;
//卧室
volatile float ws_ill_value;
volatile float ws_hum_value;
//客厅联动传参
volatile float temp_value;
volatile float hum_value;
volatile float ap_value;
volatile float ill_value;
volatile float smk_value;
volatile float co_value;
volatile float pm_value;
//客厅联动传参
//厨房
volatile float cf_smk_value;
volatile float cf_gas_value;
QMap<QString,QString> companyMap;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //to => start
    ws_ill_value = ws_hum_value = 0;
    temp_value = hum_value = ap_value = ill_value = smk_value = co_value = pm_value = 0;
    cf_smk_value = cf_gas_value = 0;
    mode = NONE;
    char_value = 0;
    ui->kt_mode_value->installEventFilter(this);
    connect(&board,SIGNAL(send_data(QString)),this,SLOT(receive_board(QString)));
    logList.clear();
    ui->tabWidget->setCurrentIndex(0);
    readNum = 0;
    client.setTcpClentFlag(false);
    client.serverIP = "192.168.5.2";
    client.start();
    connect(&client,SIGNAL(evt_socket_receive(uint,QString,uint,uint,uint)),this,SLOT(AndroidControl(uint,QString,uint,uint,uint)));
    serial.start();
    connect(&serial,SIGNAL(evt_serial_receive(QByteArray)),this,SLOT(serial_receive(QByteArray)));
    connect(&handle,SIGNAL(evt_deviceState(QString,QString,QString,QString)),this,SLOT(receive_data(QString,QString,QString,QString)));

    companyMap.insert("光照度","Lux");
    companyMap.insert("温度","℃");
    companyMap.insert("湿度","%");
    companyMap.insert("燃气","nm³");
    companyMap.insert("CO2","ppm");
    companyMap.insert("气压","pa");
    companyMap.insert("PM2.5","μg/m³");
    companyMap.insert("烟雾","ppm");

    //add sensor+device
    //ws
    addLabel(temp_id,TEMP_SERVE,ui->ws_wd);
    addLabel(temp_id,HUM_SERVE,ui->ws_sd);
    addLabel(ill_id,ILL_SERVE,ui->ws_gz);
    addButton("卧室射灯",RELAY_SERVE,lamp_id,ui->ws_bt_sd);
    addButton("卧室门禁",DC_SERVE,dc_id,ui->ws_bt_mj);
    addButton("卧室空调",INFRARED_SERVE,air_hum_id,ui->ws_bt_kt,1);
    addButton("卧室加湿器",INFRARED_SERVE,air_hum_id,ui->ws_bt_jsq,3);

    //kt
    addLabel(temp_id_2,TEMP_SERVE,ui->kt_wd);
    addLabel(temp_id_2,HUM_SERVE,ui->kt_sd);
    addLabel(ap_id,AP_SERVE,ui->kt_qy);
    addLabel(ill_id_2,ILL_SERVE,ui->kt_gz);
    addLabel(smk_id,SMK_SERVE,ui->kt_yw);
    addLabel(co2_id,CO2_SERVE,ui->kt_co);
    addLabel(pm_id,PM25_SERVE,ui->kt_pm);
    addButton("客厅射灯",RELAY_SERVE,lamp_id_2,ui->kt_bt_sd);
    addButton("客厅窗帘",CT_SERVE,ct_id,ui->kt_bt_ct);
    addButton("客厅电视",INFRARED_SERVE,tv_dvd_id,ui->kt_bt_ds,1);
    addButton("客厅DVD",INFRARED_SERVE,tv_dvd_id,ui->kt_bt_dvd,3);

    //cf
    addLabel(gas_id,GAS_SERVE,ui->cf_rq);
    addLabel(smk_id_2,SMK_SERVE,ui->cf_yw);
    addButton("厨房射灯",RELAY_SERVE,lamp_id,ui->cf_bt_sd);
    addButton("厨房报警灯",RELAY_SERVE,wl_id,ui->cf_bt_bjd);
    addButton("厨房风扇",RELAY_SERVE,fan_id,ui->cf_bt_fs);
    //QTimer
    connect(&readTimer,SIGNAL(timeout()),this,SLOT(readSlot()));
    connect(&controlTimer,SIGNAL(timeout()),this,SLOT(controlSlot()));
    connect(&styleTimer,SIGNAL(timeout()),this,SLOT(styleSlot()));
    connect(&modeTimer,SIGNAL(timeout()),this,SLOT(modeSlot()));
    modeTimer.start(1000);
    controlTimer.start(300);
    styleTimer.start(100);
    readTimer.start(300);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::AndroidControl(uint id, QString type, uint cmd, uint cmdcode, uint ch)
{
    uint qwe[9] = {0,0,0x01,0xee,0x03,0,cmdcode,cmd,ch};
    if(type==CT_SERVE){
        qwe[7] = SWITCH_ON;
        serial.send(handle.sendingDataHandle(CONTROL,id,qwe,9));
        serial.mysleep(300);
        qwe[7] = SWITCH_OFF;
    }else if(type==DC_SERVE){
        qwe[2] = 0x0a;
        qwe[8] = CHANNEL_1;
    }else if(type==INFRARED_SERVE){
        qwe[2] = 0x0b;
        qwe[7] = ch&0xf;
        qwe[8] = (ch>>8)&0xf;
    }
    serial.send(handle.sendingDataHandle(CONTROL,id,qwe,9));
}

void Dialog::serial_receive(QByteArray ba)
{
    handle.receive(ba);
}

void Dialog::receive_data(QString id, QString type, QString asc, QString value)
{
    if(client.getTcpClientFlag()) client.upload(id,type,asc,value);
    int boardId = id.toInt();
    foreach(labelObj *obj,labelList){
        if(boardId == obj->id && obj->type == type){
            obj->label->setText(obj->primary+" "+value);
        }
    }
    //客厅
    if(boardId == hi_id && type == HI_SERVE){
        ui->kt_hi->setText(QString("%1人").arg(value.toInt()?"有":"无"));
    }else if(boardId == temp_id_2 && type == TEMP_SERVE){
        temp_value = value.toFloat();
    }else if(boardId == temp_id_2 && type == HUM_SERVE){
        hum_value = value.toFloat();
    }else if(boardId == ap_id && type == AP_SERVE){
        ap_value = value.toFloat();
    }else if(boardId == ill_id_2 && type == ILL_SERVE){
        ill_value = value.toFloat();
    }else if(boardId == smk_id && type == SMK_SERVE){
        smk_value = value.toFloat();
    }else if(boardId == co2_id && type == CO2_SERVE){
        co_value = value.toFloat();
    }else if(boardId == pm_id && type == PM25_SERVE){
        pm_value = value.toFloat();
    }
    //卧室
    if(boardId == ill_value && type == ILL_SERVE){
        ws_ill_value = value.toFloat();
    }else if(boardId == temp_id && type == HUM_SERVE){
        ws_hum_value = value.toFloat();
    }
    //厨房
    if(boardId == gas_id && type == GAS_SERVE){
        cf_gas_value = value.toFloat();
    }else if(boardId == smk_id_2 && type ==SMK_SERVE){
        cf_smk_value = value.toFloat();
    }
}

void Dialog::readSlot()
{
    uint qwe[3] = {0,0,readNum};
    if(readNum++<=20){
        serial.send(handle.sendingDataHandle(READNODE,0,qwe,3));
    }else{
        readTimer.stop();
    }
}

void Dialog::on_pushButton_clicked()
{
    ui->tabWidget->setCurrentIndex(0);
}

void Dialog::on_pushButton_2_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}

void Dialog::on_pushButton_3_clicked()
{
    ui->tabWidget->setCurrentIndex(2);
}

void Dialog::addLabel(int id, QString type, QLabel *label)
{
    labelObj *obj = new labelObj;
    obj->id = id;
    obj->type = type;
    label->installEventFilter(this);// 点击装载
    obj->label = label;
    obj->primary = label->text();
    labelList.append(obj);
}

void Dialog::addButton(QString name, QString type, int id, QPushButton *button, int ch)
{
    buttonObj *obj = new buttonObj;
    obj->name = name;
    obj->type = type;
    obj->id = id;
    obj->button = button;
    obj->ch = ch;
    obj->state = false;
    obj->nowState = false;
    eleMap.insert(name,obj);
}

void Dialog::styleSlot()
{
    foreach(buttonObj*obj,eleMap){
        if(obj->type!=CT_SERVE){
            obj->button->setStyleSheet(QString("border-image: url(:/zxc/image/btn_%1.png);").arg(obj->nowState?"open":"close"));
        }
    }
}

void Dialog::controlSlot()
{
    foreach(buttonObj*obj,eleMap){
        if(obj->state!=obj->nowState){
            if(obj->type==CT_SERVE){
                AndroidControl(obj->id,obj->type,SWITCH,obj->state?SWITCH_ON:SWITCH_OFF,obj->state?CHANNEL_1:CHANNEL_2);
            }else{
                AndroidControl(obj->id,obj->type,obj->state?SWITCH_ON:SWITCH_OFF,SWITCH,obj->ch);
            }
            obj->nowState = obj->state;
            break;
        }
    }
}

void Dialog::on_ws_bt_sd_clicked()
{
    eleMap["卧室射灯"]->state =! eleMap["卧室射灯"]->state;
}

void Dialog::on_ws_bt_mj_clicked()
{
    eleMap["卧室门禁"]->state =! eleMap["卧室门禁"]->state;
}

void Dialog::on_ws_bt_kt_clicked()
{
    eleMap["卧室空调"]->state =! eleMap["卧室空调"]->state;
}

void Dialog::on_ws_bt_jsq_clicked()
{
    eleMap["卧室加湿器"]->state =! eleMap["卧室加湿器"]->state;
}

void Dialog::on_kt_bt_sd_clicked()
{
    eleMap["客厅射灯"]->state =! eleMap["客厅射灯"]->state;
}

void Dialog::on_kt_bt_ct_clicked()
{
    eleMap["客厅窗帘"]->state = true; //拉上
}

void Dialog::on_ws_bt_sd_10_clicked()
{
    eleMap["客厅窗帘"]->state = false; //拉开
}

void Dialog::on_ws_bt_sd_9_clicked()
{
    AndroidControl(ct_id,CT_SERVE,SWITCH,SWITCH_ON,CHANNEL_3);
}

void Dialog::on_kt_bt_ds_clicked()
{
    eleMap["客厅电视"]->state =! eleMap["客厅电视"]->state;
}

void Dialog::on_kt_bt_dvd_clicked()
{
    eleMap["客厅DVD"]->state =! eleMap["客厅DVD"]->state;
}

void Dialog::on_cf_bt_sd_clicked()
{
    eleMap["厨房射灯"]->state =! eleMap["厨房射灯"]->state;
}

void Dialog::on_cf_bt_bjd_clicked()
{
    eleMap["厨房报警灯"]->state =! eleMap["厨房报警灯"]->state;
}

void Dialog::on_cf_bt_fs_clicked()
{
    eleMap["厨房风扇"]->state =! eleMap["厨房风扇"]->state;
}

void Dialog::modeSlot()
{
    if(mode==GETUP){
        ui->ws_mode_getUp->setStyleSheet("border-image: url(:/zxc/image/btn_open.png);");
        if(ws_ill_value < 200){
            eleMap["卧室射灯"]->state = true;
        }else{
            eleMap["卧室射灯"]->state = false;
        }
    }else{
        ui->ws_mode_getUp->setStyleSheet("border-image: url(:/zxc/image/btn_close.png);");
    }
    if(mode==SLEEP){
        ui->ws_mode_sleep->setStyleSheet("border-image: url(:/zxc/image/btn_open.png);");
        if(ws_hum_value < 60){
            eleMap["卧室加湿器"]->state = true;
        }else{
            eleMap["卧室加湿器"]->state = false;
        }
    }else{
        ui->ws_mode_sleep->setStyleSheet("border-image: url(:/zxc/image/btn_close.png);");
    }
    if(mode==MOVIE){
        ui->kt_mode_movie->setStyleSheet("border-image: url(:/zxc/image/btn_open.png);");
    }else{
        ui->kt_mode_movie->setStyleSheet("border-image: url(:/zxc/image/btn_close.png);");
    }
    if(mode==LINKAGE){
        ui->kt_mode_text->setText("");
        QString sensor = ui->kt_mode_sensor->currentText();
        float compare_value = 0;
        if(sensor != "传感器"){
            if(sensor=="温度"){
                compare_value = temp_value;
            }else if(sensor=="湿度"){
                compare_value = hum_value;
            }else if(sensor=="气压"){
                compare_value = ap_value;
            }else if(sensor=="光照度"){
                compare_value = ill_value;
            }else if(sensor=="烟雾"){
                compare_value = smk_value;
            }else if(sensor=="CO2"){
                compare_value = co_value;
            }else if(sensor=="PM2.5"){
                compare_value = pm_value;
            }
        }else return;
        QString device = ui->kt_mode_state->currentText();
        if(device=="设备状态") return;
        float throld = ui->kt_mode_value->text().toFloat();
        QString status = device.contains("开")?"打开"+device.split("开")[0]:"关闭"+device.split("关")[0];
        ui->kt_mode_text->setText(sensor + ui->kt_mode_condition->currentText() + QString::number(throld) + "  " + status);
        if(ui->kt_mode_condition->currentText()==">="){
            if(sensor=="人体"){
                if(ui->kt_hi->text().contains("有人")){
                    if(device.contains("开")){
                        QString state = device.split("开")[0];
                        eleMap["客厅"+state]->state = true;
                    }else if(device.contains("关")){
                        QString state = device.split("关")[0];
                        eleMap["客厅"+state]->state = false;
                    }
                }
            }else{
                if(compare_value >= throld){
                    if(device.contains("开")){
                        QString state = device.split("开")[0];
                        eleMap["客厅"+state]->state = true;
                    }else if(device.contains("关")){
                        QString state = device.split("关")[0];
                        eleMap["客厅"+state]->state = false;
                    }
                }
            }
        }else if(ui->kt_mode_condition->currentText()=="<"){
            if(sensor=="人体"){
                if(ui->kt_hi->text().contains("无人")){
                    if(device.contains("开")){
                        QString state = device.split("开")[0];
                        eleMap["客厅"+state]->state = true;
                    }else if(device.contains("关")){
                        QString state = device.split("关")[0];
                        eleMap["客厅"+state]->state = false;
                    }
                }
            }else{
                if(compare_value < throld){
                    if(device.contains("开")){
                        QString state = device.split("开")[0];
                        eleMap["客厅"+state]->state = true;
                    }else if(device.contains("关")){
                        QString state = device.split("关")[0];
                        eleMap["客厅"+state]->state = false;
                    }
                }
            }
        }
    }
    if(mode==AF){
        ui->cf_mode_af->setStyleSheet("border-image: url(:/zxc/image/btn_open.png);");
        if(cf_smk_value > 100){
            eleMap["厨房报警灯"]->state = true;
            eleMap["厨房风扇"]->state = true;
            AndroidControl(fan_id,RELAY_SERVE,SWITCH_ON,SWITCH,CHANNEL_ALL);
            logList.append(QString("%1  烟雾:%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(cf_smk_value));
        }else if(cf_gas_value > 80){
            eleMap["厨房报警灯"]->state = true;
            eleMap["厨房风扇"]->state = true;
            AndroidControl(fan_id,RELAY_SERVE,SWITCH_ON,SWITCH,CHANNEL_ALL);
            logList.append(QString("%1  燃气:%2").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(cf_gas_value));
        }
    }else{
        ui->cf_mode_af->setStyleSheet("border-image: url(:/zxc/image/btn_close.png);");
    }
}

void Dialog::on_ws_mode_getUp_clicked()
{
    if(mode==GETUP){
        mode = NONE;
    }else{
        mode = GETUP;
        eleMap["卧室射灯"]->state = true;
        eleMap["卧室空调"]->state = false;
    }
}

void Dialog::on_ws_mode_sleep_clicked()
{
    if(mode==SLEEP){
        mode = NONE;
    }else{
        mode = SLEEP;
        eleMap["卧室射灯"]->state = false;
        eleMap["卧室空调"]->state = true;
    }
}

void Dialog::on_kt_mode_movie_clicked()
{
    if(mode==MOVIE){
        mode = NONE;
        eleMap["客厅射灯"]->state = true;
        eleMap["客厅电视"]->state = false;
    }else{
        mode = MOVIE;
        eleMap["客厅射灯"]->state = false;
        eleMap["客厅电视"]->state = true;
    }
}

void Dialog::on_kt_mode_switch_clicked()
{
    if(ui->kt_mode_switch->text()=="确定"){
        mode = LINKAGE;
        ui->kt_mode_switch->setText("取消");
    }else{
        mode = NONE;
        ui->kt_mode_switch->setText("确定");
    }
}

void Dialog::on_cf_mode_af_clicked()
{
    if(mode==AF){
        mode = NONE;
        eleMap["厨房报警灯"]->state = false;
        eleMap["厨房风扇"]->state = false;
        AndroidControl(fan_id,RELAY_SERVE,SWITCH_OFF,SWITCH,CHANNEL_ALL);
        eleMap["厨房射灯"]->state = true;
        AndroidControl(lamp_id,RELAY_SERVE,SWITCH_ON,SWITCH,CHANNEL_ALL);
    }else{
        mode = AF;
    }
}

void Dialog::receive_board(QString text)
{
    if(text == "<-"){
        ui->kt_mode_value->setText(ui->kt_mode_value->text().left(ui->kt_mode_value->text().length() - 1));
    }else if(text == "capsclock"){

    }else if(text == "close"){

    }else{
        ui->kt_mode_value->setText(ui->kt_mode_value->text()+text);
    }
}

bool Dialog::eventFilter(QObject *obj, QEvent *e)
{
    if(obj->inherits("QLineEdit") && e->type() == QEvent::MouseButtonDblClick){
        board.exec();
    }
    if(obj->inherits("QLabel") && e->type() == QEvent::MouseButtonDblClick){
        drawLabel = static_cast<QLabel*>(obj);
        name = drawLabel->text().split(":")[0]+"  "+companyMap[drawLabel->text().split(":")[0]];
        char_value = drawLabel->text().toFloat(); //数据传输
        huatu h;
        h.exec();
//        qDebug()<<drawLabel->text().split(":");
    }
    return QDialog::eventFilter(obj,e);
}


void Dialog::on_bt_log_clicked()
{
    rz z;
    z.exec();
}
