#include "types.h"
#include "user.h"

void get_info()
{
    print_process_info_table();
}

void help()
{
    printf(1, "\n");
    printf(1, "usage: command <inputs>\n");
    printf(1, "list of commands:\n");
    printf(1, "    get_info\n");
    printf(1, "    transfer_queue <pid> <new_queue>\n");
    printf(1, "    set_bjf_process <pid> <priority_ratio> <arrival_time_ratio> <executed_cycles_ratio> <process_size_ratio>\n");
    printf(1, "    set_bjf_system <priority_ratio> <arrival_time_ratio> <executed_cycles_ratio> <process_size_ratio>\n");
    printf(1, "\n");
}

void transfer_queue(int pid, int new_queue_id)
{
    if (pid < 1)
    {
        printf(1, "pid under 1 cannot exist\n");
        return;
    }
    if (new_queue_id < 1)
    {
        printf(1, "new queue id cannot be under 1\n");
        return;
    }
    if (new_queue_id > 3)
    {
        printf(1, "new queue id cannot be above 3\n");
        return;
    }

    int transfer_res = transfer_process_queue(pid, new_queue_id);

    if (transfer_res < 0)
        printf(1, "ERROR in Transfer queue system call.\n");
    else
        printf(1, "Queue of proc with pid = %d changed successfully from %d to %d\n", pid, transfer_res, new_queue_id);
}

void set_bjf_process_params(int pid, float priority_ratio, float arrival_time_ratio, float executed_cycles_ratio, float process_size_ratio)
{
    if (pid < 1)
    {
        printf(1, "pid cannot be less than 1\n");
        return;
    }
    if (priority_ratio < 0)
    {
        printf(1, "priority ratio cannot be less than 0\n");
        return;
    }
    if (arrival_time_ratio < 0)
    {
        printf(1, "arrival time ratio cannot be less than 0\n");
        return;
    }
    if (executed_cycles_ratio < 0)
    {
        printf(1, "executed cycles ratio cannot be less than 0\n");
        return;
    }
    if (process_size_ratio < 0)
    {
        printf(1, "size ratio cannot be less than 0\n");
        return;
    }

    int result = set_bjs_process_parameters(pid, priority_ratio, arrival_time_ratio, executed_cycles_ratio, process_size_ratio);

    if (result < 0)
        printf(1, "ERROR in setting bjf process parameters.\n");
    else
        printf(1, "the bjf parameters related to process(id:%d) changed successfully.\n", pid);
}

void set_bjf_system_params(float priority_ratio, float arrival_time_ratio, float executed_cycles_ratio, float process_size_ratio)
{
    if (priority_ratio < 0)
    {
        printf(1, "priority ratio cannot be less than 0\n");
        return;
    }

    if (arrival_time_ratio < 0)
    {
        printf(1, "arrival time ratio cannot be less than 0\n");
        return;
    }

    if (executed_cycles_ratio < 0)
    {
        printf(1, "executed cycles ratio cannot be less than 0\n");
        return;
    }

    if (process_size_ratio < 0)
    {
        printf(1, "size ratio cannot be less than 0\n");
        return;
    }

    set_bjf_system_parameters(priority_ratio, arrival_time_ratio, executed_cycles_ratio, process_size_ratio);
    printf(1, "the bjf parameters related to system changed successfully.\n");
}

int main(int argc, char *argv[])
{
    if (argc == 2 && !strcmp(argv[1], "get_info"))
        get_info();
    else if (argc == 4 && !strcmp(argv[1], "transfer_queue"))
        transfer_queue(atoi(argv[2]), atoi(argv[3]));
    else if (argc == 7 && !strcmp(argv[1], "set_bjf_process"))
        set_bjf_process_params(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]));
    else if (argc == 6 && !strcmp(argv[1], "set_bjf_system"))
        set_bjf_system_params(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    else
        help();
    exit();
}