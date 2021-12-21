#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct node{
	int arrivaltime;
	int bursttime;
	struct node * next;
}storage;
typedef struct QType{
	int count;
	storage * front;
	storage * rear;
}QType;

QType * newQueue(void);
void enQ(QType *,int,int);
void enQ2(QType*,int,int);
storage* deQ(QType *);
void delQueue(QType **);
void fcfs(QType*);
void psjf(QType*,int);
void rr(QType*);
void sjf(QType*);

int main()
{
    int i=0;
    int total_burst=0;
    QType*Q,*q,*Q2,*Q3;
    Q = newQueue();
    q = newQueue();
    Q2 = newQueue();
    Q3 = newQueue();
    int burst[SIZE]={7,8,2,13,4,9,1,14,5,3};
    int arrival[SIZE]={0,2,4,5,7,9,10,13,18,20};
    for(i=0;i<SIZE;i++){
    total_burst=total_burst+burst[i];
    }
    for(i=0;i<SIZE;i++){
        enQ(Q,arrival[i],burst[i]);
        enQ(q,arrival[i],burst[i]);
        enQ(Q2,arrival[i],burst[i]);
        enQ(Q3,arrival[i],burst[i]);
    }
    fcfs(Q);
    rr(Q2);
	sjf(Q3);
    psjf(q,total_burst);

	delQueue(&Q);
    delQueue(&q);
    delQueue(&Q2);
    delQueue(&Q3);
    return 0;
}
void fcfs(QType*q)
{
    printf("No.1 First come first serve:\n");
    printf("\nWaiting time for ...\n");
    int i,j;
    int waiting_time[SIZE]={0};
    storage* p;
    for(i=0;i<SIZE-1;i++){
        p=deQ(q);
        for(j=SIZE-1;j>i;j--){
        	waiting_time[j]=waiting_time[j]+(p->bursttime);
    	}
    }
    int total=0;
    double awt;
    for(i=0;i<SIZE;i++){
        printf("P%2d=%2d\n",i+1,waiting_time[i]);
        total=total+waiting_time[i];
    }
    awt=(double)total/SIZE;
    printf("\nAverage waiting time:%.1f\n",awt);

}
void psjf(QType*q,int tb)
{
    printf("\nNo.4 Preemptive SJF:\n");
    printf("\nWaiting time for ...\n");
    int w1[21]={0};
    int w2[21]={0};
    int waiting_time[21]={0};
    int i=0;
    QType*t;
    t=q;
    QType*Q2;
    Q2= newQueue();//ready queue
    storage* p,*n;
    for(i=0;i<tb-1;i++){
    	if(i==0){
        	p=deQ(q);
    	}
    	if(q->front!=NULL&&q->front->arrivaltime==i){
    		n=deQ(q);
    		if(p->bursttime>n->bursttime){
    			enQ2(Q2,p->arrivaltime,p->bursttime);
    			w1[p->arrivaltime]=w1[p->arrivaltime]+i;
    			p=n;
    		}
    		else{
       			enQ2(Q2,n->arrivaltime,n->bursttime);
       			w1[n->arrivaltime]=w1[n->arrivaltime]+i;
    		}
    	}
    	(p->bursttime)--;
    	if(p->bursttime==0){
      		p=deQ(Q2);
      		w2[p->arrivaltime]=w2[p->arrivaltime]+i+1;
    	}

    }

	int arrival[SIZE]={0,2,4,5,7,9,10,13,18,20};
    int j,k;
    int total=0;
    double awt;
    for(j=0;j<21;j++){
        waiting_time[j]=w2[j]-w1[j];
        for(k=0;k<SIZE;k++){
        	if(j==arrival[k]){
        	printf("P%2d=%2d\n",k+1,waiting_time[j]);
        	}
		}
        total=total+waiting_time[j];
    }
    awt=(double)total/SIZE;

    printf("\nAverage wainting time:%.1f\n",awt);
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
void delQueue(QType ** Q){
 	storage * temp;
 	while((*Q)->count > 0){
  		temp = (*Q)->front;
  		while(temp->next != NULL){
   			temp = temp->next;
  		}
  		free(temp);
  	(*Q)->count--;
 	}
 	free(*Q);
}
void enQ2(QType * Q,int arrivaltime,int bursttime){
 	storage * New,*T,*P;
 	New = malloc(sizeof(storage));
 	New->arrivaltime = arrivaltime;
 	New->bursttime = bursttime;
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
void rr(QType* Q)
{
	printf("\nNo.2 Round robbin:\n(Set time quantum 4)\n\nWaiting time for ...\n");
	int time=0,i,j=0,d,tbr=0,runt,sum=0,busy=0;//busy 1 for running,0 for done
	int arrivaltime[SIZE],waitingtime[SIZE],bursttime[SIZE],state[SIZE];//state 1 for processing,2 for waiting,3 for done
	storage * temp;
	for(i=0;i<SIZE;i++){
		temp = deQ(Q);
		bursttime[i]=temp->bursttime;
		arrivaltime[i]=temp->arrivaltime;
		waitingtime[i] = 0;
		state[i] = 0;
	}
	while(1){
		if(time == arrivaltime[j]){
			state[j] = 2;
			j++;
		}
		if(!busy){
			while(1){
				if(state[tbr] == 2){
					state[tbr] = 1;
					runt = 0;
					time--;
					busy=1;
					break;
				}
				if(tbr==9){
					tbr=-1;
				}
				tbr++;
			}
		}
		else{
			runt++;
			bursttime[tbr]--;
			for(i=0;i<SIZE;i++){ //waiting time
				if(state[i] == 2){
					waitingtime[i]++;
				}
			}
			if(bursttime[tbr] == 0){//job done
				busy = 0;
				state[tbr] = 3;
			}
			else if(runt == 4){  //line up
				state[tbr] = 2;
				tbr++;;
				busy=0;
			}
		}
		time++;
		d=0;
		for(i=0;i<SIZE;i++){
			if(state[d] == 3){
				d++;
			}
		}
		if(d == SIZE){
			break;
		}
	}
	for(i=0;i<SIZE;i++){
		printf("P%2d=%2d\n",i+1,waitingtime[i]);
		sum+=waitingtime[i];
	}
	printf("\nAverage wainting time:%.1f\n",sum/1.0/SIZE);
}
void sjf(QType* Q)
{
	printf("\nNo.3 Shortest job first:\n\nWaiting time for ...\n");
	int time=0,i,min,tbr,sum=0,busy=0;//busy 1 for running,0 for done
	int waitingtime[SIZE]={0},bursttime[SIZE]={0},state[SIZE]={0};//state 1 for processing,2 for waiting,3 for done
	storage * temp;
	while(1){
		if(Q->front->arrivaltime == time){
			temp = deQ(Q);
			bursttime[SIZE-(Q->count)-1]=temp->bursttime;
			state[SIZE-(Q->count)-1]=2;
		}
		if(!busy){
			min=99;
			for(i=0;i<SIZE;i++){
				if(state[i] == 2  &&  bursttime[i] < min){
					min = bursttime[i];
					tbr = i;
				}
			}
			state[tbr]--;
			busy = 1;
		}
		else{
			bursttime[tbr]--;
			for(i=0;i<SIZE;i++){
				if(state[i] == 2){
					waitingtime[i]++;
				}
			}
			if(bursttime[tbr] == 0){
				busy = 0;
				state[tbr] = 3;
			}
		}
		time++;
		if(state[7] == 3) break;
	}
	for(i=0;i<SIZE;i++){
		printf("P%2d=%2d\n",i+1,waitingtime[i]);
		sum+=waitingtime[i];
	}
	printf("\nAverage wainting time:%.1f\n",sum/1.0/SIZE);
}
