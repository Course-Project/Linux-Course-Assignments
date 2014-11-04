//
//  insert.c
//  Test
//
//  Created by Tom Hu on 11/1/14.
//  Copyright (c) 2014 Tom Hu. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    // 判断参数
    if (argc != 4) {
        fprintf(stderr, "usage: insert <offset> <src> <dst>\n");
        return 1;
    }
    

    off_t offset; // 偏移量
    const char *file_src, *file_dst; // 文件地址
    int fs, fd; // 文件描述符
    struct stat fs_sbuf, fd_sbuf; // 文件属性
    char *fs_buffer, *fd_buffer; // 文件缓冲区
    
    // 获取位移量
    offset = atoi(argv[1]);
    
    // 获取文件地址
    file_src = argv[2];
    file_dst = argv[3];
    
    // 打开文件
    fs = open(file_src, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    // 处理文件错误
    if (fs == -1) {
        // 文件打开错误
        // fd不会出错，因为会自动新建
        fprintf(stderr, "%s: %s\n", file_src, strerror(errno));
        return 1;
    }

    fd = open(file_dst, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    
    // 获取文件属性
    stat(file_src, &fs_sbuf);
    stat(file_dst, &fd_sbuf);
    
    offset = offset > fd_sbuf.st_size ? fd_sbuf.st_size : offset;
    offset = offset > 0 ? offset : 0;
    
    // 修改目标文件偏移量
    lseek(fd, offset, SEEK_SET);
    
    // 获取待插入的文本
    fs_buffer = (char *)malloc(fs_sbuf.st_size * sizeof(char));
    read(fs, fs_buffer, fs_sbuf.st_size);
    
    // 获取偏移量之后的文本
    fd_buffer = (char *)malloc(fd_sbuf.st_size * sizeof(char));
    read(fd, fd_buffer, fd_sbuf.st_size);
    
    // 重新写入
    lseek(fd, offset, SEEK_SET);
    write(fd, fs_buffer, fs_sbuf.st_size);
    write(fd, fd_buffer, fd_sbuf.st_size);
    
    // 释放内存
    free(fs_buffer);
    free(fd_buffer);
    
    // 关闭文件
    close(fs);
    close(fd);
    
    return 0;
}
