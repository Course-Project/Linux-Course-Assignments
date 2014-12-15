#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#define err_sys(info) { \
    fprintf(stderr, "%s: %s\n", info, strerror(errno)); \
    exit(EXIT_FAILURE); \
}

static void signal_handler(int signo) {
    if (SIGINT == signo) {
        printf("SIGINT\n");
    } else if (SIGQUIT == signo) {
        printf("SIGQUIT\n");
    } else if (SIGRTMIN == signo) {
        printf("SIGRTMIN\n");
    }
}

int main(int argc, const char *argv[]) {
    sigset_t newmask, oldmask, zeromask;
    
    if (signal(SIGINT, signal_handler) == SIG_ERR)
        err_sys("signal(SIGINT) error");
    if (signal(SIGQUIT, signal_handler) == SIG_ERR)
        err_sys("signal(SIGQUIT) error");
    if (signal(SIGRTMIN, signal_handler) == SIG_ERR)
        err_sys("signal(SIGRTMIN) error");

    sigemptyset(&newmask);
    sigemptyset(&zeromask);

    sigaddset(&zeromask, SIGINT);
    sigaddset(&zeromask, SIGRTMIN);

    sigaddset(&newmask, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("sigprocmask(SIG_BLOCK) error");

    printf("sigsuspend start\n");

    if (sigsuspend(&zeromask) != -1)
        err_sys("sigsuspend error");

    printf("sigsuspend end\n");
    
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("sigprocmask(SIG_SETMASK) error");
    
    printf("\n");
    
    exit(EXIT_SUCCESS);
}
