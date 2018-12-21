#include "grade.h"
#include "ui_grade.h"

Grade::Grade(QMainWindow *parent,int isWin,int score) :
    QDialog(parent),
    ui(new Ui::Grade)
{
    this->parent=parent;
    this->isWin=isWin;
    this->score=score;
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    im[0].load(":/new/jpg/source/排行榜/youWin.png");
    im[1].load(":/new/jpg/source/排行榜/timeUp.png");
    if(isWin==0){
        ui->label_3->setPixmap(QPixmap::fromImage(im[1]));
    }
    pIcon[0].addFile(":/new/jpg/source/排行榜/记录B.png");
    pIcon[1].addFile(":/new/jpg/source/排行榜/放弃B.png");
    ui->pushButton->setStyleSheet("background-color:transparent");
    ui->pushButton_2->setStyleSheet("background-color:transparent");

    s = QString::number(score, 10);
    ui->label_2->setText(s);
}

Grade::~Grade()
{
    delete ui;
}

void Grade::on_pushButton_pressed()
{
    ui->pushButton->setIcon(pIcon[0]);
}

void Grade::on_pushButton_2_pressed()
{
    ui->pushButton_2->setIcon(pIcon[1]);
}

void Grade::on_pushButton_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    l=new Login(this,score);
    l->show();
}

void Grade::on_pushButton_2_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    this->close();
    parent->close();
}
void Grade::closeEvent(QCloseEvent *event){
    parent->close();
}
