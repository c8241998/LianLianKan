#include"server.hpp"
bool cmp(node a,node b){
        return a.point>b.point;
}
void work(int socket){
        while(1){
                num++;
                valread=recv(socket, buffer, 14, 0);
                if(strcmp(buffer,"**************")==0)
                        break;
                if(strcmp(buffer,"##############")==0){
                        string temp;
                        for(int i=1;i<=6;i++){
                                temp+=record[i].name;
                                temp+='*';
                                temp+=to_string(record[i].point);
                                temp+='*';
                        }
                        cout<<temp<<endl;
                        send(socket, temp.c_str() , 140 , 0);
                        break;
                }
                for(int i=0;i<10;i++){
                        if(buffer[i]!='*')
                             record[num].name+=buffer[i];
                        else break;   
                }
                for(int i=10;i<14;i++){
                        record[num].point=record[num].point*10+buffer[i]-'0';
                }
                int point = record[num].point;
                sort(record+1,record+num+1,cmp);
                int rank;
                for(int i=1;i<=num;i++){
                        if(record[i].point==point){
                                rank=i;
                                break;
                        }
                }
                string temp = to_string(rank);
                send(socket, temp.c_str() , temp.size()+1 , 0);
        }
}

int main(){
        
        num=0;
        valread=1;
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
        {
                cout<<"fail!"<<endl;
        }

        listen(server_fd, 1000);

        while(1){
                new_socket = accept(server_fd, (struct sockaddr *)&(address), (socklen_t*)&(addrlen));
                thread th(work,new_socket);
                th.detach();
        }
	
	return 0;
}

