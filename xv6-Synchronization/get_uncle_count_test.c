#include "types.h"
#include "user.h"

void grand_child_for_third()
{
    int childpid = fork();
    if (childpid > 0)
        wait();
    else if (childpid == 0)
    {
        printf(1, "The child for third process has %d uncles\n", get_uncle_count(getpid()));
        exit();
    }
    else
    {
        printf(2, "Grandchild fork failed.\n");
        exit();
    }
    exit();
}

void third_child()
{
    int pid3 = fork();
    if (pid3 < 0)
    {
        printf(2, "Third child fork failed.\n");
        exit();
    }
    else if (pid3 == 0)
        grand_child_for_third();
    else
        wait();
}

void second_child()
{
    int pid2 = fork();
    if (pid2 < 0)
    {
        printf(2, "Second child fork failed\n");
        exit();
    }
    else if (pid2 == 0)
        sleep(50);
    else
        third_child();
    wait();
}

int main(int argc, char *argv[])
{
    int pid1 = fork();
    if (pid1 < 0)
    {
        printf(2, "First child fork failed\n");
        exit();
    }
    else if (pid1 == 0)
    {
        sleep(50);
    }
    else
    {
        second_child();
    }
    wait();
    exit();
}