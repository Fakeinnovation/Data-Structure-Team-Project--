#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SIZE 10  //the size of data

typedef struct node{
    int arrivaltime;
    int bursttime;
    int ID;
}storage;

typedef struct array{
   storage *q;
}array;

typedef struct QType{
    int count;
    int front;
    int rear;
    int limit;
    struct array*queue;
}QType;

QType * newQueue(void);
void enQ(QType *,int ,int ,int );
void deQ(QType *);
//void delQueue(QType**);
void RoundRobin(QType *,int );
void SJF_non(QType *,int );
void first_come_first_serve(QType *,int);
void Shortest_job_first_preemptive(QType *,int);
void sort(QType*);
void shift(QType*);

int main()
{
    srand(time(NULL));
    int i,total_burst = 0,total_bt = 0;
    QType *Q = newQueue();
    QType *Q1 = newQueue();
    QType *Q2 = newQueue();
    QType *Q3 = newQueue();
    int burst[SIZE]={0};
    int arrival[SIZE]={0};
    int ID[SIZE] = {0};
    for(i=0;i<SIZE;i++)
    {
        burst[i]=rand()%20+1;
    }
    for(i=1;i<SIZE;i++)
    {
        arrival[i]=arrival[i-1]+rand()%5+1;
    }
    for(i=0;i<SIZE;i++)
    {
        ID[i]=i+1;
    }
    printf("Process\t\tBurst time\tArrival time\n");
    for(i=0;i<SIZE;i++)
    {
        printf("P%2d\t\t%d\t\t%d\n",1+i,burst[i],arrival[i]);
    }
    for(i=0;i<SIZE;i++){ //fcfs1.1&1.2,sjf_non,sjf_p scheduling
        enQ(Q,arrival[i],burst[i],ID[i]); //enQ to Job Queue
        enQ(Q1,arrival[i],burst[i],ID[i]); //enQ to Job Queue
        enQ(Q2,arrival[i],burst[i],ID[i]); //enQ to Job Queue
        enQ(Q3,arrival[i],burst[i],ID[i]); //enQ to Job Queue
        total_burst=total_burst+burst[i];
    }
    first_come_first_serve(Q2,total_burst);
    RoundRobin(Q,total_burst);
    SJF_non(Q1,total_burst);
    Shortest_job_first_preemptive(Q3,total_burst);
    return 0;
}

QType * newQueue(void)
{
    int i;
    QType * Q;
    Q = malloc (sizeof(QType));
    Q->queue =malloc(sizeof(struct array));
    Q->queue->q = malloc(sizeof(struct node)*SIZE);
    for (i=0; i<SIZE; i++){
    Q->queue->q[i].arrivaltime=0; // initialize
    Q->queue->q[i].bursttime=0; // initialize
    Q->queue->q[i].ID=0; // initialize
    }
    Q->front = 0; // initialize
    Q->rear = -1; // initialize
    Q->count = 0; // initialize
    Q->limit = SIZE; // initialize
    return Q;
}

void  enQ(QType *Q,int arrival,int burst,int id)
{
    Q->rear++; //queue+1 at rear
    Q->queue->q[Q->rear].arrivaltime = arrival;
    Q->queue->q[Q->rear].bursttime = burst;
    Q->queue->q[Q->rear].ID = id;
    Q->count++; //queue+1
}

void  deQ(QType *Q)
{
    Q->queue->q[Q->front].arrivaltime = 0;
    Q->queue->q[Q->front].bursttime = 0;
    Q->queue->q[Q->front].ID = 0;
    Q->count--; //queue-1
    Q->front++; //queue-1 at front
}
void first_come_first_serve(QType * Q1,int total_time) //fcfs sort by P1~P10
{
    QType*Q2=newQueue();
    int i=0,j=0;
    int time=0,A=0,wait=0;
    double avg;
    printf("\nNo.1 first_come_first_serve\n\n");
    for(time=0;time<total_time;)
    {
        if(Q1->queue->q[i].arrivaltime<=time&&i<SIZE)
        {
            enQ(Q2,Q1->queue->q[i].arrivaltime,Q1->queue->q[i].bursttime,Q1->queue->q[i].ID); //enQ to Ready Queue
            wait=time-Q2->queue->q[i].arrivaltime;
            printf("P%2d waiting time : %2d\n",Q2->queue->q[i].ID,wait);
            A=wait+A; //A is total waiting time
            time=time+Q2->queue->q[i].bursttime; //time is each process's waiting time
            deQ(Q2);
            i++;
        }
        else time++;
    }
    avg=(double)A/SIZE; //avg is average waiting time
    printf("\nAverage Waiting Time : %.2f\n\n",avg);
}

void RoundRobin(QType *Q1,int total_burst)
{
    printf("\nNO.2 Round Robin \n\n");
    QType*Q2=newQueue();
    int time,tq=4,tw=0;
    int wait;
    int B[SIZE+1]={0};
    int i=0,j=0,k=0;
    int A=0;
    int flag=0;
    double avg;
    for(time=0;time<total_burst;)
    {
        if(Q1->queue->q[i].arrivaltime<=time&&i<SIZE) //judge whether process come in or not
        {
            k=0;
            for(j=i;j<SIZE;j++)
            {
                if(Q1->queue->q[j].arrivaltime<=time)
                {
                    enQ(Q2,Q1->queue->q[j].arrivaltime,Q1->queue->q[j].bursttime,Q1->queue->q[j].ID); //enQ to Ready Queue
                    k++;
                }
            }
            if(flag==0)
            {
                shift(Q2);
            }
            flag=0;
            for(tw=0;tw<tq;tw++)
            {
                time++;
                Q2->queue->q[Q2->front].bursttime--;
                B[Q2->queue->q[Q2->front].ID]++;
                if(Q2->queue->q[Q2->front].bursttime==0)
                {
                    wait=time-Q2->queue->q[Q2->front].arrivaltime-B[Q2->queue->q[Q2->front].ID];
                    printf("P%2d waiting time : %2d\n",Q2->queue->q[Q2->front].ID,wait);
                    A=A+wait;
                    deQ(Q2);
                    flag=1;
                    break;
                }
            }
            i=i+k;
        }
        else if(Q2->count!=0) //judge whether process come in or not
        {
            if(flag==0)
            {
                shift(Q2);
            }
            flag=0;
            for(tw=0;tw<tq;tw++)
            {
                time++;
                Q2->queue->q[Q2->front].bursttime--;
                B[Q2->queue->q[Q2->front].ID]++;
                if(Q2->queue->q[Q2->front].bursttime==0)
                {
                    wait=time-Q2->queue->q[Q2->front].arrivaltime-B[Q2->queue->q[Q2->front].ID];
                    printf("P%2d waiting time : %2d\n",Q2->queue->q[Q2->front].ID,wait);
                    A=A+wait;
                    deQ(Q2);
                    flag=1;
                    break;
                }
            }
        }
        else time++;
    }
    avg=(double)A/SIZE;
    printf("\nAverage Waiting Time : %.2f\n\n",avg);
}

void shift(QType*Q2)
{
    int temp,i;
    temp=Q2->queue->q[Q2->front].bursttime;
    for(i=Q2->front;i<Q2->rear;i++)
    {
        Q2->queue->q[i].bursttime=Q2->queue->q[i+1].bursttime;
    }
    Q2->queue->q[Q2->rear].bursttime=temp;
    temp=Q2->queue->q[Q2->front].arrivaltime;
    for(i=Q2->front;i<Q2->rear;i++)
    {
        Q2->queue->q[i].arrivaltime=Q2->queue->q[i+1].arrivaltime;
    }
    Q2->queue->q[Q2->rear].arrivaltime=temp;
    temp=Q2->queue->q[Q2->front].ID;
    for(i=Q2->front;i<Q2->rear;i++)
    {
        Q2->queue->q[i].ID=Q2->queue->q[i+1].ID;
    }
    Q2->queue->q[Q2->rear].ID=temp;
}

void SJF_non(QType *Q1,int total_time)
{
    QType*Q9 = newQueue();
    int time=0,wait=0;
    int A=0;
    int B[SIZE+1]={0};
    double avg;
    int i=0,flag=1;
    printf("\nNo.3 Shortest_job_first_non_preemptive\n\n");
    for(time=0;time<total_time;) //calculate time = 0 to total time
    {
        if(Q1->queue->q[i].arrivaltime<=time&&i<SIZE) //judge whether process come in or not
        {
            enQ(Q9,Q1->queue->q[i].arrivaltime,Q1->queue->q[i].bursttime,Q1->queue->q[i].ID); //enQ to Ready Queue
            if(flag==1)
            {
                sort(Q9); //sort by BT (the smallest BT do this scheduling first)
                flag=0;
            }
            time++;
            B[Q9->queue->q[Q9->front].ID]++; //calculate each process do for a few seconds
            Q9->queue->q[Q9->front].bursttime--; //go to do process so the process's BT-1
            if(Q9->queue->q[Q9->front].bursttime==0) //if the process have done,then go to print
            {
                wait=time-Q9->queue->q[Q9->front].arrivaltime-B[Q9->queue->q[Q9->front].ID]+1; //waiting time=the process's AT-the process's BT
                A=A+wait;  //A is total waiting time
                printf("P%2d waiting time : %2d\n",Q9->queue->q[Q9->front].ID,wait);
                deQ(Q9); //have done ,quit from Ready Queue
                flag=1;
            }
            i++;
        }
        else if(Q9->count!=0) //if the process not come in,but there are process in ready Queue
        {
            if(flag==1)
            {
                sort(Q9); //sort by BT (the smallest BT do this scheduling first)
                flag=0;
            }
            time++;
            B[Q9->queue->q[Q9->front].ID]++; //calculate each process do for a few seconds
            Q9->queue->q[Q9->front].bursttime--; //go to do process so the process's BT-1
            if(Q9->queue->q[Q9->front].bursttime==0) //if the process have done,then go to print
            {
                wait=time-Q9->queue->q[Q9->front].arrivaltime-B[Q9->queue->q[Q9->front].ID]+1; //waiting time=the process's AT-the process's BT
                A=A+wait;  //A is total waiting time
                printf("P%2d waiting time : %2d\n",Q9->queue->q[Q9->front].ID,wait);
                deQ(Q9); //have done ,quit from Ready Queue
                flag=1;
            }
        }
        else time++;
    }
    avg=(double)A/SIZE; //avg is average waiting time
    printf("\nAverage Waiting Time : %.2f\n\n",avg);
}
void Shortest_job_first_preemptive(QType *Q1,int total_time)
{
    int time=0,wait=0;
    int A=0;
    int B[SIZE+1]={0};
    int j;
    double avg;
    QType *Q2=newQueue();
    int i=0;
    printf("\nNo.4 Shortest_job_first_preemptive\n\n");
    for(time=0;time<total_time;time++) //calculate time = 0 to total time
    {
        if(Q1->queue->q[i].arrivaltime<=time&&i<SIZE) //judge whether process come in or not
        {
            enQ(Q2,Q1->queue->q[i].arrivaltime,Q1->queue->q[i].bursttime,Q1->queue->q[i].ID); //enQ to Ready Queue
            sort(Q2); //sort by BT (the smallest BT do this scheduling first)
            B[Q2->queue->q[Q2->front].ID]++; //calculate each process do for a few seconds
            Q2->queue->q[Q2->front].bursttime--; //go to do process so the process's BT-1
            if(Q2->queue->q[Q2->front].bursttime==0) //if the process have done,then go to print
            {
                wait=time-Q2->queue->q[Q2->front].arrivaltime-B[Q2->queue->q[Q2->front].ID]+1; //waiting time=the process's AT-the process's BT
                A=A+wait;  //A is total waiting time
                printf("P%2d waiting time : %2d\n",Q2->queue->q[Q2->front].ID,wait);
                deQ(Q2); //have done ,quit from Ready Queue
            }
            i++;
        }
        else if(Q2->count!=0) //if the process not come in,but there are process in ready Queue
        {
            sort(Q2); //sort by BT (the smallest BT do this scheduling first)
            B[Q2->queue->q[Q2->front].ID]++; //calculate each process do for a few seconds
            Q2->queue->q[Q2->front].bursttime--; //go to do process so the process's BT-1
            if(Q2->queue->q[Q2->front].bursttime==0) //if the process have done,then go to print
            {
                wait=time-Q2->queue->q[Q2->front].arrivaltime-B[Q2->queue->q[Q2->front].ID]+1; //waiting time=the process's AT-the process's BT
                A=A+wait;  //A is total waiting time
                printf("P%2d waiting time : %2d\n",Q2->queue->q[Q2->front].ID,wait);
                deQ(Q2); //have done ,quit from Ready Queue
            }
        }
    }
    avg=(double)A/SIZE; //avg is average waiting time
    printf("\nAverage Waiting Time : %.2f\n\n",avg);
}
void sort (QType*Q) //sort by BT from small to big
{
    int i=Q->front,j=0;
    int temp;
    if(Q->count!=0)
    {
        for(i=Q->front;i<(Q->count+Q->front)-1;i++)
        {
        for(j=i+1;j<(Q->count+Q->front);j++)
        {
            if((Q->queue->q[i].bursttime)>(Q->queue->q[j].bursttime)) //sort by BT from small to big
            {
                temp=Q->queue->q[i].bursttime;
                Q->queue->q[i].bursttime=Q->queue->q[j].bursttime;
                Q->queue->q[j].bursttime=temp;
                temp=Q->queue->q[i].ID;
                Q->queue->q[i].ID=Q->queue->q[j].ID;
                Q->queue->q[j].ID=temp;
                temp=Q->queue->q[i].arrivaltime;
                Q->queue->q[i].arrivaltime=Q->queue->q[j].arrivaltime;
                Q->queue->q[j].arrivaltime=temp;
            }
        }
        }
    }
}
