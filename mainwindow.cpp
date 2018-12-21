#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent,QApplication *a) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->app=a;
    ui->setupUi(this);
    this->setMouseTracking(true);
    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(on_button_Clicked()));
    musicPlayer =new QMediaPlayer();
    musicPlayer->setMedia(QUrl("qrc:/new/jpg/source/音乐/background.mp3"));
    musicPlayer->play();
    musicPlayer->setVolume(50);
   // connect(musicPlayer,SIGNAL(aboutToFinish()),this,SLOT(playAgain()));
    buttonSound1=new QMediaPlayer();
    buttonSound2=new QMediaPlayer();
    buttonSound1->setMedia(QUrl("qrc:/new/jpg/source/音乐/sound1.mp3"));
    buttonSound2->setMedia(QUrl("qrc:/new/jpg/source/音乐/sound2.mp3"));
    q = new QMovie(":/new/jpg/source/初始化界面/star.gif");
    ui->label_2->setMovie(q);
    q->start();
    q1 = new QMovie(":/new/jpg/source/初始化界面/title.gif");
    ui->label_3->setMovie(q1);
    q1->start();

    ic[0].addFile(":/new/jpg/source/初始化界面/1B.png");
    ic[1].addFile(":/new/jpg/source/初始化界面/1开始游戏.png");
    ic[2].addFile(":/new/jpg/source/初始化界面/2B.png");
    ic[3].addFile(":/new/jpg/source/初始化界面/2排行榜查询.png");
    ic[4].addFile(":/new/jpg/source/初始化界面/3B.png");
    ic[5].addFile(":/new/jpg/source/初始化界面/3游戏说明.png");
    ic[6].addFile(":/new/jpg/source/初始化界面/4B.png");
    ic[7].addFile(":/new/jpg/source/初始化界面/4游戏设置.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()   //游戏
{
    this->hide();
    g = new Gaming(this);
    g->show();

}


void MainWindow::on_pushButton_4_clicked()   //设置
{
    this->hide();
    s = new Gamesetup(this);
    s->show();

}

void MainWindow::closeEvent(QCloseEvent * event)
{
    exit(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    r = new Ranklist(this);
    r->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->hide();
    h=new HowToPlay(this);
    h->show();
}

void MainWindow::on_pushButton_pressed()
{
    if(isSound==1)
        buttonSound1->play();
}

void MainWindow::on_pushButton_2_pressed()
{
    if(isSound==1)
        buttonSound1->play();
}

void MainWindow::on_pushButton_3_pressed()
{
    if(isSound==1)
        buttonSound1->play();
}

void MainWindow::on_pushButton_4_pressed()
{
    if(isSound==1)
        buttonSound1->play();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    int x=e->x();
    int y=e->y();
    if(x>150&x<753&&y>365&&y<475){
        ui->pushButton->setIcon(ic[0]);
        ui->pushButton_2->setIcon(ic[3]);
        ui->pushButton_3->setIcon(ic[5]);
        ui->pushButton_4->setIcon(ic[7]);
    }else if(x>150&&x<753&&y>475&&y<585){
        ui->pushButton_2->setIcon(ic[2]);
        ui->pushButton->setIcon(ic[1]);
        ui->pushButton_3->setIcon(ic[5]);
        ui->pushButton_4->setIcon(ic[7]);
    }else if(x>150&&x<753&&y>613&&y<723){
        ui->pushButton_3->setIcon(ic[4]);
        ui->pushButton->setIcon(ic[1]);
        ui->pushButton_2->setIcon(ic[3]);
        ui->pushButton_4->setIcon(ic[7]);
    }else if(x>150&&x<753&&y>723&&y<833){
        ui->pushButton_4->setIcon(ic[6]);
        ui->pushButton->setIcon(ic[1]);
        ui->pushButton_2->setIcon(ic[3]);
        ui->pushButton_3->setIcon(ic[5]);
    }else{
        ui->pushButton->setIcon(ic[1]);
        ui->pushButton_2->setIcon(ic[3]);
        ui->pushButton_3->setIcon(ic[5]);
        ui->pushButton_4->setIcon(ic[7]);
    }
}
