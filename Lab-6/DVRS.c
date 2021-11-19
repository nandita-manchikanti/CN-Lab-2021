#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int s_socket, c_socket;

struct node
{
	unsigned dist[20];
	unsigned from[20];
}rt[10];

int distancemat[20][20];
int n,i,j,k,count=0;

int ServerCreate(int port)		// Return 1 for error
{
	s_socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in server, other;
	memset(&server, 0, sizeof(server));
	memset(&other, 0, sizeof(other));

	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	
	if(bind(s_socket, (struct sockaddr*)&server, sizeof(server)) != -1)
	{
		printf("Server Running.....\n");
		listen(s_socket, 5);
		socklen_t add;
		add = sizeof(other);
		c_socket = accept(s_socket, (struct sockaddr*)&other, &add);
		return 0;
	}
	else
	{
		printf("\nError in Bind.\n");
		return 1;
	} 
}

int main(){
printf("----------------------CRC TCP/IP Receiver-----------------------------\n");

	int error = ServerCreate(9009);
	if(error == 1)
	{
		close(c_socket);
		close(s_socket);
		printf("Server Binding Issue.\n");
		return 0;
	}
	else 
	{
		printf("\nServer Waiting...\n");
        int n;
        printf("\nEnter the number of nodes : ");
        scanf("%d",&n);

        printf("\nEnter the cost matrix :\n");
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {	
                scanf("%d",&distancemat[i][j]);
                distancemat[i][i]=0;
                rt[i].dist[j]=distancemat[i][j];
                rt[i].from[j]=j;
            }
        }
        do
        {	
            count=0;
            for(i=0;i<n;i++){
                for(j=0;j<n;j++){
                    for(k=0;k<n;k++){
                        if(rt[i].dist[j] > distancemat[i][k] + rt[k].dist[j])
                        {
                            rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
                            rt[i].from[j]=k;
                            count++;
                        }
                    }
                }
            }
        }while(count!=0);
        write(c_socket,&n,sizeof(int));
        for(int i=0;i<n;i++)
        {
            int x=write(c_socket,&rt[i], sizeof(struct node));
            if(x<0){
                printf("Write error\n");
            }
        }

        close(c_socket);
        close(s_socket);
    }
        return 0;
        
}