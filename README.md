# XV6 Modified
An these projects, some features were added to the [**xv6**](https://github.com/mit-pdos/xv6-public) operating system (x86 architecture).

## Experiment 1: Introduction to xv6

### Task 1: Boot Message

The name of group members appears as message when the system boots up:

### Task 2: Console Features

The following keyboard shortcuts are added to the console:

- `Ctrl+N`     : Removes all the digits from the console
- `Ctrl+R`     : Reverses the current line
- `Tab`        : Substitutes the current line with a command from the history (if exists)
- `Ctrl+B`     : Moves the cursor one character to the left
- `Ctrl+F`     : Moves the cursor one character to the right
- `Ctrl+L`     : Clears the console
- `Arrow Up`   : Shows the previous command in the history
- `Arrow Down` : Shows the next command in the history

### Task 3: User Program

A `strdiff` program is added to the system.  
This program finds the difference between two strings.  
The program is called as follows:

```text
strdiff a b
```

The result is then printed in the `strdiff_result.txt` file.

## Experiment 2: System Calls

### Task 1: System Call Using Registers

The `find_digit_root` system call is added to the system.  
This system call finds the largest prime factor of a given number.  
The system call is called as follows:

```c++
int find_digit_root(void);
```

The parameter (an integer) should be passed in the `ebx` register.

### Task 2: System Call Using Stack

- The `copy_file` system call is added to the system.  
This system call copies a file to another location.

```c++
int copy_file(char *path, int size);
```

- The `get_uncle_count` system call is added to the system.  
This system call returns the number of uncle processes of the current process.  

```c++
void get_uncle_count(void);
```

- The `get_process_lifetime` system call is added to the system.  
This system call returns the lifetime of the current process.

```c++
int get_process_lifetime(void);
```

## Experiment 3: Process Scheduling

### Task 1: Multi-Level Feedback Queue

An **MLFQ** scheduler is added to the system.  
The scheduler has 3 queues with the first one having the highest priority.  
The following queueing policies are used:

- The first queue is a round-robin queue with a time quantum of 1 tick.
- The second queue is LCFS (Last-Come-First-Served) which means the process that came last is executed first.
- The third queue is a BJF (Best-Job-First) queue in which the process with the lowest rank is executed.

### Task 2: Aging

All processes are started in the second queue (except the `init` and `sh` processes).  
If a **runnable** process has not been executed for *8000* ticks, it is moved to the first queue.

### Task 3: System Calls

The following system calls are added to the system:

- `change_scheduling_queue` : Changes the scheduling queue of a process.

```c++
int change_scheduling_queue(int pid, int queue);
```

- `set_bjf_params_process` : Sets the parameters of the BJF algorithm for a process.

```c++
int set_bjf_params_process(int pid, float priority_ratio, float arrival_time_ratio, float executed_cycles_ratio);
```

- `set_bjf_params_system` : Sets the parameters of the BJF algorithm for the system.

```c++
int set_bjf_params_system(float priority_ratio, float arrival_time_ratio, float executed_cycles_ratio);
```

- `print_process_info` : Prints the information of processes in a table.

```c++
void print_process_info(void);
```

All of the aforementioned system calls are accessible using the `schedule` user program:

```text
usage: schedule command [arg...]
Commands and Arguments:
  info
  set_queue <pid> <new_queue>
  set_process_bjf <pid> <priority_ratio> <arrival_time_ratio> <executed_cycle_ratio>
  set_system_bjf <priority_ratio> <arrival_time_ratio> <executed_cycle_ratio>
  set_priority_bjf <pid> <priority>
```

## Experiment 4: Synchronization

### Task 1: Number of System Calls

As a part of the synchronization experiment, the number of system calls is counted. First we make sure to run the operating system on 4 cores, then we run the `getnsyscalls` program. The program is called as follows:

```c++
int getnsyscalls();
```

This result of counting number of system calls in each core and summation of them is printed to the console. To make sure that the system calls are counted correctly, we used spin locks to prevent any process from being interrupted while counting the system calls.

### Task 2: Priority Lock

A priority lock is added to the system. It follows the spin lock policy. The following system calls are added to the system:

```c++
void acquirepriority(struct prioritylock* lk);
void releasepriority(struct prioritylock* lk);
```

The `prioritylock` structure is defined as follows:

```c++
struct prioritylock {
uint locked; // Is the lock held?
struct spinlock lk; // spinlock protecting this priority lock
int inqueue; // number of processes waiting in queue
int lockreq[NPROC]; // pid of processes which requested priority lock
int pid; // Process holding lock
char* name; // Name of lock
};
```

Then for testing the priority lock, we used the `prio` user program. The program is called as follows:

```text
prio
```

The program creates 10 processes and each process tries to acquire the priority lock. The process with the highest priority should be able to acquire the lock first. The process with the lowest priority should be able to acquire the lock last. The program prints the order of the processes that acquired the lock to the console.


## Experiment 5: Memory Management

In this experiment, A shared memory system is added to the system. `shpage` and `shmemtable` were added for managing the shared memory also the following system calls are added to the system to interact with them, each process stores its shared memory in the `shmemtable` and the `shpage` is used to manage the shared memory.

```c++
char* openshmem(int id);
int closeshmem(int id);
```

To test the shared memory system, we used the `shmem_test` user program. It creates multiple process and each process changes the value of a shared memory and prints the value of the shared memory to the console. The program is called as follows:

```text
shmem_test
```
