#include "login.h"
#include "ui_login.h"

Login::Login(QDialog *parent,int point) :
    QDialog(parent),
    ui(new Ui::Login)
{
    this->parent=parent;
    this->point=point;
    ui->setupUi(this);
    this->setWindowModality(Qt::ApplicationModal);
    ic[0].addFile(":/new/jpg/source/排行榜/确认.png");
    ui->pushButton->setStyleSheet("background-color:transparent");
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_pressed()
{
    ui->pushButton->setIcon(ic[0]);
    if(isSound==1)
        buttonSound2->play();
}

void Login::on_pushButton_clicked()
{
    QString name=ui->lineEdit->text();
    QString rank=submitScore(name);
    QMessageBox::information(this, "rank", "您的全球排名为第"+rank+"名！", QMessageBox::Ok, QMessageBox::Ok);\
    parent->close();
    this->close();
}

QString Login::submitScore(QString name){
    string temp="";
    for(int i=0;i<(name.size()>10?10:name.size());i++)
        temp+=name[i].toLatin1();
    for(int i=0;i<10-name.size();i++)
        temp+="*";
    if(point<1000){
        temp+="0";
        if(point<100){
            temp+="0";
            if(point<10)
                temp+="0";
        }
    }
    temp+=to_string(point);
    Client client("123.206.30.177",port);
    client.senddata(temp.c_str());
    QString temp2=client.getRank();
    client.senddata("**************");
    return temp2;
}
