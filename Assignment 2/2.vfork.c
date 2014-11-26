#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define err_sys(info) { \
    fprintf(stderr, "%s: %s\n", info, strerror(errno)); \
    exit(EXIT_FAILURE); \
}

int g = 521;
char buf[] = "hello, to stdout\n";

int main(int argc, const char *argv[]) {
    int l;
    pid_t pid;
    
    l = 125;
    
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        err_sys("write error");
    }
    printf("before call fork\n");
    
    pid = vfork();
    if (pid < 0) {
        err_sys("fork error");
    } else if (0 == pid) {
        // 子进程
        g--;
        l++;
        printf("in child process\n");
        printf("pid=%d, global=%d, local=%d\n", getpid(), g, l);
    } else {
        // 父进程
        printf("in parent process\n");
        printf("pid=%d, global=%d, local=%d\n", getpid(), g, l);
    }
    
    exit(0);
}
