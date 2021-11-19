#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
 int main()
{
int c_sock;
char buf[100];
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
recv(c_sock,buf,sizeof(buf),0);
printf("message from server:%s",buf);

return 0;
}
