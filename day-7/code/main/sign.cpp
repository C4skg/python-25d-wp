#include "sign.h"
#include "ui_sign.h"

sign::sign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    table = new QSqlTableModel(this);
    table = sql.sqlTableMode("tb_user");
    table->setHeaderData(1,Qt::Horizontal,"用户名");
    table->setHeaderData(2,Qt::Horizontal,"密码");
    ui->tableView->setModel(table);
    ui->tableView->hideColumn(3);
    ui->tableView->hideColumn(4);

    ui->lineEdit->installEventFilter(this);
    ui->lineEdit_2->installEventFilter(this);
    connect(&board,SIGNAL(send_data(QString)),this,SLOT(receive_data(QString)));
}

sign::~sign()
{
    delete ui;
}

void sign::on_pushButton_7_clicked()
{
    QString user = ui->lineEdit->text();
    QString pwd = ui->lineEdit_2->text();
    QString user1 = sql.sqlQuery(QString("select user from tb_user where user='%1'").arg(user)).toString();
    QRegExp exp("[`~!@#$%^&*()\\_+=<>?:\"{}]");
    if(user!=user1){
        QMessageBox::warning(this,"管理失败","无此用户");
    }else if(pwd.contains(QRegExp("[Aa-Zz]")) && pwd.contains(QRegExp("[0-9]")) && pwd.contains(exp)){
        if(sql.sqlExec(QString("update tb_user set pwd='%1' where user='%2'").arg(pwd).arg(user))){
            table->select();
        }
    }else{
        QMessageBox::warning(this,"管理失败","新密码格式不正确");
    }
}

void sign::on_pushButton_6_clicked()
{
    int row = ui->tableView->currentIndex().row();
    QString user = table->index(row,1).data().toString();
    if(sql.sqlExec(QString("delete from tb_user where user='%1'").arg(user))){
        table->select();
    }
}

void sign::on_pushButton_5_clicked()
{
    this->close();
    login l;
    l.exec();
}

void sign::on_pushButton_3_clicked()
{
    this->close();
    zhuce z;
    z.exec();
}

void sign::on_pushButton_4_clicked()
{

}

bool sign::eventFilter(QObject *obj, QEvent *e)
{
    if(obj->inherits("QLineEdit") && e->type()==QEvent::MouseButtonDblClick){
        line = static_cast<QLineEdit*>(obj);
        board.exec();
    }
    return QDialog::eventFilter(obj,e);
}

void sign::receive_data(QString text)
{
    if(text=="<-"){
        line->setText(line->text().left(line->text().length()-1));
    }else if(text=="close"){

    }else if(text=="capsclock"){

    }else{
        line->setText(line->text()+text);
    }
}
