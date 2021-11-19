//implement hamming code 
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

        int data[10];
        printf("Enter 4 bits of data one by one\n");
        scanf("%d",&data[0]);
        scanf("%d",&data[1]);
        scanf("%d",&data[2]);
        scanf("%d",&data[4]);
    

        data[6]=data[0]^data[2]^data[4];
        data[5]=data[0]^data[1]^data[4];
        data[3]=data[0]^data[1]^data[2];

        printf("\nEncoded data is :\n");
        printf("D7 D6 D5 D4 D3 D2 D1\n");
        for(int i=0;i<7;i++){
            printf(" %d ",data[i]);
        }
        
        int n;
        printf("\nEnter the bit number to be changed : ");
        scanf("%d",&n);
        n=abs(n-7);
        data[n]=1-data[n];

        for(int i=0;i<7;i++)
        {
            n=write(c_socket,&data[i], sizeof(int));
            if(n<0){
                printf("Write error\n");
            }
        }

        printf("Data sent is \n");
        printf("D7 D6 D5 D4 D3 D2 D1\n");
        for(int i=0;i<7;i++)
        {
            printf(" %d ",data[i]);
        }

        printf("\n");
        close(c_socket);
        close(s_socket);
    }
        return 0;
        
}