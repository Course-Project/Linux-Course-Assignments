#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define MAX_SIZE 1024

#define err_sys(info) { \
    fprintf(stderr, "%s: %s\n", info, strerror(errno)); \
    exit(EXIT_FAILURE); \
}

int main(int argc, const char *argv[]) {
    char str[MAX_SIZE];
    pid_t pid;
    while (scanf("%[^\n]", str) != EOF) {
        getchar(); // 读取回车
        
        if (strcmp(str, "exit") == 0) break;
        
        pid = vfork();
        if (pid < 0) {
            err_sys("vfork error");
        } else if (pid == 0) {
            if (execlp("ls", "ls", "/Users/tomhu/Desktop", NULL) < 0) {
                fprintf(stderr, "sh: command not found: %s\n", "");
            }
            _exit(EXIT_SUCCESS);
        }
        
        memset(str, 0, sizeof(str));
    }
    exit(EXIT_SUCCESS);
}
