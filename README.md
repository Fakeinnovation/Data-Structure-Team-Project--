# Data-Structure-Team-Project-CPU_Scheduling

A simple C-based programming project for simulating CPU process scheduling.

## Introduction

1 . The project has two versions : Array and Linked list.

2 . Algorithms to compare:
1. First-come, first serve (or first-in, first out)
2. Round robin 
3. Shortest job first (non-preemptive)
4. Shortest job first (preemptive)

3 . The step of CPU_Scheduling

First Put the data in a job queue,then Move Process in the job queue to the ready queue according to time.Pick one Process (It may changed with different algorithms) to make it running to consume the burst time or quantum.Lastly, Record the waiting time if the process is not preempted; otherwise, move the process back to the end of the ready queue.

The following example is the result of first_come_first_serve :
```bash
No.1 First come first serve:

Waiting time for ...
P 1= 0
P 2= 5
P 3=11
P 4=12
P 5=23
P 6=25
P 7=33
P 8=31
P 9=40
P10=43

Average waiting time:22.3
```

## Usage

### Waiting time

After compiling program,it shows each Process's waiting time corresponding to four different CPU_scheduling.

The following words are definition of scheduling criteria : 

- CPU utilization : A computer's usage of processing resources, or the amount of work handled by a CPU.
- Throughput : Calculate how many Processes completed task in given time. 
- Waiting time (WT) : TurnAround Time - Burst Time.
- TurnAround Time (TAT) : Complete Time - Arrival Time.
- Complete Time (CT) : The time of the Process's Burst Time has been finished by CPU.
- Response Time (RT) : Amount of time it takes from when a request was submitted until the first response is produced.
 
 ## Abstracts of data versions

### Linked List

- 1220 : Fixed RR schduling & modify all results are Processes's waiting time.

### Array

- 1208 : Fixed RR schduling to Queue type.
- 1212 : Fixed RR timer.
- 1220 : Modify all results are Processes's waiting time. 

### Prototype

- 1209 : All CPU_schduling algorithms function almost done.

### Final System
- 1223 : Linked List have two version. 

- [x] Fixed_data version.
- [x] Random_data version.

- 1223 : Array have two version. 

- [x] Fixed_data version.
- [x] Random_data version. 

 ## Coauthor
  
  408415068廖子靚
  
  408415060藍鴻毅 
  
  408220045詹雨婷 
  
  408420083陳昀顥
