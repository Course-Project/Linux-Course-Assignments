第三次作业
=========

最好在自己机器上先编译，生成两个可执行文件

```bash
$ make
```

如需删除可执行文件

```bash
$ make clean
```

## Write a program to handle the exception of divided by 0.

#### 源文件

- signal_handler.c

#### 用法

```bash
$ ./signal_handler
```

## What problems are there for normal signal handling?

#### 源文件

- signal_real_normal.c

#### 用法

```bash
$ ./signal_real_normal
```

#### 使用效果

进程号为：2759

![程序运行](https://raw.githubusercontent.com/h1994st/Linux-Project/master/Assignment%203/img/1.png)

![发送信号](https://raw.githubusercontent.com/h1994st/Linux-Project/master/Assignment%203/img/2.png)

其中`kill -34 2759`是发送`SIGRTMIN`信号给进程
