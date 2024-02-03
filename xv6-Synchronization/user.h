struct stat;
struct rtcdate;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int set_bjs_process_parameters(int, float, float, float, float);
void set_bjf_system_parameters(float, float, float, float);
void print_process_info_table(void);
int transfer_process_queue(int, int);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);

// Extra
int find_digital_root(void);
int copy_file(const char *src, const char *dest);
int get_uncle_count(int);
int get_process_lifetime(int);
void init_prioritylock(void);
void acquire_prioritylock(void);
void release_prioritylock(void);
void print_cpu_syscalls_count(void);
void set_zero_syscall_count(void);