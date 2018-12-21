#include "ranklist.h"
#include "ui_ranklist.h"

Ranklist::Ranklist(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Ranklist)
{
    this->parent=parent;
    ui->setupUi(this);
      QFont q1("Ink Free",28,50);
      ui->label_1->setFont(q1);
      ui->label_2->setFont(q1);
      ui->label_3->setFont(q1);
      ui->label_4->setFont(q1);
      ui->label_5->setFont(q1);
      ui->label_6->setFont(q1);
      ui->label_7->setFont(q1);
      ui->label_8->setFont(q1);
      ui->label_9->setFont(q1);
      ui->label_10->setFont(q1);
      ui->label_11->setFont(q1);
      ui->label_12->setFont(q1);


      Client client("123.206.30.177",port);
      client.senddata("##############");
      client.receive(rank);
      client.senddata("**************");

      ui->label_1->setText(rank[1]);
      ui->label_2->setText(rank[2]);
      ui->label_3->setText(rank[3]);
      ui->label_4->setText(rank[4]);
      ui->label_5->setText(rank[5]);
      ui->label_6->setText(rank[6]);
      ui->label_7->setText(rank[7]);
      ui->label_8->setText(rank[8]);
      ui->label_9->setText(rank[9]);
      ui->label_10->setText(rank[10]);
      ui->label_11->setText(rank[11]);
      ui->label_12->setText(rank[12]);
      ic[0].addFile(":/new/jpg/source/设置/返回2.png");
      ui->pushButton->setStyleSheet("background-color:transparent");

}

Ranklist::~Ranklist()
{
    delete ui;
}



void Ranklist::closeEvent(QCloseEvent *event){
    parent->show();
}



void Ranklist::on_pushButton_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    this->close();
    parent->show();
}

void Ranklist::on_pushButton_pressed()
{
    ui->pushButton->setIcon(ic[0]);
}
