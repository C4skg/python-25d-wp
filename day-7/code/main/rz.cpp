#include "rz.h"
#include "ui_rz.h"
QStringList logList;
rz::rz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rz)
{
    ui->setupUi(this);
    this->setWindowTitle("读取日志");
    for(int i=0;i<logList.length();i++){
        ui->textBrowser->append(logList[i]);
    }
}

rz::~rz()
{
    delete ui;
}

void rz::on_pushButton_clicked()
{
    this->close();
}
