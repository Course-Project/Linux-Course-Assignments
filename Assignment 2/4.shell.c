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
    while (scanf("%[^\n]", str) != EOF) {
        getchar(); // 读取回车
        
        if (strcmp(str, "exit") != 0) system(str);
        else break;
        
        memset(str, 0, sizeof(str));
    }
    exit(EXIT_SUCCESS);
}
