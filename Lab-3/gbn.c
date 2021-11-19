//Go back N Protocol
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
    int sent=0,rec=0,temp;
    int propagation_delay=10,round_trip_time=2*propagation_delay,timeout_timer=2*round_trip_time;
    while (rec!=numpackets)
    {
    	int i;
        int framectr=0;
        printf("Sending frames:");
        for ( i = sent; i < sent+windowsize; i++)
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
        int ctr=0;
        for (i = temp; i < temp+framectr; i++)
        {
            int time_taken_for_ack=0;
            while (time_taken_for_ack<=round_trip_time)
            {
                time_taken_for_ack=rand()%((9*timeout_timer)/8);
            }
            if (time_taken_for_ack>timeout_timer)
            {
                printf("Ack received until frame %d...Moving start of window to frame %d and sending again. \n",i-1,i);
                break;
            }
            else
            {
                ctr++;//checks if entire window is rcvd
                sent++;
                rec++;

                if(ctr==framectr){
                    printf("Acknowledgement received for entire window.Moving it forward.\n");
                }
            }
        }
        printf("\n");
    }
    return 0;
}
