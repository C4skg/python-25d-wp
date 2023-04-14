#ifndef VARIABLEDEFINITION_H
#define VARIABLEDEFINITION_H

/******************************串口通信部分要用到的定义**************************************************/
#define MAX_BOARDID_NUM 30 //最大设备数

/************************************************
设备类型定义
 ***********************************************/
#define RELAY           0XEE01          //继电器
#define BODYINFRARED    0XEE02          //人体红外
#define SMOKE           0XEE03          //烟雾
#define CO2             0XEE04          //二氧化碳
#define GAS             0XEE05          //燃气
#define PRESSURE        0XEE06          //气压
#define THI             0XEE07          //温湿度
#define ILL             0XEE08          //光照
#define PM25            0XEE09          //PM2.5
#define RFID            0XEE0A          //门禁
#define INFRARED        0XEE0B          //红外转发
/**************************************************/
/************************************************
 操作码定义
 ***********************************************/
#define CONTROL             0X06    //控制设备
#define GETSTATE            0X07    //获取状态
#define READNODE            0X0B    //读取节点
#define DEVICETEST          0XFF    //握手测试
/**************************************************/
//cmdCode 定义
#define VOL_RELAY            0x01  //电压型继电器
#define DOOR_CONTROL         0x01  //门禁控制
#define INFRARED_EMIT        0x01  //红外发射
#define INFRARED_STUDY       0x02  //红外学习
#define INFRARED_EXIT        0x00  //红外退出学习
#define NODE_RELAY           0x03  //节点型继电器

//cmd 定义
#define SWITCH              0x01  //开关命令
#define SWITCH_ON           0x01  //开
#define SWITCH_OFF          0x00  //关

//设备通道定义
#define CHANNEL_1                    0x01   //通道1
#define CHANNEL_2                    0x02   //通道2
#define CHANNEL_3                    0x04   //通道3
#define CHANNEL_4                    0x08   //通道4
#define CHANNEL_ALL                  0x07   //所有通道
/**************************************模式定义**********************************************/
#define ILL_MODE    0
#define TEMP_MODE   1
#define SAFE_MODE   2
#define OUT_MODE    3
#define SLEEP_MODE  4
#define WAKE_MODE   5
/*********************************与服务器通信部分定义********************************************/
#define TEMP_SERVE             "0"           //温度
#define HUM_SERVE              "1"           //湿度
#define ILL_SERVE              "2"           //光照
#define SMK_SERVE              "3"           //烟雾
#define GAS_SERVE              "4"           //燃气
#define PM25_SERVE             "5"           //PM2.5
#define CO2_SERVE              "6"           //二氧化碳
#define AP_SERVE               "7"           //气压
#define HI_SERVE               "8"           //人体红外
#define RELAY_SERVE            "9"           //继电器
#define INFRARED_SERVE         "10"          //红外发射
#define DC_SERVE               "11"          //门禁控制
#define SWITCH_SERVE           "12"         //插座
#define CT_SERVE               "13" //窗帘

//BoardId
#define temp_id 4
#define ill_id 10
#define dc_id 13
#define air_hum_id 15
#define temp_id_2 1
#define ill_id_2 2
#define ap_id 8
#define hi_id 7
#define co2_id 5
#define smk_id 3
#define pm_id 6
#define lamp_id 12
#define tv_dvd_id 20
#define ct_id 19
#define gas_id 11
#define smk_id_2 9
#define lamp_id_2 19
#define wl_id 18
#define fan_id 16

//上传状态
#define ON                "1"
#define OFF               "0"
#define STOP              "2"
#define CLOSE             "4"

/****************************************************************************************/
#endif // VARIABLEDEFINITION_H
