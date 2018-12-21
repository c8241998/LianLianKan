#ifndef GRADE_H
#define GRADE_H

#include <QDialog>
#include <QIcon>
#include "login.h"
#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class Grade;
}

class Grade : public QDialog
{
    Q_OBJECT

public:
    explicit Grade(QMainWindow *parent = 0,int isWin = 1,int score=0);
    ~Grade();
    QMainWindow *parent;
private slots:
    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:

    Ui::Grade *ui;
    int isWin;//赢了是1，输了是0，显示youwin和timeup图片
    QImage im[2];
    QIcon pIcon[10];
    int score;
    QString s;
    Login *l;
protected:
     void closeEvent(QCloseEvent *event);
};

#endif // GRADE_H
