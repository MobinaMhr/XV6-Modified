#include "types.h"
#include "user.h"

#define SOME_BIG_NUM 1000000000000
#define NUM_FORKS 5

int main()
{
    transfer_process_queue(getpid(), 2);
    for (int i = 0; i < NUM_FORKS; ++i)
    {
        int pid = fork();
        if (pid > 0)
            continue;
        if (pid == 0)
        {
            int y;
            sleep(5000);
            y = 432;
            for (int j = 0; j < 100 * i; ++j)
            {
                y *= y;
                int x = 1;
                for (long k = 0; k < SOME_BIG_NUM; ++k)
                {
                    x++;
                    x /= y;
                } 

            }
            exit();
        }
    }
    while (wait() != -1)
        ;
    exit();
}