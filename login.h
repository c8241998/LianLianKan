#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QIcon>
#include <QString>
#include <QMessageBox>
#include <string>
#include <client.hpp>
#include <header.hpp>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QDialog *parent = 0,int point=0);
    ~Login();
    QString submitScore(QString name);

private slots:
    void on_pushButton_pressed();

    void on_pushButton_clicked();

private:
    QDialog * parent;
    Ui::Login *ui;
    QIcon ic[1];
    QString name;
    int point;
};

#endif // LOGIN_H
