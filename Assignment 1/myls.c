//
//  myls.c
//  Test
//
//  Created by Tom Hu on 11/1/14.
//  Copyright (c) 2014 Tom Hu. All rights reserved.
//

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#define MAXLENGTH 1024

void ana_dir(const char *name, const u_int8_t option);
void get_file(const char *dir, const char *name);
void get_file_info(const char *dir, const char *name);
void get_file_mode_str(const mode_t file_mode, char *mode_str);

void ana_dir(const char *name, const u_int8_t option) {
    DIR *dp; // 文件夹指针
    struct dirent *dirp; // 文件结构
    
    // 打开文件夹
    if ((dp = opendir(name)) == NULL) {
        fprintf(stderr, "ls: %s: No such file or directory.\n", name);
        return;
    }
    
    // 遍历文件夹
    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_name[0] == '.') {
            // 排除隐藏文件
            continue;
        }
        
        if (option) {
            get_file_info(name, dirp->d_name);
            printf("\n");
        } else {
            get_file(name, dirp->d_name);
        }
    }
    if (!option) {
        printf("\n");
    }
    
    // 关闭文件夹
    closedir(dp);
}

void get_file(const char *dir, const char *name) {
    printf("%s  ", name);
}

void get_file_info(const char *dir, const char *name) {
    struct stat sbuf;
    char mode_str[11];
    char path[MAXLENGTH];
    
    // 拼接路径
    long l = strlen(dir);
    strcpy(path, dir);
    if (path[l - 1] != '/')
        strcat(path, "/");
    strcat(path, name);
    
    stat(path, &sbuf);
    
    // 处理权限字符串
    get_file_mode_str(sbuf.st_mode, mode_str);
    
    printf("%s %3d %5s %s %7d %.20s %s",
           mode_str,
           sbuf.st_nlink,
           getpwuid(sbuf.st_uid)->pw_name,
           getgrgid(sbuf.st_gid)->gr_name,
           (int)sbuf.st_size,
           ctime(&sbuf.st_mtime),
           name);
}

void get_file_mode_str(const mode_t file_mode, char *mode_str) {
    // 文件类型
    switch (file_mode & S_IFMT) {
        case S_IFREG: mode_str[0] = '-'; break;
        case S_IFDIR: mode_str[0] = 'd'; break;
        case S_IFCHR: mode_str[0] = 'c'; break;
        case S_IFBLK: mode_str[0] = 'b'; break;
        case S_IFIFO: mode_str[0] = 'l'; break;
        case S_IFLNK: mode_str[0] = 'l'; break;
        case S_IFSOCK: mode_str[0] = 'l'; break;
        default: mode_str[0] = '?'; break;
    }
    
    // 用户权限
    mode_str[1] = file_mode & S_IRUSR ? 'r' : '-';
    mode_str[2] = file_mode & S_IWUSR ? 'w' : '-';
    mode_str[3] = file_mode & S_ISUID ? 's' : (file_mode & S_IXUSR ? 'x' : '-');
    
    // 组权限
    mode_str[4] = file_mode & S_IRGRP ? 'r' : '-';
    mode_str[5] = file_mode & S_IWGRP ? 'w' : '-';
    mode_str[6] = file_mode & S_ISGID ? 's' : (file_mode & S_IXGRP ? 'x' : '-');
    
    // 其他用户权限
    mode_str[7] = file_mode & S_IROTH ? 'r' : '-';
    mode_str[8] = file_mode & S_IWOTH ? 'w' : '-';
    mode_str[9] = file_mode & S_ISVTX ? 't' : (file_mode & S_IXOTH ? 'x' : '-');
    
    mode_str[10] = '\0';
}

int main(int argc, const char *argv[]) {
    if (argc == 1) {
        // 当前目录，无-l
        ana_dir(".", 0);
        return 0;
    }
    
    bool with_option = (strcmp("-l", argv[1]) == 0);
    
    if (argc > 2 + with_option) {
        // 指定两个以上的目录
        // 需指明
        for (int i = 1 + with_option; i < argc; i++) {
            printf("%s:\n", argv[i]);
            ana_dir(argv[i], with_option);
            if (i != argc - 1) printf("\n");
        }
    } else if (argc == 2 + with_option) {
        // 仅一个目录
        ana_dir(argv[1 + with_option], with_option);
    } else {
        // 当前目录
        ana_dir(".", with_option);
    }
    
    return 0;
}
