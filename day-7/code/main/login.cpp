#include "login.h"
#include "ui_login.h"
QPoint success_point(670,280);
QPoint default_point(590,280);
bool inLabel,verify;
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    inLabel = verify = false;
    ui->label_verify->installEventFilter(this);
    ui->checkBox->setChecked(true);
    QString user = sql.sqlQuery(QString("select user from tb_user where state='1'")).toString();
    QString pwd = sql.sqlQuery(QString("select pwd from tb_user where state='1'")).toString();
    QString ip = sql.sqlQuery(QString("select ip from tb_user where state='1'")).toString();
    ui->lineEdit->setText(user);
    ui->lineEdit_2->setText(pwd);
    ui->lineEdit_3->setText(ip);
    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    ui->lineEdit_3->installEventFilter(this);
    connect(&board,SIGNAL(send_data(QString)),this,SLOT(receive_data(QString)));
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_5_clicked()
{
    QString user = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();
    QString ip = ui->lineEdit_3->text();
    QString user1 = sql.sqlQuery(QString("select user from tb_user where user='%1'").arg(user)).toString();
    QString pwd1 = sql.sqlQuery(QString("select pwd from tb_user where user='%1'").arg(user)).toString();
    if(user.isEmpty() || user!=user1 || pwd!=pwd1){
        QMessageBox::warning(this,"登录失败","用户名或密码错误","确认","取消");
        verify = false;
        ui->label_verify->move(default_point);
    }else{
        sql.sqlExec(QString("update tb_user set state='0'"));
        if(ui->checkBox->isChecked()){
            sql.sqlExec(QString("update tb_user set state='1' where user='%1'").arg(user));
        }
        this->close();
        board.close();
        Dialog D;
        D.exec();
    }
}

bool login::eventFilter(QObject *obj, QEvent *e)
{
    if(obj->inherits("QLabel")){
        if(e->type() == QEvent::Enter){
            inLabel = true;
        }else if(e->type() == QEvent::Leave){
            inLabel = false;
        }else if(e->type() == QEvent::MouseButtonRelease){
            if(ui->label_verify->x() > success_point.x()+10 || ui->label_verify->x() < success_point.x() - 10){
                ui->label_verify->move(default_point);
                verify = false;
            }else{
                ui->label_verify->move(success_point);
                verify = true;
                on_pushButton_5_clicked();
            }
        }
    }
    if(obj->inherits("QLineEdit") && e->type() == QEvent::MouseButtonDblClick){
        line = static_cast<QLineEdit*>(obj);
        board.exec();
    }
    return QDialog::eventFilter(obj,e);
}

void login::mouseMoveEvent(QMouseEvent *e)
{
    if(inLabel){
        if(ui->label_verify->x()<ui->label_4->x() || ui->label_verify->x()>ui->label_4->x()+ui->label_4->width()-ui->label_verify->width()){
            return;
        }else{
            ui->label_verify->move(e->pos().x(),ui->label_verify->y());
        }
    }
}

void login::receive_data(QString text)
{
    if(text=="<-"){
        line->setText(line->text().left(line->text().length()-1));
    }else if(text=="close"){

    }else if(text=="capsclock"){

    }else{
        line->setText(line->text()+text);
    }
}

void login::on_pushButton_3_clicked()
{
    this->close();
    zhuce s;
    s.exec();
}

void login::on_pushButton_4_clicked()
{
    this->close();
    sign s;
    s.exec();
}
