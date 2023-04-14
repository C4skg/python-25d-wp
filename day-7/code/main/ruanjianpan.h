#ifndef RUANJIANPAN_H
#define RUANJIANPAN_H

#include <QDialog>
#include <QPushButton>
#include <QList>
namespace Ui {
class ruanjianpan;
}

class ruanjianpan : public QDialog
{
    Q_OBJECT
    
public:
    explicit ruanjianpan(QWidget *parent = 0);
    ~ruanjianpan();
signals:
    void send_data(QString text);
private:
    Ui::ruanjianpan *ui;
private slots:
    bool eventFilter(QObject *obj, QEvent *e);
    void reSetText(QStringList list);
};

#endif // RUANJIANPAN_H
