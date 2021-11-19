#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#define MAX_LIMIT 100

int main()
{
    int s_sock;
    int c_socket;
    char buff[MAX_LIMIT];
    char receive[MAX_LIMIT];
    s_sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server,other;
    memset(&server,0,sizeof(server));
    memset(&other,0,sizeof(other));
    server.sin_family=AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;
    socklen_t add;
    bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    listen(s_sock,5);
    add=sizeof(other);
    while(c_socket=accept(s_sock,(struct sockaddr*)&other,&add)){
        printf("Enter a message and -1 to close connection:");
        fgets(buff, MAX_LIMIT, stdin);
        if(buff=="-1"){
            exit(0);
        }
        send(c_socket, buff,sizeof(buff), 0);
        recv(c_socket,receive,sizeof(receive),0);
        printf("message from client:%s",receive);
    }
    return 0;
}
