#ifndef GAMESETUP_H
#define GAMESETUP_H

#include <QMainWindow>
#include "header.hpp"
#include <QCloseEvent>

namespace Ui {
class Gamesetup;
}

class Gamesetup : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gamesetup(QMainWindow *parent = 0);
    ~Gamesetup();


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_7_pressed();

private:
    QMainWindow* parent;
    Ui::Gamesetup *ui;
    QIcon ic[8];

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // GAMESETUP_H
