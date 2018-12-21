#include "mainwindow.h"
#include "gaming.h"
#include <QApplication>
#include <vector>
#include "header.hpp"
#include <QString>
int mode=1;
bool isMusic=true;
bool isSound=true;
int port = 8088;
QMediaPlayer* musicPlayer;
QMediaPlayer* buttonSound1;
QMediaPlayer* buttonSound2;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(0,&a);
    w.show();
    return a.exec();
}
