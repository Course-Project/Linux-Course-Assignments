#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define err_sys(info) { \
    fprintf(stderr, "%s: %s\n", info, strerror(errno)); \
    exit(EXIT_FAILURE); \
}

void pre_exit(int status) {
    if (WIFEXITED(status))
        printf("normal termination, exit status=%d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number=%d%s\n", WTERMSIG(status), WCOREDUMP(status) ? "(core file generated)" : "");
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));
}

int main(int argc, const char *argv[]) {
    pid_t pid, _pid;
    int status;
    
    pid = fork();
    
    if (pid < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        // 子进程
        printf("in child process\n");
        printf("child pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgid(getpid()));
        printf("child process is still running\n");
        sleep(3);
        exit(EXIT_SUCCESS);
    } else {
        // 父进程
        printf("before waiting\n");
        while (1) {
            _pid = waitpid(pid, &status, WNOHANG);
            if (_pid < 0) {
                err_sys("wait error");
            } else if (0 == _pid) {
                sleep(1);
            } else {
                break;
            }
        }
        printf("after waiting\n");
        printf("in parent process\n");
        printf("parent pid=%d, ppid=%d, pgid=%d\n", getpid(), getppid(), getpgid(getpid()));
        pre_exit(status);
    }
    
    exit(EXIT_SUCCESS);
}
