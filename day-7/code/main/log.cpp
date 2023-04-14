#include "log.h"
#include "ui_log.h"
QStringList logList;
log::log(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log)
{
    ui->setupUi(this);
    this->setWindowTitle("读取日志");
    for(int i=0;i<logList.length();i++){
        ui->textBrowser->append(logList[i]);
    }
}

log::~log()
{
    delete ui;
}

void log::on_pushButton_clicked()
{
    this->close();
}
