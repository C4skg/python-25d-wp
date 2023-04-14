#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "dialog.h"
#include "./smarthome/sql.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include "ruanjianpan.h"
#include "login.h"
#include "sign.h"
#include "zhuce.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    
public:
    explicit login(QWidget *parent = 0);
    ~login();
    
private slots:
    void on_pushButton_5_clicked();

private:
    Ui::login *ui;
    Sql sql;
    QLineEdit *line;
    ruanjianpan board;

private slots:
    void receive_data(QString text);
    bool eventFilter(QObject *obj, QEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // LOGIN_H
