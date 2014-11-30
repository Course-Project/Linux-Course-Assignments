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
    int status;
    char *cmd, *rest, *path;
    while (1) {
        path = getcwd(NULL, 0);
        printf("guest@guest:%s$ ", path);
        scanf("%[^\n]", str);
        getchar(); // 读取回车
        
        if (strcmp(str, "exit") == 0) break; // 判断是否退出
        
        cmd = strtok_r(str, " ", &rest); // 分割字符串，用于判断cd命令
        
        if (strcmp(cmd, "cd") == 0) {
            if (rest) chdir(rest);
            continue;
        }
        
        if (rest) *(rest - 1) = ' ';
        
        pid = vfork();
        if (pid < 0) {
            err_sys("vfork error");
        } else if (pid == 0) {
            execl("/bin/sh", "sh", "-c", str, NULL);
            _exit(EXIT_SUCCESS);
        } else {
            waitpid(pid, &status, WUNTRACED); // 父进程等待子进程
        }
        
        memset(str, 0, sizeof(str));
        free(path);
    }
    exit(EXIT_SUCCESS);
}
