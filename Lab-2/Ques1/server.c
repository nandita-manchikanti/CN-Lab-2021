#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>

int main()
{
    int s_sock;
    int c_socket;
    char buf[100]="hello client";
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
    c_socket=accept(s_sock,(struct sockaddr*)&other,&add);
    send(c_socket,buf,sizeof(buf),0);
    return 0;
}
