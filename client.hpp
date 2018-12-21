#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <cstdio>
#include <string.h>
#include <iostream>
#include<WINSOCK2.H>
#include<string.h>
#include <cstdlib>
#include <cstring>
#include<STDIO.H>
#include<windows.h>
#include<WS2tcpip.h>
#include <QString>
#include <string>
#include <QMessageBox>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

class Client {
public:
    Client(const string host, const int port);
    ~Client();
    void senddata(const char* text);
    void receive(QString* list);
    QString getRank();
private:
    const string host;
    const int port;
    SOCKET sockClient;
    struct sockaddr_in address;
    int sock,valread;
    struct sockaddr_in serv_addr;
    char buffer[512];
};
#endif
