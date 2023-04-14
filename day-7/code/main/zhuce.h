#ifndef ZHUCE_H
#define ZHUCE_H

#include <QDialog>
#include <QMessageBox>
#include "login.h"
#include "sign.h"
#include "./smarthome/sql.h"
#include <QDebug>
#include "ruanjianpan.h"
namespace Ui {
class zhuce;
}

class zhuce : public QDialog
{
    Q_OBJECT
    
public:
    explicit zhuce(QWidget *parent = 0);
    ~zhuce();
    
private slots:
    bool eventFilter(QObject *obj, QEvent *e);
    void receive_data(QString text);
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::zhuce *ui;
    Sql sql;
    QLineEdit *line;
    ruanjianpan board;
};

#endif // ZHUCE_H
