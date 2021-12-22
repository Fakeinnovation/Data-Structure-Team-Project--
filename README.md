# Data-Structure-Team-Project-CPU_Scheduling

A simple C-based programming project for simulating CPU process scheduling.

## Introduction

1 . The project has two versions : Array and Linked list.

2 . Algorithms to compare:
1. First-come, first serve (or first-in, first out)
2. Round robin (with different quantum size)
3. Shortest job first (non-preemptive)
4. Shortest job first (preemptive)

3 . The step of CPU_Scheduling

First Put the data in a job queue,then Move Process in the job queue to the ready queue according to time.Pick one Process (It may changed with different algorithms) to make it running to consume the burst time or quantum.Lastly, Record the waiting time if the process is not preempted; otherwise, move the process back to the end of the ready queue.

The following example is the result of first_in_first_out :
```bash
No.1.1 first_in_first_out(sort by P1~P10)

P 1 waiting time :  0
P 2 waiting time :  7
P 3 waiting time : 15
P 4 waiting time : 17
P 5 waiting time : 30
P 6 waiting time : 34
P 7 waiting time : 43
P 8 waiting time : 44
P 9 waiting time : 58
P10 waiting time : 63

Average Waiting Time : 31.10
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
 
 ## Coauthor
  
  408415068廖子靚
  
  408415060藍鴻毅 
  
  408220045詹雨婷 
  
  408420083陳昀顥
 
 ## Abstracts of data versions

