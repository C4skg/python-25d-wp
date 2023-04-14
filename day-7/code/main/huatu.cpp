#include "huatu.h"
#include "ui_huatu.h"
extern QString name;
extern float char_value;
QPoint center;
QLabel *label;
huatu::huatu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::huatu)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //QTimer
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);

    center = QPoint(width() / 2,height() / 2);
    label = new QLabel(this);
    label->resize(50,25);
    label->setText(QString::number(char_value));
    label->move(center.x() - label->width()/2,center.y() + 120);
    label->setStyleSheet("border:1 solid gray;color:gray;border-radius:8px;");
    label->setAlignment(Qt::AlignCenter);

    this->setStyleSheet("background-color:white");
}

huatu::~huatu()
{
    delete ui;
}

void huatu::update()
{
    if(name.contains("温度")){
        char_value = random()%100 - 50;
    }else{
        char_value = random()%100;
    } //模拟数据,实际传值需要注释
    label->setText(QString::number(char_value));
    this->repaint();
}

void huatu::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QLinearGradient linear(0,0,550,0);
    linear.setColorAt(0.4,Qt::green);
    linear.setColorAt(0.7,Qt::blue);
    linear.setColorAt(0.9,Qt::red);

    painter.setBrush(linear);
    painter.setPen(Qt::NoPen);
    if(name.contains("温度")){
        painter.drawPie(center.x() - 200,center.y() - 200,400,400,(90)*16,-(char_value/50*150)*16); // 300度
    }else{
        painter.drawPie(center.x() - 200,center.y() - 200,400,400,(90+150)*16,-(char_value/100*300)*16); // 300度
    }
    painter.setBrush(Qt::white);
    painter.drawPie(center.x() - 190,center.y() - 190,380,380,-65*16,310*16);

    painter.translate(center);
    painter.setPen(Qt::gray);
    painter.drawText(-20,-100,name);

    this->drawScale(&painter);
    this->drawPointer(&painter);
}

void huatu::drawScale(QPainter *painter)
{
    painter->save();
    painter->rotate(-150);
    for(int i=0;i<101;i++){
        if(i==0) painter->setPen(Qt::green);
        if(i==30) painter->setPen(Qt::blue);
        if(i==71) painter->setPen(Qt::red);
        if(i%10==0){
            painter->drawLine(QPoint(0,-190),QPoint(0,-200));
            painter->save();
            painter->setPen(Qt::black);
            if(name.contains("温度")){
                painter->drawText(-5,-170,QString::number(i - 50));
            }else{
                painter->drawText(-5,-170,QString::number(i));
            }
            painter->restore();
        }else{
            painter->drawLine(QPoint(0,-195),QPoint(0,-200));
        }
        painter->rotate(+3);
    }

    painter->restore();
}

void huatu::drawPointer(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    if(name.contains("温度")){
        painter->rotate((char_value/50)*150);
    }else{
        painter->rotate(-150+(char_value/100)*300);
    }
    QPoint polygons[4] = {QPoint(0,-200),QPoint(0,-200),QPoint(-8,0),QPoint(8,0)};
    painter->drawPolygon(polygons,4);
    painter->drawEllipse(-10,-10,20,20);
    painter->setBrush(Qt::white);
    painter->drawEllipse(-5,-5,10,10);

    painter->restore();
}
