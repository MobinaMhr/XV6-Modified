#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_get_uncle_count(void)
{
  int pid;
  if (argint(0, &pid) < 0)
    return -1;
  return uncle_count(pid);
}

int
sys_get_process_lifetime()
{
    int pid;
  if (argint(0, &pid) < 0)
    return -1;
  return process_lifetime(pid);
}

int sys_set_bjs_process_parameters(void)
{
  int pid;
  float priority_ratio;
  float arrival_time_ratio;
  float executed_cycle_ratio;
  float process_size_ratio;


  if (argint(0, &pid) < 0)
    return -1;
  if (argfloat(1, &priority_ratio) < 0)
    return -1;
  if (argfloat(2, &arrival_time_ratio) < 0)
    return -1;
  if (argfloat(3, &executed_cycle_ratio) < 0)
    return -1;
  if (argfloat(4, &process_size_ratio) < 0)
    return -1;

  return set_bjs_process_parameters(pid, priority_ratio, arrival_time_ratio, executed_cycle_ratio, process_size_ratio);
}

int
sys_set_bjf_system_parameters(void)
{
  int pid;
  float priority_ratio;
  float arrival_time_ratio;
  float  executed_cycle_ratio;
  float process_size_ratio;

  if(argint(0, &pid) < 0)
    return -1;
  if(argfloat(1, &priority_ratio) < 0)
    return -1;
  if(argfloat(2, &arrival_time_ratio) < 0)
    return -1;
  if(argfloat(3, &executed_cycle_ratio) < 0)
    return -1;
  if (argfloat(4, &process_size_ratio) < 0)
    return -1;

  set_bjf_system_parameters(priority_ratio, arrival_time_ratio, executed_cycle_ratio, process_size_ratio);
  return 0;
}

int
sys_print_process_info_table(void)
{
  print_process_info_table();
  return 0;
}

int
sys_transfer_process_queue(void)
{
  int queue_number, pid;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &queue_number) < 0)
    return -1;
  if(queue_number < RR)
    return -1;  
  if(queue_number > BJF)
    return -1;

  return transfer_process_queue(pid, queue_number);
}

