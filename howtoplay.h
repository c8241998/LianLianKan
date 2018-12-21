#ifndef HOWTOPLAY_H
#define HOWTOPLAY_H

#include <QMainWindow>
#include <QIcon>
#include <QCloseEvent>
#include "header.hpp"

namespace Ui {
class HowToPlay;
}

class HowToPlay : public QMainWindow
{
    Q_OBJECT

public:
    explicit HowToPlay(QMainWindow *parent = 0);
    ~HowToPlay();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_pressed();

private:
    QMainWindow* parent;
    Ui::HowToPlay *ui;
    QIcon ic[2];
protected:
     void closeEvent(QCloseEvent *event);
};

#endif // HOWTOPLAY_H
