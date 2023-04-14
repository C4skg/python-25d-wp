#ifndef SIGN_H
#define SIGN_H

#include <QDialog>
#include "./smarthome/sql.h"
#include "login.h"
#include <QMessageBox>
#include "ruanjianpan.h"
#include <QLineEdit>
#include <QSqlTableModel>
#include "zhuce.h"
namespace Ui {
class sign;
}

class sign : public QDialog
{
    Q_OBJECT
    
public:
    explicit sign(QWidget *parent = 0);
    ~sign();
    
private slots:
    void receive_data(QString text);
    bool eventFilter(QObject *obj, QEvent *e);
    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::sign *ui;
    QLineEdit *line;
    ruanjianpan board;
    Sql sql;
    QSqlTableModel *table;
};

#endif // SIGN_H
