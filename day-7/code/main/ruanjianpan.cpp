#include "ruanjianpan.h"
#include "ui_ruanjianpan.h"
bool isCaps;
QStringList CapList;
QStringList list;
ruanjianpan::ruanjianpan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ruanjianpan)
{
    ui->setupUi(this);
    this->setWindowTitle("softkey");
    isCaps = false;
    QString value = "`~-_=+[]{},./<>?;':\"!@#$%^&*()0123456789abcedfghijklmnopqrstuvwxyz";
    QString isCap = "`~-_=+[]{},./<>?;':\"!@#$%^&*()0123456789ABCEDFGHIJKLMNOPQRSTUVWXYZ";
    list = value.split("");
    CapList = isCap.split("");
    list.removeFirst();
    list.removeLast();
    CapList.removeFirst();
    CapList.removeLast();
    for(int i=0;i<list.length()+3;i++){
        QPushButton *button = new QPushButton(this);
        button->resize(25,25);
        button->move(25*(i%10),20+25*(i/10));
        button->installEventFilter(this);
        if(i==67){
            button->resize(75,25);
        }else if(i==68){
            button->resize(60,25);
            button->move(25*(i%10)-25,20+25*(i/10)+25);
        }
    }
    reSetText(list);
}

ruanjianpan::~ruanjianpan()
{
    delete ui;
}

bool ruanjianpan::eventFilter(QObject *obj, QEvent *e)
{
    if(obj->inherits("QPushButton") && e->type() == QEvent::MouseButtonRelease){
        QString text = static_cast<QPushButton*>(obj)->text();
        if(text=="close"){
            this->close();
        }else if(text == "capsclock"){
            isCaps = !isCaps;
            if(isCaps){
                reSetText(CapList);
            }else{
                reSetText(list);
            }
        }
        emit send_data(text);
    }
    return QDialog::eventFilter(obj,e);
}

void ruanjianpan::reSetText(QStringList list)
{
    QList<QPushButton*> buttonList = this->findChildren<QPushButton*>();
    for(int i=0;i<buttonList.length();i++){
        if(i<66){
            if(list[i] == "&"){
                buttonList[i]->setText("&&");
            }else{
                buttonList[i]->setText(list[i]);
            }
        }else if(i==66){
            buttonList[i]->setText("<-");
        }else if(i==67){
            buttonList[i]->setText("capsclock");
        }else if(i==68){
            buttonList[i]->setText("close");
        }
    }
}
