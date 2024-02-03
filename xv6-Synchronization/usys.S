#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)

SYSCALL(find_digital_root)
SYSCALL(copy_file)
SYSCALL(get_uncle_count)
SYSCALL(get_process_lifetime)

SYSCALL(set_bjs_process_parameters)
SYSCALL(set_bjf_system_parameters)
SYSCALL(print_process_info_table)
SYSCALL(transfer_process_queue)

SYSCALL(init_prioritylock)
SYSCALL(acquire_prioritylock)
SYSCALL(release_prioritylock)

SYSCALL(print_cpu_syscalls_count)

SYSCALL(set_zero_syscall_count)