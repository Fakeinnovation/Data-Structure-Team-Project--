#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10
#define SIZE1 22

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


QType * newQueue_circular(void);
void enQ_c(QType *,int ,int ,int );
void deQ_c(QType *);
QType * newQueue(void);
void enQ(QType *,int ,int ,int );
void deQ(QType *);
void delQueue(QType**);
void RoundRobin(QType *);
void RoundRobin_new(QType *,int );
void SJF_non(QType *,QType *,int );
//void  first_in_first_out(int []);
//void  Shortest_job_first_preemptive(int [],int []);
int main()
{
    int i,total_burst = 0,total_bt = 0;
    QType *Q = newQueue();
    QType *Q1 = newQueue();
    QType *Q5 = newQueue_circular();
    int burst[SIZE]={7,8,2,13,4,9,1,14,5,3};
    int arrival[SIZE]={0,2,4,5,7,9,10,13,18,20};
    int ID[SIZE] = {1,2,3,4,5,6,7,8,9,10};
    for(i=0;i<SIZE;i++){
      enQ(Q,arrival[i],burst[i],ID[i]);
      enQ(Q1,arrival[i],burst[i],ID[i]);
      total_burst=total_burst+burst[i];
    }
    for(i=0;i<SIZE;i++){ // Circular Queue,one space to ensure it work
      enQ_c(Q5,arrival[i],burst[i],ID[i]);
      total_bt=total_bt+burst[i];
    }
    //RoundRobin(Q);
    RoundRobin_new(Q5,total_bt);
    SJF_non(Q1,Q,total_burst);
    //first_in_first_out(burst);
    //Shortest_job_first_preemptive(burst,arrival);
    return 0;
}

QType * newQueue_circular(void)
{
    int i;
    QType * Q;
    Q = malloc (sizeof(QType));
    Q->queue =malloc(sizeof(struct array));
    Q->queue->q = malloc(sizeof(struct node)*SIZE1);
    for (i=0; i<SIZE1; i++){
    Q->queue->q[i].arrivaltime=0; // initialize
    Q->queue->q[i].bursttime=0; // initialize
    Q->queue->q[i].ID=0;
    }
    Q->front = 0;
    Q->rear = 0;
    Q->count = 0;
    Q->limit = SIZE1;
    return Q;
}

void  enQ_c(QType *Q,int arrival,int burst,int id)
{
    Q->rear = (Q->rear + 1) % SIZE1;
    Q->queue->q[Q->rear].arrivaltime = arrival;
    Q->queue->q[Q->rear].bursttime = burst;
    Q->queue->q[Q->rear].ID = id;
    Q->count++;
}

void  deQ_c(QType *Q)
{
    Q->front = (Q->front + 1) % SIZE1;
    Q->queue->q[Q->front].arrivaltime = 0;
    Q->queue->q[Q->front].bursttime = 0;
    Q->queue->q[Q->front].ID = 0;
    Q->count--;
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
    Q->queue->q[Q->front].ID = 0;
    Q->count--;
    Q->front++;
}

void RoundRobin_new(QType *Q,int total_burst)
{
    QType *job = Q;
    QType *ready = newQueue_circular();
    int temp_at,temp_bt,temp_id;
    int complete[10]={0},ct = 0,proccess[10]={0},p=0,turnaround_time[10];
    int burst,tq = 4,count = 0,time = 4;

    for (int i = 0;i <= total_burst; i++)
    {
        if (job->queue->q[job->front+1].arrivaltime == i) // 比處理後的還要早
        {
            enQ_c(ready,job->queue->q[job->front+1].arrivaltime,job->queue->q[job->front+1].bursttime,job->queue->q[job->front+1].ID);
            deQ_c(job); // get data & delete
        }
        if (i == 0)
        { //if (ready->queue->q[ready->front+1].bursttime > tq)
                ready->queue->q[ready->front+1].bursttime = ready->queue->q[ready->front+1].bursttime - tq;
                temp_at = ready->queue->q[ready->front+1].arrivaltime;
                temp_bt = ready->queue->q[ready->front+1].bursttime;
                temp_id = ready->queue->q[ready->front+1].ID;
                deQ_c(ready);
        }
        /*i == 4 || i == 8 || i==10 || i == 13 || i== 17 || i == 21 ||i ==25 ||i==29||i==30||i==34||i==38||i==42||i==45
           ||i==49||i==53||i==57||i==58||i==59||i==63||i==64||i==66*/
       if (time == i)
        {
            burst = ready->queue->q[ready->front+1].bursttime;
            //printf("%d\n",burst);
            if (burst > tq)
            {
                time = time + tq;
            }
            else
            {
                time = time + burst;
            }
            if (temp_bt != 0)
                enQ_c(ready,temp_at,temp_bt,temp_id);
            if (ready->queue->q[ready->front+1].bursttime > tq) // First BT > tq = 4
            {
                ready->queue->q[ready->front+1].bursttime = ready->queue->q[ready->front+1].bursttime - tq;
                temp_at = ready->queue->q[ready->front+1].arrivaltime;
                temp_bt = ready->queue->q[ready->front+1].bursttime;
                temp_id = ready->queue->q[ready->front+1].ID;
                deQ_c(ready);
            }
            else if (ready->queue->q[ready->front+1].bursttime <= tq) // First BT <= tq = 4 ,delete process
            {
                burst = ready->queue->q[ready->front+1].bursttime;
                complete[ct] = i + burst;
                proccess[p] = ready->queue->q[ready->front+1].ID;
                ct++;
                p++;
                temp_at = temp_bt = temp_id =  0;
                deQ_c(ready);
            }
        }
    }
    for (int i=0;i<SIZE1;i++)
    {
        printf("Process[%d]\t\%d\t  %d\t  %d\n", i ,ready->queue->q[i].arrivaltime,ready->queue->q[i].bursttime,ready->queue->q[i].ID);
    }
    printf("Front : %d,Rear : %d,Count : %d\n",ready->front,ready->rear,ready->count);
    printf("Process\tComplete time\n");
    for (int i=0;i<SIZE;i++)
    {
        printf("P%d\t %d\n",proccess[i],complete[i]);
    }
}

void SJF_non(QType *Q,QType *R,int total_burst)
{
    QType *job = Q;
    QType *original = R;
    QType *ready = newQueue();
    int process[10]={0,2,4,6,1,9,8,5,3,7},p = 0,complete[10],turnaround_time[10],j = 0;
    int burst,temp_time = 0;
    float average_wait_time = 0, average_turnaround_time = 0;
    printf(" -------Shortest Job First(Non-Preemptive)-------\n");
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
        printf("    P[%d]\t   %3d\t\t   %3d\t\t   %3d\t\t   %3d\t\t\t   %3d\n",temp+1,complete[i],
        original->queue->q[temp].arrivaltime,original->queue->q[temp].bursttime,
        tat,wt);
    }
    printf("\nAverage Waiting Time:\t%.4f", average_wait_time/SIZE);
    printf("\nAverage Turnaround Time:   %.4f\n", average_turnaround_time/SIZE);
}
