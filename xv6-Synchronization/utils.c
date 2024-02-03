#include "types.h"
#include "defs.h"

int digitcount(int num)
{
    if (num == 0)
        return 1;

    int count;
    for (count = 0; num != 0; ++count)
    {
        num /= 10;
    }

    return count;
}

void print_spaces(int count)
{
    for (int i = 0; i < count; ++i)
        cprintf(" ");
}

void print_header()
{
  cprintf("Process_Name    PID     State    Queue   Cycle   Arrival Priority R_Prty  R_Arvl  R_Exec  R_Size  Rank\n"
          "------------------------------------------------------------------------------------------------------\n");
}