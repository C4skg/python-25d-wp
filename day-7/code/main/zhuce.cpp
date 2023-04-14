#include "zhuce.h"
#include "ui_zhuce.h"

zhuce::zhuce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit_3->installEventFilter(this);
    connect(&board,SIGNAL(send_data(QString)),this,SLOT(receive_data(QString)));
}

zhuce::~zhuce()
{
    delete ui;
}

void zhuce::on_pushButton_3_clicked()
{
    QString user = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();
    QString sure = ui->lineEdit_3->text();
    QString user1 = sql.sqlQuery(QString("select user from tb_user where user='%1'").arg(user)).toString();
    int len = sql.sqlQuery(QString("select count(*) from tb_user")).toInt();
    if(user.isEmpty() || pwd.isEmpty()){
        QMessageBox::warning(this,"注册失败","用户注册信息不能为空");
    }else if(pwd!=sure){
        QMessageBox::warning(this,"注册失败","两次密码不一致");
    }else if(user==user1){
        QMessageBox::warning(this,"注册失败","用户已存在");
    }else{
        if(sql.sqlExec(QString("insert into tb_user values('%1','%2','%3','192.168.5.2','0')").arg(QString::number(len+1)).arg(user).arg(pwd))){
            QMessageBox::information(this,"注册成功","欢迎使用！");
        }
    }
}

void zhuce::on_pushButton_5_clicked()
{
    this->close();
    login l;
    l.exec();
}

void zhuce::on_pushButton_4_clicked()
{
    this->close();
    sign s;
    s.exec();
}

bool zhuce::eventFilter(QObject *obj, QEvent *e)
{
    if(obj->inherits("QLineEdit") && e->type()== QEvent::MouseButtonDblClick){
        line = static_cast<QLineEdit*>(obj);
        board.exec();
    }
    return QDialog::eventFilter(obj,e);
}

void zhuce::receive_data(QString text)
{
    if(text=="<-"){
        line->setText(line->text().left(line->text().length()-1));
    }else if(text=="close"){

    }else if(text=="capsclock"){

    }else{
        line->setText(line->text()+text);
    }
}
