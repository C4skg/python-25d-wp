#ifndef HUATU_H
#define HUATU_H

#include <QDialog>
#include <QPainter>
#include <QTimer>
#include <QLabel>
namespace Ui {
class huatu;
}

class huatu : public QDialog
{
    Q_OBJECT
    
public:
    explicit huatu(QWidget *parent = 0);
    ~huatu();
    
private:
    Ui::huatu *ui;
    QTimer *timer;
private slots:
    void paintEvent(QPaintEvent *);
    void drawScale(QPainter *painter);
    void drawPointer(QPainter *painter);
    void update();
};

#endif // HUATU_H
