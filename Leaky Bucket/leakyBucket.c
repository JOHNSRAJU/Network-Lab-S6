#include<stdio.h>
#include <unistd.h>
int main(){
    int buffS,buffSize,noPackets,i,bucket[50],temp,count=0,packetS[50],rateF,time,dataSent=0;
    printf("Enter the buffer size :- ");
    scanf("%d",&buffSize);
    buffS=buffSize;
    printf("Enter the no. of packets :-");
    scanf("%d",&noPackets);
    for(i=0;i<noPackets;i++){
        printf("Size of Packet [%d] :- ",i);
        scanf("%d",&temp);
        if(temp>buffS){
            printf("Packet size is grater then buffer space\n");
        }
        else{
            bucket[count]=i;
            buffS-=temp;
            packetS[count]=temp;
            count++;
        }
    }
    printf("\nEnter the rate of data flow :- ");
    scanf("%d",&rateF);
    printf("Time interval of data flow :- ");
    scanf("%d",&time);
    for(i=0;i<count;i++){
        while(packetS[i]>0){
            sleep(time);
            packetS[i]-=rateF;
            dataSent++;
        }
        printf("Packet[%d] completed in %d send\n",bucket[i],dataSent);
    }
}