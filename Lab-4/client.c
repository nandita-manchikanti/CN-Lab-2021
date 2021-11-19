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
                int dataatrec[10];
                int p,p1,p2,p3;
                printf("The data received is :\n");
                printf("D7 D6 D5 D4 D3 D2 D1\n");
                for(int i=0;i<7;i++){
                        int n=read(c_socket,&dataatrec[i],sizeof(int));
                        if(n<0){
                                printf("Error in reading");
                                exit(1);
                        }
                        printf("%d  ",dataatrec[i]);
                }

                p1=dataatrec[6]^dataatrec[4]^dataatrec[2]^dataatrec[0];
                p2=dataatrec[5]^dataatrec[4]^dataatrec[1]^dataatrec[0];
                p3=dataatrec[3]^dataatrec[2]^dataatrec[1]^dataatrec[0];
                p=p3*4+p2*2+p1 ;

                if(p==0) {
                        printf("\nNo error while transmission of data\n");
                }
                else {     
                printf("\nError on position %d",p);
        
                printf("\nCorrect message is :\n");
                //if errorneous bit is 0 we complement it else vice versa
                if(dataatrec[7-p]==0)
                dataatrec[7-p]=1;
                        else
                dataatrec[7-p]=0;
                printf("D7 D6 D5 D4 D3 D2 D1\n");
                for (int i=0;i<7;i++) {
                printf(" %d ",dataatrec[i]);
                }
                printf("\n");
                close(c_socket);
                return 0;
                }
        }
}


