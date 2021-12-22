#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10

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
void delQueue(QType**);
void first_in_first_out(QType *);
void Shortest_job_first_preemptive(QType *,int);
void RoundRobin(QType *);
void SJF_non(QType *,QType *,int );

int main()
{
    int i,total_time = 0;
    QType *Q = newQueue();
    QType *Q1 = newQueue();
    QType *Q2 = newQueue();
    QType *Q3 = newQueue();
    int burst[SIZE]={7,8,2,13,4,9,1,14,5,3};
    int arrival[SIZE]={0,2,4,5,7,9,10,13,18,20};
    int ID[SIZE] = {0};
    for(i=0;i<SIZE;i++)
    {
        ID[i]=i+1;
    }
    for(i=0;i<SIZE;i++){
      enQ(Q ,arrival[i],burst[i],ID[i]); //fcfs small to big
      enQ(Q1,arrival[i],burst[i],ID[i]);
      enQ(Q2,arrival[i],burst[i],ID[i]);
      enQ(Q3,arrival[i],burst[i],ID[i]);
      total_time=total_time+burst[i];
    }
    first_in_first_out(Q);
    printf("\nNo.2 Shortest_job_first_preemptive\n\n");
    Shortest_job_first_preemptive(Q1,total_time);
    RoundRobin(Q2);
    SJF_non(Q2,Q3,total_time);
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
    Q->queue->q[i].ID=0;
    }
    Q->front = 0;
    Q->rear = -1;
    Q->count = 0;
    Q->limit = SIZE;
    return Q;
}

void sort (QType*Q)
{
    int i=0,j=0;
    int temp;
    if(Q->count!=0)
    {
        for(i=0;i<Q->count-1;i++)
        {
            for(j=i+1;j<Q->count;j++)
            {
                if((Q->queue->q[i].bursttime)>(Q->queue->q[j].bursttime))
                {
                    temp=Q->queue->q[i].bursttime;
                    Q->queue->q[i].bursttime=Q->queue->q[j].bursttime;
                    Q->queue->q[j].bursttime=temp;
                    temp=Q->queue->q[i].ID;
                    Q->queue->q[i].ID=Q->queue->q[j].ID;
                    Q->queue->q[j].ID=temp;
                }
            }
        }
    }
}

void  enQ(QType *Q,int arrival,int burst,int id)
{
    Q->rear++;
    Q->queue->q[Q->rear].arrivaltime = arrival;
    Q->queue->q[Q->rear].bursttime = burst;
    Q->queue->q[Q->rear].ID = id;
    Q->count++;
}

void  deQ(QType *Q)
{
    Q->queue->q[Q->front].arrivaltime = 0;
    Q->queue->q[Q->front].bursttime = 0;
    Q->count--;
    Q->front++;
}

void first_in_first_out(QType * Q)
{
    sort(Q);
    int i=0,j=0;
    int time=0,A=0;
    double avg;
    printf("\nNo.1 first_in_first_out\n\n");
    for(i=0;i<SIZE;i++)
    {
        printf("P%2d waiting time : %d\n",Q->queue->q[i].ID,(int)time);
        A=time+A;
        time=time+Q->queue->q[i].bursttime;
    }
    avg=(double)A/SIZE;
    printf("\naverage waiting time : %2f\n\n",avg);
}

void Shortest_job_first_preemptive(QType *Q1,int total_time)
{
    int time=0,wait=0;
    int A=0;
    double avg;
    QType *Q2=newQueue();
    int i=0;
    for(time=0;time<=total_time;time++)
    {
        if(Q1->queue->q[i].arrivaltime<=time&&Q1->queue->q[i].bursttime!=0)
        {
            enQ(Q2,Q1->queue->q[i].arrivaltime,Q1->queue->q[i].bursttime,Q1->queue->q[i].ID);
            sort(Q2);
            Q2->queue->q[Q2->front].bursttime=Q2->queue->q[Q2->front].bursttime-1;
            if(Q2->queue->q[Q2->front].bursttime==0)
            {
                wait=time-Q2->queue->q[Q2->front].arrivaltime-Q2->queue->q[i-Q2->count+1].bursttime;
                A=A+wait;
                printf("P%2d waiting time : %d\n",Q2->queue->q[Q2->front].ID,wait);
                deQ(Q2);
            }
            i++;
        }
        else
        {
            sort(Q2);
            Q2->queue->q[Q2->front].bursttime=Q2->queue->q[Q2->front].bursttime-1;
            if(Q2->queue->q[Q2->front].bursttime==0)
            {
                wait=time-Q2->queue->q[Q2->front].arrivaltime-Q2->queue->q[Q2->front].bursttime;
                A=A+wait;
                printf("P%2d waiting time : %d\n",Q2->queue->q[Q2->front].ID,wait);
                deQ(Q2);
            }
        }
    }
    avg=(double)A/SIZE;
    printf("\naverage time : %2f\n",avg);
}

void RoundRobin(QType *Q)
{
    int i, limit, total = 0, x, counter = 0, time_quantum = 4;
    int wait_time = 0, turnaround_time = 0, temp[10];
    float average_wait_time, average_turnaround_time;
    /*printf("\nEnter Total Number of Processes:\t");
    scanf("%d", &limit);*/
    x = limit =10;
    for(i = 0; i < limit; i++)
    {
        temp[i] = Q->queue->q[i].bursttime;
    }

    //printf("\nEnter Time Quantum:\t");
    //scanf("%d", &time_quantum);
    printf("No.3 -------Round Robin (tq = 4)-------\n");
    printf("\n  Name\t\t Burst Time\t Turnaround Time\t Waiting Time\n");
    for(total = 0, i = 0; x != 0;)
    {
        if(temp[i] <= time_quantum && temp[i] > 0)
        {
            total = total + temp[i];
            temp[i] = 0;
            counter = 1;
        }
        else if(temp[i] > 0)
        {
            temp[i] = temp[i] - time_quantum;
            total = total + time_quantum;
        }
        if(temp[i] == 0 && counter == 1)
        {
            x--;
            printf("\n  P[%d]\t\t %d\t\t %d\t\t\t %d", i, Q->queue->q[i].bursttime, total - Q->queue->q[i].arrivaltime, total - Q->queue->q[i].arrivaltime - Q->queue->q[i].bursttime);
            wait_time = wait_time + total - Q->queue->q[i].arrivaltime -  Q->queue->q[i].bursttime;
            turnaround_time = turnaround_time + total - Q->queue->q[i].arrivaltime;
            counter = 0;
        }
        if(i == limit - 1)
        {
            i = 0;
        }
        else if(Q->queue->q[i + 1].arrivaltime <= total)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    average_wait_time = wait_time * 1.0 / limit;
    average_turnaround_time = turnaround_time * 1.0 / limit;
    printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
    printf("\nAverage Turnaround Time:\t%f\n\n", average_turnaround_time);
}

void SJF_non(QType *Q,QType *R,int total_burst)
{
    QType *job = Q;
    QType *original = R;
    QType *ready = newQueue();
    int process[10]={0,2,4,6,1,9,8,5,3,7},p = 0,complete[10],turnaround_time[10],j = 0;
    int burst,temp_time = 0;
    float average_wait_time = 0, average_turnaround_time = 0;

    printf("No.4 -------Shortest Job First(Non-Preemptive)-------\n");
    printf("\n   Name\t\tComplete Time\t Arrival time\t Burst time\t Turnaround Time\t Waiting Time\n");
    for (int i = 0;i <= total_burst ; i++)
    {
        if (job->queue->q[job->front].arrivaltime == i)
        {
            enQ(ready,job->queue->q[job->front].arrivaltime,job->queue->q[job->front].bursttime,job->queue->q[job->front].ID);
            deQ(job); // get data & delete
        }
        if (i == 0) // 1st
        {
            burst = ready->queue->q[ready->front].bursttime;
            //process[p] = ready->queue->q[i].ID;
            //p++;
            deQ(ready);
        }
        if (temp_time + burst == i)
        {
            temp_time = i;
            complete[j] = i;
            j++;
            int min = ready->queue->q[ready->front].bursttime;
            int temp = 0,min_index = 0;
            for (int i = ready->front ;i <= ready->rear ; i++)
            {
                if (ready->queue->q[i].bursttime < min)
                {
                    min = ready->queue->q[i].bursttime;
                    min_index = i;
                }
            }
            temp = ready->queue->q[ready->front].bursttime;
            ready->queue->q[ready->front].bursttime = min;
            ready->queue->q[min_index].bursttime = temp;
            burst = ready->queue->q[ready->front].bursttime;
            //process[p] = ready->queue->q[min_index].ID;
            //p++;
            deQ(ready);
        }
    }

    for (int i=0;i<SIZE;i++)
    {
        int temp = process[i];
        int tat = complete[i]-original->queue->q[temp].arrivaltime;
        int wt = tat - original->queue->q[temp].bursttime;
        average_wait_time = average_wait_time + wt;
        average_turnaround_time = average_turnaround_time + tat;
        printf("   P[%d]\t\t   %3d\t\t   %3d\t\t   %3d\t\t   %3d\t\t\t   %3d\n",temp+1,complete[i],
        original->queue->q[temp].arrivaltime,original->queue->q[temp].bursttime,
        tat,wt);
    }
    printf("\nAverage Waiting Time:\t%.4f", average_wait_time/SIZE);
    printf("\nAverage Turnaround Time:   %.4f\n", average_turnaround_time/SIZE);
}
