#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <string.h>
#include <pthread.h>
#include <algorithm>
using namespace std;

struct node{
    string name="";
    int point=0;
}record[10000];

int num=10;
const int port=8082;
int server_fd,new_socket,valread;
struct sockaddr_in address;
int addrlen;
int opt;
char buffer[512];
