#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define numpackets 10

int main(){

    int packets[numpackets]={0,1,2,3,4,5,6,7,8,9};
    srand(time(0));
    int windowsize;

    printf("Enter size of window:");
    scanf("%d",&windowsize);

    int sent=0;
    int rec=0;
    int temp;
    int propagation_delay=10;
    int round_trip_time=2*propagation_delay;
    int timeout_timer=2*round_trip_time;

    while (rec<numpackets)
    {
    	int i;
        printf("Sent %d rec %d\n",sent,rec);
        int framectr=0;
        printf("Sending frames:");
        for (i = sent; i < sent+windowsize; i++)
        {
            if (i>=numpackets)
            {
                break;
            }
            printf("Frame %d ",i);
            framectr++;
        }
        printf("\n");

        temp=sent;
        int arr[windowsize];
        int all_done=0;
        for ( i = 0; i < framectr; i++)
        {
            arr[i]=-1;//-1 implies not recieved,thus sorting is achieved,by indexing
        }
        while (!all_done)
        {
            int not_done_ctr=0;
            for ( i = temp; i < temp+framectr; i++)
            {
                int time_taken_for_ack=0;
                while (time_taken_for_ack<=round_trip_time)
                {
                    time_taken_for_ack=rand()%((4*timeout_timer)/3);
                }
                if (arr[i-temp]==-1 && time_taken_for_ack>timeout_timer)
                //frame has not been recieved before and still doesnt come on time
                {
                    printf("Negative Ack recieved for frame  %d so sending it again. \n",i);
                }
                else if(arr[i-temp]==-1)//frame has not been recieved before but it is now.
                {
                    printf("Ack recieved for frame %d.\n",i);
                    arr[i-temp]=i;// acts as searching
                    sent++;
                    rec++;
                }                
            }
            for (i = 0; i <framectr; i++)
            {
                if (arr[i]==-1)//if frame is not received
                {
                    not_done_ctr++;
                }
            }
            if (not_done_ctr==0)//if all received move forward
            {
                all_done=1;
                printf("Moving window forward.");
            }
            printf("\n");
        }
    }
}
    
