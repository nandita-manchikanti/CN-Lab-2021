#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define MAX_LIMIT 100
 int main()
{
    int c_sock;
    char buf[MAX_LIMIT];
    char receive[MAX_LIMIT];
    c_sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in client;
    memset(&client,0,sizeof(client));  // optional
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;
    if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
    {
        printf("error in connection");
        return 0;
    }
    while(1){
        recv(c_sock,receive,sizeof(receive),0);
        printf("message from server:%s",receive);
        printf("Enter a message and -1 to close connection:");
        fgets(buf, MAX_LIMIT, stdin);
        if(buf=="-1"){
            exit(0);
        }
        send(c_sock, buf,sizeof(buf), 0);
    }
    //recv(c_sock,buf,sizeof(buf),0);
    //printf("message from server:%s",buf);
    return 0;
}
