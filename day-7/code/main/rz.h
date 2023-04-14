#ifndef RZ_H
#define RZ_H

#include <QDialog>

namespace Ui {
class rz;
}

class rz : public QDialog
{
    Q_OBJECT
    
public:
    explicit rz(QWidget *parent = 0);
    ~rz();
    
private slots:
    void on_pushButton_clicked();

private:
    Ui::rz *ui;
};

#endif // RZ_H
