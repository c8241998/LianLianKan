#include "gaming.h"
#include "mainwindow.h"
#include "ui_gaming.h"
#include <ctime>
Gaming::Gaming(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::Gaming)
{
    this->parent=parent;
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("background-color:transparent");
    ui->pushButton_2->setStyleSheet("background-color:transparent");
    ui->pushButton_3->setStyleSheet("background-color:transparent");
    ui->pushButton_4->setStyleSheet("background-color:transparent");
    ui->pushButton_5->setStyleSheet("background-color:transparent");

    qm=new QMovie(":/new/jpg/source/游戏ing界面/pause.gif");
    ui->label_4->setMovie(qm);
    ui->label_4->hide();
    pause=1;
    pIcon[0].addFile(":/new/jpg/source/提示/B/pauseB.png");
    pIcon[1].addFile(":/new/jpg/source/提示/B/startB.png");
    pIcon[2].addFile(":/new/jpg/source/提示/S/pauseS.png");
    pIcon[3].addFile(":/new/jpg/source/提示/S/startS.png");

    bIcon[0].addFile(":/new/jpg/source/提示/B/hintB.png");
    bIcon[1].addFile(":/new/jpg/source/提示/B/restartB.png");
    bIcon[2].addFile(":/new/jpg/source/提示/B/backB.png");
    bIcon[3].addFile(":/new/jpg/source/提示/B/musicB.png");
    bIcon[4].addFile(":/new/jpg/source/提示/S/hintS.png");
    bIcon[5].addFile(":/new/jpg/source/提示/S/restartS.png");
    bIcon[6].addFile(":/new/jpg/source/提示/S/backS.png");
    bIcon[7].addFile(":/new/jpg/source/提示/S/musicS.png");


    mapsize=14;            //init
    numButton=mapsize*mapsize;
    first=-1;
    second=-1;
    point=(mode-1)*1000;
    pstring=QString::number(point, 10);
    ui->label_3->setText(pstring);
    for(int i=0;i<=mapsize+1;i++){
        for(int j=0;j<=mapsize+1;j++){
            map[i][j]=-1;
        }
    }
    for(int i=0;i<20;i++){
        QString filename;
        int temp=i%(5+mode*5);
        filename = ":/new/jpg/source/animal/"+QString::number(temp)+".jpg";   //难度设置  10 15 20
        key[temp].addFile(filename);

    }
    int flag = 0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    buttonGroup = new QButtonGroup(this);

    //  生成棋子
    for(int i = 1;i<=mapsize/2;i++){
        for(int j = 1;j<=mapsize;j++){
            grid[i][j] = new MyButton(this);
            buttonGroup->addButton(grid[i][j],i*mapsize+j-1);
            grid[i][j]->setGeometry(50+j*50,10+i*50,50,50);
            flag = qrand()%(5+mode*5);
            grid[i][j]->setIcon(key[flag]);
            map[i][j]=flag;
            grid[i][j]->setIconSize(QSize(40,40));


            int x=qrand()%(mapsize/2)+mapsize/2+1,y=qrand()%mapsize+1;
            while(map[x][y]!=-1){
                x=qrand()%(mapsize/2)+mapsize/2+1;
                y=qrand()%mapsize+1;
            }
            grid[x][y] = new MyButton(this);
            buttonGroup->addButton(grid[x][y],x*mapsize+y-1);
            grid[x][y]->setGeometry(50+y*50,10+x*50,50,50);
            grid[x][y]->setIcon(key[flag]);
            map[x][y]=flag;
            grid[x][y]->setIconSize(QSize(40,40));
        }
    }
    connect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(click(int)));

    //倒计时
    i = 0;
    QPixmap monkey(":/new/jpg/source/animal/time2.png");
    monkey = monkey.scaled(ui->Monkey->width(),ui->Monkey->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->Monkey->setPixmap(monkey);
    ui->Monkey->show();
    QPixmap branch(":/new/jpg/source/animal/time1.png");
    branch = branch.scaled(ui->Branch->width(),ui->Branch->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->Branch->setPixmap(branch);
    ui->Branch->show();

    ui->TimeLeft->setStyleSheet("border:1px solid #FFFFFF;"
                                "border-radius:10px;"
                                "background-color: #ffffff;"
                );
    QFont font("Courier",16);
    ui->TimeLeft->setFont(font);
    percent = 1000;
    qti = new QTimer(this);\
    qti->start(100);

    connect(qti, SIGNAL(timeout()),this,SLOT(time_out()));

//    //倒计时
//    ui->TimeLeftBar->setTextVisible(false);
//    ui->TimeLeftBar->setStyleSheet(
//                    "QProgressBar{border:1px solid #FFFFFF;"
//                                   "border-radius:10px;}"
//                    "QProgressBar::chunk{\
//                       border:1px solid #FFFFFF;\
//                       border-radius: 8px; \
//                       background:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 red,stop:1 blue);}"
//                );
//    ui->TimeLeft->setStyleSheet("border:1px solid #FFFFFF;"
//                                "border-radius:10px;"
//                                "background-color: #ffffff;"

//            );
//    QFont font("Courier",16);
//    ui->TimeLeft->setFont(font);
//    percent = 1000;
//    qti = new QTimer(this);\
//    qti->start(100);


//    connect(qti, SIGNAL(timeout()),this,SLOT(time_out()));

    //连线
    for(int i=0;i<11;i++){
        QString filename;
        filename = ":/new/jpg/source/连线/"+QString::number(i)+".png";
        line_icon[i].load(filename);
    }
    QImage test;
    test.load(":/new/jpg/source/连线/"+QString::number(10)+".jpg");
    for(int i = 0;i<mapsize+2;i++){
        for(int j = 0;j<mapsize+2;j++){
            line[i][j] = new QLabel(this);
            line[i][j]->setGeometry(50+j*50,10+i*50,50,50);
            line[i][j]->setPixmap(QPixmap::fromImage(test));
            line[i][j]->hide();
        }
    }

    soundPlayer =new QMediaPlayer();
    soundPlayer->setMedia(QUrl("qrc:/new/jpg/source/音乐/消除声.mp3"));
    QFont q1("Ink Free",14,100);
    ui->label_3->setFont(q1);
}

void Gaming::time_out(){

    --percent;
        if(i<1000){
            ui->Monkey->setGeometry(580-0.49*(1000-percent),10,80,50);
            ui->Monkey->show();
            i++;
        }
     //   ui->TimeLeftBar->setValue(percent/10);
        QString tl;
        tl = QString::number(percent/10) + " s";
        ui->TimeLeft->setText(tl);
        if(percent<=0){
            qti->stop();

            g = new Grade(this,0,point);
            g->show();
            disconnect(qti, SIGNAL(timeout()),this,SLOT(time_out()));
            this->close();
            this->parent->show();
            //percent = 1000;
        }
//    percent-=1;
//    ui->TimeLeftBar->setValue(percent/10);
//    QString tl;
//    tl = QString::number(percent/10) + " s";
//    ui->TimeLeft->setText(tl);
//    if(percent<=0){
//        qti->stop();

//        g= new Grade(this,0,point);
//        g->show();
//        disconnect(qti, SIGNAL(timeout()),this,SLOT(time_out()));
//        this->close();
//        this->parent->show();
//    }

}

void Gaming::buttonFlash(int id,int size1,int size2){ //棋子动画
    buttonGroup->button(id)->setIconSize(QSize(size1,size1));

    QTime delayTime = QTime::currentTime().addMSecs(100);           //延迟
    while( QTime::currentTime() < delayTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    buttonGroup->button(id)->setIconSize(QSize(size2,size2));
}
bool Gaming::lineTo3(int x, int y, int a, int b){
    addPoint(&p3,x,y);
    for(int i=x-1;i>=0;i--){
        if(map[i][y]==-1){
            if(lineTo2(i,y,a,b)){
                return true;
            }
            addPoint(&p3,i,y);
            continue;
        }
        else break;
    }
    p3.clear();
    addPoint(&p3,x,y);
    for(int j=y-1;j>=0;j--){
        if(map[x][j]==-1){
            if(lineTo2(x,j,a,b))
                return true;
            addPoint(&p3,x,j);
            continue;
        }
        else break;
    }
    p3.clear();
    addPoint(&p3,x,y);
    for(int i=x+1;i<=mapsize+1;i++){
        if(map[i][y]==-1){
            if(lineTo2(i,y,a,b))
                return true;
            addPoint(&p3,i,y);
            continue;
        }
        else break;
    }
    p3.clear();
    addPoint(&p3,x,y);
    for(int j=y+1;j<=mapsize+1;j++){
        if(map[x][j]==-1){
            if(lineTo2(x,j,a,b))
                return true;
            addPoint(&p3,x,j);
            continue;
        }
        else break;
    }
    p3.clear();
    return false;
}
bool Gaming::lineTo2(int x, int y, int a, int b){
    addPoint(&p2,x,y);
    for(int i=x-1;i>=0;i--){
        if(map[i][y]==-1){
            if(lineTo1(i,y,a,b))
                return true;
            addPoint(&p2,i,y);
            continue;
        }
        else break;
    }
    p2.clear();
    addPoint(&p2,x,y);
    for(int j=y-1;j>=0;j--){
        if(map[x][j]==-1){
            if(lineTo1(x,j,a,b))
                return true;
            addPoint(&p2,x,j);
            continue;
        }
        else break;
    }
    p2.clear();
    addPoint(&p2,x,y);
    for(int i=x+1;i<=mapsize+1;i++){
        if(map[i][y]==-1){
            if(lineTo1(i,y,a,b))
                return true;
            addPoint(&p2,i,y);
            continue;
        }
        else break;
    }
    p2.clear();
    addPoint(&p2,x,y);
    for(int j=y+1;j<=mapsize+1;j++){
        if(map[x][j]==-1){
            if(lineTo1(x,j,a,b))
                return true;
            addPoint(&p2,x,j);
            continue;
        }
        else break;
    }
    p2.clear();
    return false;
}
bool Gaming::lineTo1(int x, int y, int a, int b){
    addPoint(&p1,x,y);
    if(x!=a&&y!=b)
        return false;
    for(int i=x-1;i>=0;i--){
        if(map[i][y]==-1){
            addPoint(&p1,i,y);
            continue;
        }
        else if(i==a&&y==b){
            addPoint(&p1,i,y);
            return true;
        }
        else break;
    }
    p1.clear();
    addPoint(&p1,x,y);
    for(int j=y-1;j>=0;j--){
        if(map[x][j]==-1){
            addPoint(&p1,x,j);
            continue;
        }
        else if(x==a&&j==b){
            addPoint(&p1,x,j);
            return true;
        }
        else break;
    }
    p1.clear();
    addPoint(&p1,x,y);
    for(int i=x+1;i<=mapsize+1;i++){
        if(map[i][y]==-1){
            addPoint(&p1,i,y);
            continue;
        }
        else if(i==a&&y==b){
            addPoint(&p1,i,y);
            return true;
        }
        else break;
    }
    p1.clear();
    addPoint(&p1,x,y);
    for(int j=y+1;j<=mapsize+1;j++){
        if(map[x][j]==-1){
            addPoint(&p1,x,j);
            continue;
        }
        else if(x==a&&j==b){
            addPoint(&p1,x,j);
            return true;
        }
        else break;
    }
    p1.clear();
    return false;
}
bool Gaming::checkLineTo(int x1,int y1,int x2,int y2){         //能否消掉
    if(map[x1][y1]!=map[x2][y2])
        return false;
    if(lineTo1(x1,y1,x2,y2)||lineTo2(x1,y1,x2,y2)||lineTo3(x1,y1,x2,y2))
    {
        percent+=10;
        ui->Monkey->setGeometry(580-0.49*(1000-percent),10,80,50);
        showLine();
        return true;
    }
    return false;
}
void Gaming::winGame(){
    //QMessageBox::information(this, "Win", "You are the winner!\nAnd your score is "+QString::number(point, 10), QMessageBox::Ok, QMessageBox::Ok);
    g= new Grade(this,1,point);
    g->show();
    this->close();
    parent->show();
}
void Gaming::click(int id)
{

    if(first==-1){      //选中第一个棋子
        buttonFlash(id,60,50);
        first=id;
        int x3=first/mapsize;
        int y3=first%mapsize+1;
        line[x3][y3]->setPixmap(QPixmap::fromImage(line_icon[10]));
        line[x3][y3]->show();
    }
    else if(second==-1&&first!=id){          //选中第二个棋子进行判断
        buttonFlash(id,60,50);
        second=id;
        int x1=first/mapsize;
        int y1=first%mapsize+1;
        int x2=second/mapsize;
        int y2=second%mapsize+1;
        if(checkLineTo(x1,y1,x2,y2)){              //可以消掉
            buttonGroup->button(first)->hide();
            buttonGroup->button(second)->hide();
            map[first/mapsize][first%mapsize+1]=-1;
            map[second/mapsize][second%mapsize+1]=-1;
            first=-1;
            second=-1;
            numButton-=2;
            point+=50;
            pstring=QString::number(point, 10);
            ui->label_3->setText(pstring);
            soundPlayer->play();
            if(numButton==0)
                winGame();
        }
        else{                       //还原一二棋子
            buttonFlash(first,60,40);
            buttonFlash(second,60,40);
            line[first/mapsize][first%mapsize+1]->hide();
            first=-1;
            second=-1;
        }
        p1.clear();
        p2.clear();
        p3.clear();
    }
    else if(first==id){        //重复选取取消
        buttonFlash(id,60,40);
        line[first/mapsize][first%mapsize+1]->hide();
        first=second;
        second=-1;
    }
    else{
        line[first/mapsize][first%mapsize+1]->hide();
        buttonFlash(id,50,40);
    }

}

Gaming::~Gaming()
{
    delete ui;
    delete buttonGroup;
    delete qti;
    for(int i=0;i<=mapsize;i++){
        for(int j=0;j<=mapsize;j++){
            delete grid[i][j];
            delete line[i][j];
        }
    }
}

void Gaming::on_pushButton_2_clicked()        //提示
{
    point-=25;
    if(point<0)
        point=0;
    pstring=QString::number(point, 10);
    ui->label_3->setText(pstring);
    if(isSound==1)
        buttonSound2->play();
    for(int i=1;i<=mapsize;i++){
        for(int j=1;j<=mapsize;j++){
            if(map[i][j]!=-1){
                for(int k=i;k<=mapsize;k++){
                    for(int m=1;m<=mapsize;m++){
                        if(i==k&&j==m) continue;
                        if(checkLineTo(i,j,k,m)){
                            buttonFlash(i*mapsize+j-1,80,50);
                            buttonFlash(k*mapsize+m-1,80,50);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void Gaming::showLine(){
    Point tempPointa;
    Point tempPointb;
    Point tempPointc;
    std::vector<Point> Path;
    while(!p1.empty()){
        tempPointa=p1.back();
        Path.push_back(tempPointa);
        p1.pop_back();
    }
    while(!p2.empty()){
        tempPointa=p2.back();
        Path.push_back(tempPointa);
        p2.pop_back();
    }
    while(!p3.empty()){
        tempPointa=p3.back();
        Path.push_back(tempPointa);
        p3.pop_back();
    }
    if(Path.size()==2){
        if(Path[0].x==Path[1].x){
            if(Path[0].y>Path[1].y){
                line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[0]));
                line[Path[1].x][Path[1].y]->setPixmap(QPixmap::fromImage(line_icon[2]));
            }
            if(Path[0].y<Path[1].y){
                line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[2]));
                line[Path[1].x][Path[1].y]->setPixmap(QPixmap::fromImage(line_icon[0]));
            }
        }
        if(Path[0].y==Path[1].y){
            if(Path[0].x>Path[1].x){
                line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[1]));
                line[Path[1].x][Path[1].y]->setPixmap(QPixmap::fromImage(line_icon[3]));
            }
            if(Path[0].x<Path[1].x){
                line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[3]));
                line[Path[1].x][Path[1].y]->setPixmap(QPixmap::fromImage(line_icon[1]));
            }
        }
        line[Path[0].x][Path[0].y]->show();
        line[Path[1].x][Path[1].y]->show();
        QTime delayTime = QTime::currentTime().addMSecs(300);           //延迟
        while( QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 300);

        for(int i = 0;i<mapsize+2;i++)
            for(int j = 0;j<mapsize+2;j++)
                line[i][j]->hide();
        return;
    }/////////////////

    if(Path[0].x==Path[1].x){
        if(Path[0].y>Path[1].y){
            line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[0]));
        }
        if(Path[0].y<Path[1].y){
            line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[2]));
        }
    }//////
    if(Path[0].y==Path[1].y){
        if(Path[0].x>Path[1].x){
            line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[1]));//
        }
        if(Path[0].x<Path[1].x){
            line[Path[0].x][Path[0].y]->setPixmap(QPixmap::fromImage(line_icon[3]));
        }
    }
    line[Path[0].x][Path[0].y]->show();

    for(int i=1;i<Path.size()-1;i++){
        if(Path[i-1].x==Path[i+1].x)
            line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[8]));
        if(Path[i-1].y==Path[i+1].y)
            line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[9]));//

        if(Path[i-1].x<Path[i+1].x)
            if(Path[i-1].y<Path[i+1].y){
            if(Path[i].x==Path[i-1].x&&Path[i].y==Path[i+1].y)
                line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[7]));
            else if(Path[i].y==Path[i-1].y&&Path[i].x==Path[i+1].x)
                line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[5]));
            }

        if(Path[i-1].x<Path[i+1].x)
            if(Path[i-1].y>Path[i+1].y){
                if(Path[i].x==Path[i-1].x&&Path[i].y==Path[i+1].y)
                    line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[6]));
                else if(Path[i].y==Path[i-1].y&&Path[i].x==Path[i+1].x)
                    line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[4]));
                }

        if(Path[i-1].x>Path[i+1].x)
            if(Path[i-1].y>Path[i+1].y){
                if(Path[i].x==Path[i-1].x&&Path[i].y==Path[i+1].y)
                    line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[5]));
                else if(Path[i].y==Path[i-1].y&&Path[i].x==Path[i+1].x)
                    line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[7]));
                }

        if(Path[i-1].x>Path[i+1].x)
            if(Path[i-1].y<Path[i+1].y){
                if(Path[i].x==Path[i-1].x&&Path[i].y==Path[i+1].y)
                    line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[4]));
                else if(Path[i].y==Path[i-1].y&&Path[i].x==Path[i+1].x)
                    line[Path[i].x][Path[i].y]->setPixmap(QPixmap::fromImage(line_icon[6]));
                }
        line[Path[i].x][Path[i].y]->show();
    }
    int m=Path.size()-2;
    int n=Path.size()-1;
    if(Path[m].x==Path[n].x){
        if(Path[m].y>Path[n].y){
            line[Path[n].x][Path[n].y]->setPixmap(QPixmap::fromImage(line_icon[2]));
        }
        if(Path[m].y<Path[n].y){
            line[Path[n].x][Path[n].y]->setPixmap(QPixmap::fromImage(line_icon[0]));//
        }
    }
    if(Path[m].y==Path[n].y){
        if(Path[m].x>Path[n].x){
            line[Path[n].x][Path[n].y]->setPixmap(QPixmap::fromImage(line_icon[3]));
        }
        if(Path[m].x<Path[n].x){
            line[Path[n].x][Path[n].y]->setPixmap(QPixmap::fromImage(line_icon[1]));
        }
    }
    line[Path[n].x][Path[n].y]->show();

    QTime delayTime = QTime::currentTime().addMSecs(300);           //延迟
    while( QTime::currentTime() < delayTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents, 300);

    for(int i = 0;i<mapsize+2;i++)
        for(int j = 0;j<mapsize+2;j++)
            line[i][j]->hide();
}

void Gaming::addPoint(std::vector<Point> *p,int x,int y){
    Point tempPoint;
    tempPoint.x=x;
    tempPoint.y=y;
    p->push_back(tempPoint);
}


void Gaming::on_pushButton_4_clicked()   //返回按钮
{
    if(isSound==1)
        buttonSound2->play();
    disconnect(qti, SIGNAL(timeout()),this,SLOT(time_out()));
    disconnect(buttonGroup,SIGNAL(buttonClicked(int)),this,SLOT(click(int)));
    this->close();
    parent->show();

}

void Gaming::on_pushButton_3_clicked()  //重新生成
{
    if(isSound==1)
        buttonSound2->play();
    disconnect(qti, SIGNAL(timeout()),this,SLOT(time_out()));
    this->close();
    newGame = new Gaming(this->parent);
    newGame->show();
}

void Gaming::closeEvent(QCloseEvent *event)
{
    //TODO: 在退出窗口之前，实现希望做的操作

    parent->showNormal();
    disconnect(qti, SIGNAL(timeout()),this,SLOT(time_out()));
}

void Gaming::on_pushButton_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    if(pause==0){
        qti->start();
        pause=1;
        ui->pushButton->setIcon(pIcon[0]);
    }else if(pause==1){
        qti->stop();
        pause=0;
        ui->pushButton->setIcon(pIcon[1]);
    }

}

void Gaming::on_pushButton_pressed()
{
    if(pause==0)
        ui->pushButton->setIcon(pIcon[3]);
    else if(pause==1)
        ui->pushButton->setIcon(pIcon[2]);
}

void Gaming::on_pushButton_released()
{
    if(pause==1){
        ui->label_4->show();
        qm->start();
        for(int i=14;i<210;i++)
            buttonGroup->button(i)->lower();
    }else if(pause==0){
        ui->label_4->hide();
        for(int i=14;i<210;i++)
            buttonGroup->button(i)->raise();
        for(int i = 0;i<mapsize+2;i++)
            for(int j = 0;j<mapsize+2;j++)
                line[i][j]->raise();
    }
}

void Gaming::on_pushButton_5_clicked()
{
    if(isSound==1)
        buttonSound2->play();
    if(isMusic){
        isMusic=false;
        musicPlayer->stop();
    }else{
        isMusic=true;
        musicPlayer->play();
    }
}

void Gaming::on_pushButton_2_pressed()
{
    ui->pushButton_2->setIcon(bIcon[0]);
    ui->pushButton_2->setIconSize(QSize(200,200));
}

void Gaming::on_pushButton_2_released()
{
    ui->pushButton_2->setIcon(bIcon[4]);
    ui->pushButton_2->setIconSize(QSize(95,95));
}

void Gaming::on_pushButton_3_pressed()
{
    ui->pushButton_3->setIcon(bIcon[1]);
    ui->pushButton_3->setIconSize(QSize(200,200));
}

void Gaming::on_pushButton_3_released()
{
    ui->pushButton_3->setIcon(bIcon[5]);
    ui->pushButton_3->setIconSize(QSize(95,95));
}

void Gaming::on_pushButton_4_pressed()
{
    ui->pushButton_4->setIcon(bIcon[2]);
    ui->pushButton_4->setIconSize(QSize(200,200));
}

void Gaming::on_pushButton_4_released()
{
    ui->pushButton_4->setIcon(bIcon[6]);
    ui->pushButton_4->setIconSize(QSize(95,95));
}

void Gaming::on_pushButton_5_pressed()
{
    ui->pushButton_5->setIcon(bIcon[3]);
    ui->pushButton_5->setIconSize(QSize(200,200));
}

void Gaming::on_pushButton_5_released()
{
    ui->pushButton_5->setIcon(bIcon[7]);
    ui->pushButton_5->setIconSize(QSize(95,95));
}

void Gaming::mouseMoveEvent(QMouseEvent *e){
    int x=e->x();
    int y=e->y();
    if(x>70&x<165&&y>790&&y<875){
        ui->pushButton_2->setIcon(bIcon[0]);
        ui->pushButton_3->setIcon(bIcon[5]);
        ui->pushButton_4->setIcon(bIcon[6]);
        ui->pushButton_5->setIcon(bIcon[7]);
        ui->pushButton_2->setIconSize(QSize(200,200));
        ui->pushButton_3->setIconSize(QSize(95,95));
        ui->pushButton_4->setIconSize(QSize(95,95));
        ui->pushButton_5->setIconSize(QSize(95,95));
    }else if(x>297&&x<393&&y>790&&y<875){
        ui->pushButton_2->setIcon(bIcon[4]);
        ui->pushButton_3->setIcon(bIcon[1]);
        ui->pushButton_4->setIcon(bIcon[6]);
        ui->pushButton_5->setIcon(bIcon[7]);
        ui->pushButton_2->setIconSize(QSize(95,95));
        ui->pushButton_3->setIconSize(QSize(200,200));
        ui->pushButton_4->setIconSize(QSize(95,95));
        ui->pushButton_5->setIconSize(QSize(95,95));
    }else if(x>515&&x<610&&y>790&&y<875){
        ui->pushButton_2->setIcon(bIcon[4]);
        ui->pushButton_3->setIcon(bIcon[5]);
        ui->pushButton_4->setIcon(bIcon[2]);
        ui->pushButton_5->setIcon(bIcon[7]);
        ui->pushButton_2->setIconSize(QSize(95,95));
        ui->pushButton_3->setIconSize(QSize(95,95));
        ui->pushButton_4->setIconSize(QSize(200,200));
        ui->pushButton_5->setIconSize(QSize(95,95));
    }else if(x>742&&x<837&&y>790&&y<875){
        ui->pushButton_2->setIcon(bIcon[4]);
        ui->pushButton_3->setIcon(bIcon[5]);
        ui->pushButton_4->setIcon(bIcon[6]);
        ui->pushButton_5->setIcon(bIcon[3]);
        ui->pushButton_2->setIconSize(QSize(95,95));
        ui->pushButton_3->setIconSize(QSize(95,95));
        ui->pushButton_4->setIconSize(QSize(95,95));
        ui->pushButton_5->setIconSize(QSize(200,200));
    }else{
        ui->pushButton_2->setIcon(bIcon[4]);
        ui->pushButton_3->setIcon(bIcon[5]);
        ui->pushButton_4->setIcon(bIcon[6]);
        ui->pushButton_5->setIcon(bIcon[7]);
        ui->pushButton_2->setIconSize(QSize(95,95));
        ui->pushButton_3->setIconSize(QSize(95,95));
        ui->pushButton_4->setIconSize(QSize(95,95));
        ui->pushButton_5->setIconSize(QSize(95,95));
    }
}
