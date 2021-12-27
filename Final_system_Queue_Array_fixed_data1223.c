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

QType * newQueue_large(void);
QType * newQueue(void);
void enQ(QType *,int ,int ,int );
void deQ(QType *);
//void delQueue(QType**);
void RoundRobin(QType *,QType *,int );
void SJF_non(QType *,QType *,int );
void sort(QType*);
void first_come_first_serve(QType *,int);
void Shortest_job_first_preemptive(QType *,int);

int main()
{
    int i,total_burst = 0,total_bt = 0;
    QType *Q = newQueue();
    QType *Q1 = newQueue();
    QType *Q2 = newQueue();
    QType *Q3 = newQueue();
    QType *Q4 = newQueue_large();
    int burst[SIZE]={7,8,2,13,4,9,1,14,5,3};
    int arrival[SIZE]={0,2,4,5,7,9,10,13,18,20};
    int ID[SIZE] = {1,2,3,4,5,6,7,8,9,10};
    printf("Process\t\tBurst time\tArrival time\n");
    for(i=0;i<SIZE;i++)
    {
        printf("P%2d\t\t%d\t\t%d\n",1+i,burst[i],arrival[i]);
    }
    for(i=0;i<SIZE;i++){
      enQ(Q,arrival[i],burst[i],ID[i]);
      enQ(Q1,arrival[i],burst[i],ID[i]);
      enQ(Q2,arrival[i],burst[i],ID[i]); //enQ to Job Queue
      enQ(Q3,arrival[i],burst[i],ID[i]); //enQ to Job Queue
      total_burst=total_burst+burst[i];
    }
    for(i=0;i<SIZE1;i++){
      enQ(Q4,arrival[i],burst[i],ID[i]);
      total_bt=total_bt+burst[i];
    }
    first_come_first_serve(Q2,total_burst);
    RoundRobin(Q4,Q,total_bt);
    SJF_non(Q1,Q,total_burst);
    Shortest_job_first_preemptive(Q3,total_burst);
    return 0;
}

QType * newQueue_large(void)
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
    Q->rear = -1;
    Q->count = 0;
    Q->limit = SIZE1;
    return Q;
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

void RoundRobin(QType *Q,QType *R,int total_burst)
{
    int i;
    QType *job = Q;
    QType *original = R;
    QType *ready = newQueue_large();
    int temp_at,temp_bt,temp_id;
    int complete[10]={0},ct = 0,process[10]={0},p=0,turnaround_time[10];
    int burst,tq = 4,count = 0,time = 4;
    float average_wait_time = 0;

    for (i = 0;i <= total_burst; i++)
    {
        if (job->queue->q[job->front].arrivaltime == i) // Priority : Arrival's P must enQ earlier than operated P
        {
            enQ(ready,job->queue->q[job->front].arrivaltime,job->queue->q[job->front].bursttime,job->queue->q[job->front].ID);
            deQ(job); // get data & delete
        }
        if (i == 0) // operate at 0's
        {
                ready->queue->q[ready->front].bursttime = ready->queue->q[ready->front].bursttime - tq;
                temp_at = ready->queue->q[ready->front].arrivaltime;
                temp_bt = ready->queue->q[ready->front].bursttime;
                temp_id = ready->queue->q[ready->front].ID;
                deQ(ready);
        }
       if (time == i) // when a process has been done or reach time quantum's limit at this time
        {
            burst = ready->queue->q[ready->front].bursttime; //get the next P BT
            if (burst > tq) // determine to add tq or BT
            {
                time = time + tq;
            }
            else
            {
                time = time + burst;
            }

            if (temp_bt != 0) // put the Prcoess in ready Queue (if it has been operated)
                enQ(ready,temp_at,temp_bt,temp_id);
            if (ready->queue->q[ready->front].bursttime > tq) // First BT > tq = 4
            {
                ready->queue->q[ready->front].bursttime = ready->queue->q[ready->front].bursttime - tq;
                temp_at = ready->queue->q[ready->front].arrivaltime;
                temp_bt = ready->queue->q[ready->front].bursttime; // record the remain's BT
                temp_id = ready->queue->q[ready->front].ID;
                deQ(ready);
            }
            else if (ready->queue->q[ready->front].bursttime <= tq) // First BT <= tq = 4 ,delete process
            {
                burst = ready->queue->q[ready->front].bursttime;
                complete[ct] = i + burst; // calculate CT
                process[p] = ready->queue->q[ready->front].ID;  // record Process's ID
                ct++;
                p++;
                temp_at = temp_bt = temp_id =  0; // clear temp value
                deQ(ready);
            }
        }
    }
    printf("No.2 Round Robin (tq = 4) \n\n");// Showing the result
    for (int i=0;i<SIZE;i++)
    {
        int temp = process[i];
        int tat = complete[i] - original->queue->q[temp-1].arrivaltime;
        int wt = tat - original->queue->q[temp-1].bursttime;
        average_wait_time = average_wait_time + wt;
        printf("P%2d waiting time : %2d \n",process[i],wt);
    }
    printf("\nAverage Waiting Time : \t%.2f\n", average_wait_time/SIZE);
}

void SJF_non(QType *Q,QType *R,int total_burst)
{
    QType *job = Q;
    QType *original = R;
    QType *ready = newQueue();
    int process[10]={0,2,4,6,1,9,8,5,3,7},p = 0,complete[10],turnaround_time[10],j = 0; // the process[10] is according to complete time's value to sort
    int burst,temp_time = 0;
    float average_wait_time = 0;

    for (int i = 0;i <= total_burst ; i++)
    {
        if (job->queue->q[job->front].arrivaltime == i) // Priority : Arrival's P must enQ earlier than operated P
        {
            enQ(ready,job->queue->q[job->front].arrivaltime,job->queue->q[job->front].bursttime,job->queue->q[job->front].ID);
            deQ(job); // get data & delete
        }
        if (i == 0) // operate at 0's
        {
            burst = ready->queue->q[ready->front].bursttime;
            deQ(ready);
        }
        if (temp_time + burst == i) // when a process has been done at this time
        {
            temp_time = i;
            complete[j] = i;
            j++;
            int min = ready->queue->q[ready->front].bursttime;
            int temp = 0,min_index = 0;
            for (int i = ready->front ;i <= ready->rear ; i++) // looking for the smallest Process of Ready Queue
            {
                if (ready->queue->q[i].bursttime < min) // find the smallest ,replace it
                {
                    min = ready->queue->q[i].bursttime;
                    min_index = i;
                }
            }
            // record the next Process's BT to trigger next operation
            temp = ready->queue->q[ready->front].bursttime;
            ready->queue->q[ready->front].bursttime = min;
            ready->queue->q[min_index].bursttime = temp;
            burst = ready->queue->q[ready->front].bursttime;
            deQ(ready);
        }
    }
    printf("\nNo.3  Shortest Job First(Non-Preemptive) \n\n");// Showing the result
    for (int i=0;i<SIZE;i++)
    {
        int temp = process[i];
        int tat = complete[i]-original->queue->q[temp].arrivaltime;
        int wt = tat - original->queue->q[temp].bursttime;
        average_wait_time = average_wait_time + wt;
        printf("P%2d waiting time : %2d\n",temp+1,wt);
    }
    printf("\nAverage Waiting Time:\t%.2f\n", average_wait_time/SIZE);
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
