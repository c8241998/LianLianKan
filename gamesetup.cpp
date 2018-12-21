#include "gamesetup.h"
#include "ui_gamesetup.h"
#include <QMessageBox>
Gamesetup::Gamesetup(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Gamesetup)
{
    this->parent=parent;
    ui->setupUi(this);
    ic[0].addFile(":/new/jpg/source/设置/透明.png");
    ic[1].addFile(":/new/jpg/source/设置/simple1.jpg");
    ic[2].addFile(":/new/jpg/source/设置/中等1.jpg");
    ic[3].addFile(":/new/jpg/source/设置/困难1.jpg");
    ic[4].addFile(":/new/jpg/source/设置/sound.png");
    ic[5].addFile(":/new/jpg/source/设置/soundmute.png");
    ic[6].addFile(":/new/jpg/source/设置/music.png");
    ic[7].addFile(":/new/jpg/source/设置/musicmute.png");
    ic[7].addFile(":/new/jpg/source/设置/返回2.png");
    ui->pushButton_2->setStyleSheet("background-color:transparent");
    ui->pushButton_3->setStyleSheet("background-color:transparent");
    ui->pushButton_4->setStyleSheet("background-color:transparent");
    ui->pushButton_5->setStyleSheet("background-color:transparent");
    ui->pushButton_6->setStyleSheet("background-color:transparent");
    ui->pushButton_7->setStyleSheet("background-color:transparent");

    ui->pushButton_2->setIcon(mode==1?ic[1]:ic[0]);
    ui->pushButton_3->setIcon(mode==2?ic[2]:ic[0]);
    ui->pushButton_4->setIcon(mode==3?ic[3]:ic[0]);
    ui->pushButton_5->setIcon(isMusic?ic[4]:ic[5]);
    ui->pushButton_6->setIcon(isSound?ic[6]:ic[7]);

}

Gamesetup::~Gamesetup()
{
    delete ui;
}

void Gamesetup::on_pushButton_2_clicked()
{
    ui->pushButton_2->setIcon(ic[1]);
    ui->pushButton_3->setIcon(ic[0]);
    ui->pushButton_4->setIcon(ic[0]);
    if(isSound==1)
        buttonSound2->play();
    mode=1;
}

void Gamesetup::on_pushButton_3_clicked()
{
    ui->pushButton_2->setIcon(ic[0]);
    ui->pushButton_3->setIcon(ic[2]);
    ui->pushButton_4->setIcon(ic[0]);
    if(isSound==1)
        buttonSound2->play();
    mode=2;
}

void Gamesetup::on_pushButton_4_clicked()
{
    ui->pushButton_2->setIcon(ic[0]);
    ui->pushButton_3->setIcon(ic[0]);
    ui->pushButton_4->setIcon(ic[3]);
    if(isSound==1)
        buttonSound2->play();
    mode=3;
}

void Gamesetup::on_pushButton_5_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    if(isMusic){
        ui->pushButton_5->setIcon(ic[5]);
        isMusic=false;
        musicPlayer->stop();
    }else{
        ui->pushButton_5->setIcon(ic[4]);
        isMusic=true;
        musicPlayer->play();
    }
}

void Gamesetup::on_pushButton_6_clicked()
{
    if(isSound){
        ui->pushButton_6->setIcon(ic[7]);
        isSound=false;
    }else{
        ui->pushButton_6->setIcon(ic[6]);
        isSound=true;
    }
    if(isSound==1)
        buttonSound2->play();
}

void Gamesetup::on_pushButton_7_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    this->close();
    parent->show();
}
void Gamesetup::closeEvent(QCloseEvent *event)
{
    parent->show();
}

void Gamesetup::on_pushButton_7_pressed()
{
    ui->pushButton_7->setIcon(ic[7]);
}
