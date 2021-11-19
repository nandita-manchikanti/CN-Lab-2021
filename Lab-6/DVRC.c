#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int c_socket;
struct node
{
	unsigned dist[20];
	unsigned from[20];
}rt[10];

int ClientCreate(int port, int anyip, char IPADDR[])		// Return 1 for error
{
	c_socket = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(port);
	if(anyip == 0) client.sin_addr.s_addr = inet_addr(IPADDR);
	else client.sin_addr.s_addr = INADDR_ANY;
	if(connect(c_socket, (struct sockaddr *)&client, sizeof(client)) == -1)
	{
		printf("Connection Issue.\n");
		return 1;
	}
	else return 0;
}

int main(){
        printf("----------------------CRC TCP/IP Transmitter-----------------------------\n");

	int error = ClientCreate(9009, 1, "");
	if(error == 1)
	{
		close(c_socket);
		printf("Connection Issue.\n");
		return 0;
	}
	else 
	{
        int n;
        read(c_socket,&n,sizeof(int));
        for(int i=0;i<n;i++){
            int n=read(c_socket,&rt[i],sizeof(struct node));
            if(n<0){
                    printf("Error in reading");
                    exit(1);
            }
        }

        for(int i=0;i<n;i++)
        {
            printf("\nDistance Vector for router %d is \n",i+1);
            printf("\n Destination\tDistance\tNexthop\n");
            for(int j=0;j<n;j++)
            {
                printf("\t%d\t%d\t\t%d\n",j+1,rt[i].dist[j],rt[i].from[j]+1);
            }
        }	
        
        close(c_socket);
        return 0;
    }
}


