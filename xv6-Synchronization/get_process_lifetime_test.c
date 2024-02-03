#include "types.h"
#include "user.h"

void child_test()
{
    int child_pid = fork();
    if (child_pid > 0)
    {
        wait();
    }
    else if (child_pid == 0)
    {
        while (1)
        {
            if (get_process_lifetime(getpid()) >= 5)
            {
                printf(1, "child lifetime: %d seconds\n",get_process_lifetime(getpid()));
                kill(child_pid);
                break;
            }
        }
        exit();
    }
    else
    {
        printf(2, "Failed to create child process.\n");
    }
}

int main(int argc, char* argv[])
{
    int parent_pid = fork();
    if (parent_pid > 0)
    {
        wait();
    }
    else if (parent_pid == 0)
    {
        child_test();
        while (1)
        {
            if (get_process_lifetime(getpid()) >= 10)
            {
                printf(1, "parent lifetime: %d seconds\n",get_process_lifetime(getpid()));
                break;
            }
        }
        exit();
    }
    else
    {
        printf(2, "Failed to create parent process.\n");
    }
    exit();
}