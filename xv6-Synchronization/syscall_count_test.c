#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

const char* fileNames[] = {
    "output0.txt",
    "output1.txt",
    "output2.txt",
    "output3.txt",
    "output4.txt"
};

void write_file(const char *text, int i)
{
    int fd = open(fileNames[i], O_WRONLY | O_CREATE);
    if (fd < 0)
    {
        printf(2, "Failed to open file for writing\n");
        exit();
    }
    write(fd, text, strlen(text));
    close(fd);
}

int main()
{
    for (int i = 0; i < 5; i++)
    {
        int pid = fork();
        if (pid < 0)
        {
            printf(2, "Fork failed\n");
            exit();
        }
        else if (pid == 0)
        {
            write_file("Dummy text for test!", i);
            exit();
        }
    }
    while (wait() != -1)
      ;
    print_cpu_syscalls_count();
    exit();
}