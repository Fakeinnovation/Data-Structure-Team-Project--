# Data-Structure-Team-Project-CPU_Scheduling

A simple C-based programming project for simulating CPU process scheduling.

## What's new?

1.The project has two versions : Array and Linked list.

2.Algorithms to compare:
1. First-come, first serve (or first-in, first out)
2. Round robin (with different quantum size)
3. Shortest job first (non-preemptive)
4. Shortest job first (preemptive)

The following example is result of first_in_first_out :
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

Use queues to implement the job queue and the ready queue, then accordind to each Process's arrival time & burst time operates Enqueue & Dequeue function. (It may changed with different algorithms)

## Usage

### Server

On server side, execute the `server` with a specified port number `[port]`. 1024 < `[port]` < 65536.

```bash
./server [port]
```

A directory `server_dir` will be created in the current directory. Files uploaded from clients are saved in `server_dir`, and clients can download files from it also.

The server is then listening for asked connection and command requests from clients.

### Client

On client side, execute the `client` with a specified IP address and port number `[ip:port]`. The IP address and port number should correspond to that of server.

```bash
./client [ip:port]
```

A directory `client_dir` will be created in the current directory. Files downloaded from the servers are saved in `client_dir`, and clients can upload files to server from it.

Each client first needs to type a username that is not registered in server currently, and after that it can send command requests to the server.

## Command

The server support the following commands for clients to request:

### ls
`ls` command shows all the files in `server_dir`:
```bash
ls
```

### get
Clients use `get` to download files from server.
```bash
get filename
```
The downloaded files are saved in `client_dir`.

### put
Clients use `put` to upload files to server.
```bash
put filename
```
The uploaded files will be saved in `server_dir` on server side.
