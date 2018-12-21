#ifndef GAMING_H
#define GAMING_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <string>
#include <string.h>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QButtonGroup>
#include <math.h>
#include <vector>
#include "mybutton.h"
#include "header.hpp"
#include <QCloseEvent>
#include <QMovie>
#include <client.hpp>
#include "grade.h"

namespace Ui {
class Gaming;
}

struct Point {
  int x;
  int y;
};

class Gaming : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gaming(QMainWindow *parent = 0);
    ~Gaming();
    void buttonFlash(int id,int size1,int size2);
    bool checkLineTo(int x1,int y1,int x2,int y2);
    bool lineTo3(int x,int y,int a,int b);
    bool lineTo2(int x,int y,int a,int b);
    bool lineTo1(int x,int y,int a,int b);
    void winGame();
    void showLine();
    void addPoint(std::vector<Point>* p,int x,int y);
    int i;
private:
    QMovie* qm;
    QMainWindow* parent;
    Ui::Gaming *ui;
    MyButton *grid[14+2][14+2];
    QButtonGroup *buttonGroup;
    int mapsize;
    int map[14+2][14+2];
    int first;
    int second;
    int numButton;
    QTimer *qti;
    QIcon key[20];
    double percent;
    QLabel *line[14+2][14+2];
    std::vector<Point> p1,p2,p3;
    QImage line_icon[11];
    Gaming* newGame;      // restart a game
    int point;     //分数   基础分 0 1000 2000   一对50分
    QString pstring;
    int pause;
    QIcon pIcon[4];
    QIcon bIcon[8];
    Grade *g;
    QMediaPlayer* soundPlayer;

   // Point tempPoint;
private slots:
    void click(int id);
    void on_pushButton_2_clicked();
    void time_out();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_pressed();
    void on_pushButton_released();

    void on_pushButton_5_clicked();

    void on_pushButton_2_pressed();

    void on_pushButton_2_released();

    void on_pushButton_3_pressed();

    void on_pushButton_3_released();

    void on_pushButton_4_pressed();

    void on_pushButton_4_released();

    void on_pushButton_5_pressed();

    void on_pushButton_5_released();

    void mouseMoveEvent(QMouseEvent *e);

protected:
     void closeEvent(QCloseEvent *event);
};

#endif // GAMING_H
