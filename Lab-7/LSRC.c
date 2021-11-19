#include<stdio.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define INFINITY 9999
#define MAX 10

int G[MAX][MAX],i,j,n,u;
int c_socket;
void dijkstra(int G[MAX][MAX],int n,int startnode)
{
    int cost[MAX][MAX],distance[MAX],pred[MAX];
    int visited[MAX],count,mindistance,nextnode,i,j;
    //pred[] stores the predecessor of each node
    //count gives the number of nodes seen so far
    //create the cost matrix
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(G[i][j]==0)
                cost[i][j]=INFINITY;
            else
                cost[i][j]=G[i][j];
        }
    }

    //initialize pred[],distance[] and visited[]
    for(i=0;i<n;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }
    distance[startnode]=0;
    visited[startnode]=1;
    count=1;
    while(count<n-1)
    {
        mindistance=INFINITY;
        //nextnode gives the node at minimum distance
        for(i=0;i<n;i++){
            if(distance[i]<mindistance&&!visited[i]){
                mindistance=distance[i];
                nextnode=i;
            }
        }
        //check if a better path exists through nextnode
        visited[nextnode]=1;
        for(i=0;i<n;i++){
            if(!visited[i]){
                if(mindistance+cost[nextnode][i]<distance[i]){
                    distance[i]=mindistance+cost[nextnode][i];
                    pred[i]=nextnode;
                }
            }
        }
        count++;
    }
    
    //print the path and distance of each node
    for(i=0;i<n;i++){
        if(i!=startnode){
            printf("\nDistance of node %d from %d = %d",i+1,startnode+1,distance[i]);
            printf("\nPath=%d",i+1);
            j=i;
            do{
                j=pred[j];
                printf("<-%d",j);
            }while(j!=startnode);
        }
    }
    printf("\n");
}

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
            for(int j=0;j<n;j++){
                read(c_socket,&G[i][j],sizeof(int));
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                printf("%d ",G[i][j]);
            }
        }

        for(int i=0;i<n;i++){
            dijkstra(G,n,i);
        }

        close(c_socket);
        return 0;
    }
}


