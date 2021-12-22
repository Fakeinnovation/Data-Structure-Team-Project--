#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

typedef struct node{
 int arrivaltime;
 int bursttime;
 struct node * next;
 int order;
}storage;
typedef struct QType{
 int count;
 storage * front;
 storage * rear;
}QType;

QType * newQueue(void);
void enQ(QType *,int,int);
void enQ2(QType*,int,int,int);
storage* deQ(QType *);
void delQueue(QType **);
int processnum(int);
void fcfs(QType*,int[]);
void psjf(QType*,int,int[]);
void rr(QType*,int);
void sjf(QType*,int);

int main()
{
 srand(time(NULL));
    int i=0;
    int total_burst=0;
    QType *Q,*q,*Q2,*Q3,*Q4;
    Q = newQueue();
    q = newQueue();
    Q2 = newQueue();
    Q3 = newQueue();
    Q4 = newQueue();
    int burst[SIZE]={7,8,2,13,4,9,1,14,5,3};            //generate data
    int arrival[SIZE]={0,2,4,5,7,9,10,13,18,20};
    printf("Process   arrival time    burst time\n");
    for(i=0;i<SIZE;i++){
      printf("P%2d:         %2d            %2d\n",i+1,arrival[i],burst[i]);
    }
    for(i=0;i<SIZE;i++){
    total_burst=total_burst+burst[i];                   //count up total burst time
    }
    for(i=0;i<SIZE;i++){                                //put data into job queue
        enQ(Q,arrival[i],burst[i]);
        enQ(q,arrival[i],burst[i]);
        enQ(Q2,arrival[i],burst[i]);
        enQ(Q3,arrival[i],burst[i]);
        enQ(Q4,arrival[i],burst[i]);
    }
    /*each scheduling algorithms*/
    fcfs(Q,arrival);
    rr(Q2,total_burst);
    sjf(Q3,total_burst);
    psjf(q,total_burst,arrival);

    delQueue(&Q);
    delQueue(&q);
    delQueue(&Q2);
    delQueue(&Q3);
    delQueue(&Q4);
    return 0;
}
void fcfs(QType*q,int*arrival)
{
    printf("\nNo.1 First come first serve:\n");
    printf("\nWaiting time for ...\n");
    int i,j;
    int waiting_time[SIZE]={0};
    storage* p;
    for(i=0;i<SIZE-1;i++){
        p=deQ(q);//dequeue the next process from job queue
        for(j=SIZE-1;j>i;j--){
         waiting_time[j]=waiting_time[j]+(p->bursttime);
         //add the burst time of Pi to the waiting time of all processes behind Pi
     }
    }
    for(i=0;i<SIZE;i++){
         waiting_time[i]=waiting_time[i]-arrival[i];
    }
    int total=0;
    double awt;
    for(i=0;i<SIZE;i++){//calculate average waiting time & print each waiting time
        printf("P%2d=%2d\n",i+1,waiting_time[i]);
        total=total+waiting_time[i];
    }
    awt=(double)total/SIZE;
    printf("\nAverage waiting time:%.1f\n",awt);
}

void psjf(QType*q,int tb,int*arrival)
{
    printf("\nNo.4 Preemptive SJF:\n");
    printf("\nWaiting time for ...\n");
    int w1[1000]={0};
    int w2[1000]={0};
    int waiting_time[1000]={0};
    int i=0,k1=0,ty=1;
    QType*t;
    t=q;
    QType*Q2;
    Q2= newQueue();//ready queue
    storage* p,*n;
    for(i=0;i<tb-1;i++){//make i time counter
     if(i==0){
         p=deQ(q);//when the time is 0s,dequeue the first process
         p->order=1;
     }
     if(q->front!=NULL&&q->front->arrivaltime==i){
            //check the arrival time of the next process in job queue is same as the time i
      n=deQ(q);//if true,dequeue the next process of job queue
      ty++;
      n->order=ty;
      if(p->bursttime>n->bursttime){//if the remainig burst time of processing process is bigger than the next process
       enQ2(Q2,p->arrivaltime,p->bursttime,p->order);//enqueue the processing process to ready queue
       w1[p->arrivaltime]=w1[p->arrivaltime]+i;
       p=n;//process the next P
      }
      else{
          enQ2(Q2,n->arrivaltime,n->bursttime,n->order);//enqueue the next P to ready queue
          w1[n->arrivaltime]=w1[n->arrivaltime]+i;
      }
     }
     (p->bursttime)--;//the burst time of the processing P subtract 1s
     k1++;
     if(p->bursttime==0){//if the remaining burst time of the processing P is 0s
        p=deQ(Q2);//dequeue the next P in ready queue, make it the processing P at the next second
        w2[p->arrivaltime]=w2[p->arrivaltime]+i+1;
     }

    }
    k1++;

    int j,k;
    int total=0;
    double awt;
    for(j=0;j<1000;j++){
        waiting_time[j]=w2[j]-w1[j];
        for(k=0;k<SIZE;k++){
         if(j==arrival[k]){
         printf("P%2d=%2d\n",k+1,waiting_time[j]);//print each waiting time
         }
  }
        total=total+waiting_time[j];
    }
    awt=(double)total/SIZE;
    printf("\nAverage wainting time:%.1f\n",awt);//calculate average waiting time
}
QType * newQueue(void)
{
 QType * Q;
  Q = malloc(sizeof(QType));
  Q->count = 0;
  Q->front = NULL;
  Q->rear = NULL;
  return Q;
}
void enQ(QType * Q,int arrivaltime,int bursttime)
{
  storage * New;
  New = malloc(sizeof(storage));
  New->arrivaltime = arrivaltime;
  New->bursttime = bursttime;
  New->next = NULL;
  if(Q->count!=0){
   Q->rear->next = New;
  }
  Q->rear = New;
  Q->count++;
  if(Q->count==1){
     Q->front=New;
  }
}
storage* deQ(QType * Q)
{
  storage * temp;
  Q->count--;
  temp = Q->front;
 if(Q->count!=0){
    Q->front = Q->front->next;
  }
  return temp;
}
void delQueue(QType ** Q)
{
  storage * temp;
  while((*Q)->count > 0){
    temp = deQ(*Q);
    free(temp);
  }
  free(*Q);
}
void enQ2(QType * Q,int arrivaltime,int bursttime,int order)
{
  storage * New,*T,*P;
  New = malloc(sizeof(storage));
  New->arrivaltime = arrivaltime;
  New->bursttime = bursttime;
  New->order = order;
  New->next = NULL;
  if(Q->count==0){
     Q->rear = New;
     Q->front=New;
     Q->count++;
  }
  else if((Q->front->bursttime)>(New->bursttime)){
     New->next=Q->front;
     Q->front=New;
     Q->count++;
  }
 else{
     T=Q->front;
     while((T->bursttime)<=(New->bursttime)){
         if(T->next==NULL){
             T->next=New;
             Q->rear = New;
             Q->count++;
             return;
         }
         P=T;
         T=T->next;
         if((T->bursttime)>(New->bursttime)){
             New->next=T;
             P->next=New;
             Q->count++;
             return;
         }
     }
 }
}
void rr(QType * Q,int tb)
{
	printf("\nNo.2 Round robbin:\n(Set time quantum 4)\n\nWaiting time for ...\n");
	int time=0,sum=0,runtime=0,busy=0;//busy 1 for running,0 for done
	int i=0,j=0;                      //loop operator
	int arrivaltime[SIZE],waitingtime[SIZE],state[SIZE]; //state 1 for waiting,2 for running,3 for done
	storage * temp,* run;
	QType * readyQ = newQueue();
	while(time < tb){
		if(time == Q->front->arrivaltime){  //Dequeue job queue to ready queue when arrive
			temp = deQ(Q);
			arrivaltime[i] = temp->arrivaltime;
			waitingtime[i] = 0;
			state[i] = 1;
			enQ(readyQ,temp->arrivaltime,temp->bursttime);
			i++;
		}
		if(runtime == 4){                   //if runtime == quantum, reline-up
			enQ(readyQ,run->arrivaltime,run->bursttime);
			busy = 0;
			runtime = 0;
			state[processnum(run->arrivaltime)] = 1;
		}
		if( !busy  &&  readyQ->count != 0){  //if the job is paused, run a new job
			busy = 1;
			run = deQ(readyQ);
			state[processnum(run->arrivaltime)] = 2;
		}
		run->bursttime--;
		runtime++;
		for(j=0;j<SIZE;j++){       //count up waiting time
			if(state[j] == 1)
				waitingtime[j]++;
		}
		if(run->bursttime == 0){  //if job is finished, reset related operator
			busy = 0;
			runtime = 0;
			state[processnum(run->arrivaltime)] = 3;
		}
		time++;
	}
	for(i=0;i<SIZE;i++){               //calculate average waiting time & print each waiting time
		printf("P%2d=%2d\n",i+1,waitingtime[i]);
		sum+=waitingtime[i];
	}
	printf("\nAverage wainting time:%.1f\n",sum/1.0/SIZE);
}
int processnum(int arr)//inorder to verify the process number
{
	switch(arr){
		case 0: return 0;
		case 2: return 1;
		case 4: return 2;
		case 5: return 3;
		case 7: return 4;
		case 9: return 5;
		case 10: return 6;
		case 13: return 7;
		case 18: return 8;
		case 20: return 9;
	}
}
void sjf(QType* Q,int tb)
{
 printf("\nNo.3 Shortest job first:\n\nWaiting time for ...\n");
 int time=0,min,running,sum=0,busy=0;         //busy 1 for running,0 for done
 int i=0;                                     //loop operator
 int waitingtime[SIZE]={0},bursttime[SIZE]={0},state[SIZE]={0};//state 1 for processing,2 for waiting,3 for done
 storage * temp;
 while(time < tb){
  if(Q->front->arrivaltime == time){ //if time = arrival time of the job, dequeue
   temp = deQ(Q);
   bursttime[SIZE-(Q->count)-1]=temp->bursttime;
   state[SIZE-(Q->count)-1]=2;

  }
  if(!busy){                              //condition of the CPU is not busy
   min=99;                             //find the job of the shortest burst time
   for(i=0;i<SIZE;i++){
    if(state[i] == 2  &&  bursttime[i] < min){
     min = bursttime[i];
     running = i;
    }
   }
   state[running] = 1;                 //make that job run
   busy = 1;
   bursttime[running]--;
   if(bursttime[running] == 0){
    busy = 0;
    state[running] = 3;
   }
  }
  else{                                   //condition of job is running
   bursttime[running]--;
   if(bursttime[running] <= 0){         //job done
    busy = 0;                        //reset
    state[running] = 3;
   }
  }
  for(i=0;i<SIZE;i++){                    //count up waiting time
   if(state[i] == 2){
    waitingtime[i]++;
   }
  }
  time++;
 }
 for(i=0;i<SIZE;i++){              //calculate average waiting time & print each waiting time
  printf("P%2d=%2d\n",i+1,waitingtime[i]);
  sum+=waitingtime[i];
 }
 printf("\nAverage wainting time:%.1f\n",sum/1.0/SIZE);
}
