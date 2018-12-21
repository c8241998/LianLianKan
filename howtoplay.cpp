#include "howtoplay.h"
#include "ui_howtoplay.h"

HowToPlay::HowToPlay(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::HowToPlay)
{
    this->parent=parent;
    ui->setupUi(this);
    ic[0].addFile(":/new/jpg/source/设置/返回2.png");
    ui->pushButton->setStyleSheet("background-color:transparent");
}

HowToPlay::~HowToPlay()
{
    delete ui;
}

void HowToPlay::on_pushButton_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    this->close();
    parent->show();
}


void HowToPlay::on_pushButton_pressed()
{
    ui->pushButton->setIcon(ic[0]);
}

void HowToPlay::closeEvent(QCloseEvent *event){
    parent->show();
}
