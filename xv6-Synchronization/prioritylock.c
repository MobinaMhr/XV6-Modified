#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "prioritylock.h"

void initprioritylock(struct prioritylock *plk, char *name)
{
  initlock(&plk->slk, "spin lock");
  plk->name = name;
  plk->pid_locked = 0;
  plk->head = 0;
}

void add_to_queue(struct prioritylock *plk)
{
  struct node* temp = (struct node *)kalloc();
  temp->priority = myproc()->pid;
  temp->next = 0;
  if(plk->head == 0)
  {
    temp->next = plk->head;
    plk->head = temp;
  }
  else
  {
    struct node* trace = plk->head;
    while(trace->next != 0 && temp->priority <= trace->next->priority)
    {
      trace = trace->next;
    }
    temp->next = trace->next;
    trace->next = temp;
  }
}

void print_queue(struct prioritylock *plk)
{
  struct node *temp = plk->head;
  cprintf("Queue: ");
  while (temp != 0)
  {
    cprintf("%d ", temp->priority);
    temp = temp->next;
  }
  cprintf("\n");
}

void remove_from_queue(struct prioritylock *plk)
{
  struct node *temp = plk->head;
  struct node *prev = temp;
  if (temp != 0 && temp->priority == plk->pid_locked)
  {
    plk->head = temp->next;
  }
  else
  {
    while (temp != 0 && temp->priority != plk->pid_locked)
    {
      prev = temp;
      temp = temp->next;
    }
    prev->next = temp->next;
  }
}

void acquirepriority(struct prioritylock *plk)
{
  acquire(&plk->slk);
  add_to_queue(plk);
  if (plk->pid_locked != myproc()->pid && plk->pid_locked != 0)
  {
    sleep(myproc(), &plk->slk);
  }
  print_queue(plk);
  plk->pid_locked = myproc()->pid;
  release(&plk->slk);
}

void releasepriority(struct prioritylock *plk)
{
  if(myproc()->pid == plk->pid_locked)
  {
    acquire(&plk->slk);
    if (plk->head == 0 || plk->head->next == 0)
    {
      plk->pid_locked = 0;
      plk->head = 0;
    }
    else
    {
      plk->pid_locked = plk->head->next->priority;
      struct node *temp = plk->head->next;
      plk->head = temp;
      awaken_proc(temp->priority);
    }
    release(&plk->slk);
  }
}