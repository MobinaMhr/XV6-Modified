#include "types.h"
#include "user.h"

#define NEGATIVE_INPUT_ERROR "Invalid input. Input must be positive!\n"
#define FEW_ARGUMANT_ERROR "Less input. One integer input is needed!\n"

int digital_root_syscall(int n) {
    int prev_ebx;
    asm volatile(
        "movl %%ebx, %0\n\t"
        "movl %1, %%ebx"
        : "=r"(prev_ebx)
        : "r"(n)
    );
    int result = find_digital_root();
    asm volatile(
        "movl %0, %%ebx"
        :: "r"(prev_ebx)
    );
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf(2, FEW_ARGUMANT_ERROR);
        exit();
    }
    int n;
    if (strlen(argv[1]) >= 2 && argv[1][0] == '-')
    {
        argv[1][0] = '0';
        n = atoi(argv[1]);
        n = -n;
    }
    else
        n = atoi(argv[1]);

    if (n < 0) 
    {
        printf(2, NEGATIVE_INPUT_ERROR);
    }
    else 
    {
        int result = digital_root_syscall(n);
        printf(1, "Digital root is: %d\n", result);
    }
    exit();
}