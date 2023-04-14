#include <QtGui/QApplication>
#include "dialog.h"
#include <QTextCodec>
#include "./smarthome/sql.h"
#include "login.h"
#include "ruanjianpan.h"
#include "huatu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    Sql sql;
    sql.sqlConnect("db_modelRoom.db");
    sql.sqlExec("create table tb_user(id varchar primary key,user varchar,pwd varchar,ip varchar,state varchar)");
    sql.sqlExec("insert into tb_user values('1','bizideal','123456','192.168.5.2','0')");

    Dialog w;
    w.show();
    
    return a.exec();
}
