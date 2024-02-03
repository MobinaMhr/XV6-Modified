#include "types.h"
#include "user.h"

#define NO_PROCS 5

int main()
{
  init_prioritylock();
  for (int i = 0; i < NO_PROCS; i++)
  {
    int pid = fork();
    if (pid < 0)
    {
      printf(1, "Fork failed.\n");
      exit();
    }
    else if (pid == 0)
    {
      acquire_prioritylock();
      printf(1, "Process %d acquired the lock.\n", getpid());
      sleep(200);
      printf(1, "Process %d released the lock.\n", getpid());
      release_prioritylock();
      exit();
    }
  }
  while (wait() != -1)
      ;
  exit();
}