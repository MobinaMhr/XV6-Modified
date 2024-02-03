#include "spinlock.h"

struct node{
    int priority;
    struct node *next;
};

struct prioritylock {
  uint pid_locked;       // The process which helds the lock
  struct spinlock slk; // spinlock protecting this sleep lock
  char *name;        // Name of lock.
  struct node *head; // Head of the queue
};
