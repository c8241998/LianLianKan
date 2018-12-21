#include"client.hpp"
Client:: Client(const string host, const int port):host(host),port(port){

    WORD wVersionRequested;
    WSAData wsaData;
    int err;
    printf("This is a Client side application!\n");
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if(err != 0) {
        //Tell the user that we could not find a usable WinSock Dll.
        printf("WSAStartup() called failed!\n");
        QMessageBox::information(NULL, "fail","网络连接失败", QMessageBox::Ok, QMessageBox::Ok);
    } else {
        printf("WSAStartup called successful!\n");
    }
    if(LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        //Tell the user that we could not find a usable WinSock Dll.
        WSACleanup();
    }
    //The WinSock Dll is acceptable. Proceed
    //创建套接字
    sockClient = socket(AF_INET, SOCK_STREAM, 0);
    if(sockClient == INVALID_SOCKET) {
        printf("socket() called failed!, error code is %d\n", WSAGetLastError());
        QMessageBox::information(NULL, "fail","网络连接失败", QMessageBox::Ok, QMessageBox::Ok);
    } else {
        printf("socket() called successful!\n");
    }
    //需要连接的服务端套接字结构信息
    SOCKADDR_IN addrServer;
    //设定服务器IP
    addrServer.sin_addr.S_un.S_addr = inet_addr(host.c_str());
    addrServer.sin_family = AF_INET;
    //设定服务器的端口号(使用网络字节序)
    addrServer.sin_port = htons(port);
    //向服务器发出连接请求
    err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));
    if(err == SOCKET_ERROR) {
        printf("connect() called failed! The error code is %d\n", WSAGetLastError());
        QMessageBox::information(NULL, "fail","网络连接失败", QMessageBox::Ok, QMessageBox::Ok);
    } else {
        printf("connect() called successful\n");
    }
}
void Client::senddata(const char* text){
           send(sockClient,text,14,0);
}
void Client::receive(QString list[]){
           char buf[512];
           recv(sockClient,buf,sizeof buf,0);
           string ss = buf;
           QString s ="";
           for(int i=0;i<ss.size();i++)
               s+=ss[i];
           for(int i=1;i<=6;i++){
               QString name=s.section('*',i*2-2,i*2-2);
               QString point=s.section('*',i*2-1,i*2-1);
               list[i]=name;
               list[i+6]+=point;
               }
}
QString Client::getRank(){
    char buf[512];
    recv(sockClient,buf,4,0);
    string ss = buf;
    QString s ="";
    for(int i=0;i<ss.size();i++)
        s+=ss[i];
    return s;
}
Client:: ~Client(){
        closesocket(sockClient);
        WSACleanup();
}
