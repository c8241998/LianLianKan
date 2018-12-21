#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gaming.h"
#include "gamesetup.h"
#include "ranklist.h"
#include "header.hpp"
#include "howtoplay.h"
#include <QCloseEvent>
#include "QMovie"
#include <QIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,QApplication *a=0);
    void mouseMoveEvent(QMouseEvent *e);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_4_pressed();

private:
    Ui::MainWindow *ui;
    Gaming *g;
    Gamesetup *s;
    QApplication *app;
    Ranklist *r;
    HowToPlay *h;
    QMovie *q;
    QMovie *q1;
    QIcon ic[8];

protected:
    void closeEvent(QCloseEvent *event);

};

#endif // MAINWINDOW_H
