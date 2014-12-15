#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <setjmp.h>
#include <signal.h>

#define err_sys(info) { \
    fprintf(stderr, "%s: %s\n", info, strerror(errno)); \
    exit(EXIT_FAILURE); \
}

sigjmp_buf env;

void SIGFPE_handler(int sigsum) {
    if (sigsum == SIGFPE) {
        printf("can't be divided by 0: %s\n", strerror(errno));
        siglongjmp(env, SIGFPE);
    }
}

int main(int argc, const char *argv[]) {
    if (signal(SIGFPE, SIGFPE_handler) == SIG_ERR)
        err_sys("signal(SIGFPE) error");
    
    int jmpResult = sigsetjmp(env, 1);
    printf("sigjmpresult: %d\n", jmpResult);
    if (0 == jmpResult) {
        printf("%d\n", 5 / 0);
    } else {
        printf("jmp finished + %d\n", jmpResult);
    }
    
    exit(EXIT_SUCCESS);
}
