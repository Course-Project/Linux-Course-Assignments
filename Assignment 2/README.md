第二次作业
=========

## Is the COW technique same with running in the parent's address space?

这两者显然不一样。COW(Copy on Write) 是指所请求的资源在被修改时才会被复制一份，一般出现在一个资源被多个对象请求时，这样可以避免不必要的开销。运行在父进程地址空间意味着父子进程都会使用同样的一份数据，任何一方修改，另一方也能觉察到。

## `fork`和`vfork`有什么不同，写一个程序来验证你的答案

#### 区别

利用`fork`创建子进程时，子进程完全复制父进程的资源，这样得到的子进程独立，有良好的并发性，并且`fork`执行后，复制并不会马上进行，因为子进程可能对这些资源不进行任何更改，所以系统采用了一种叫做COW(Copy on Write)的技术，也就是说知道资源被改动，才会复制出一份副本。

`vfork`则不同于`fork`，用`vfork`创建的子进程与父进程共享地址空间，也就是说子进程完全运行在父进程的地址空间上，如果这时子进程修改了某个变量，这将影响到父进程。另外`vfork`调用之后，父进程会阻塞，知道子进程调用`_exit()`终止，或调用`exec`函数族成员。

#### 参考

1. [http://blog.sina.com.cn/s/blog_7673d4a5010103x7.html](fork、vfork、clone区别)
2. [http://www.cnblogs.com/li-hao/archive/2011/10/19/2218317.html](fork与vfork的区别)

## 写一个程序去对比父子进程的阻塞和非阻塞等待，同时展示Memory Layout(内存空间分布)的变化

#### 源文件

- 3.wait-block.c
- 3.wait-noblock.c

#### 用法

```bash
$ ./3.wait-block
$ ./3.wait-noblock
```

## How can you write a shell? Practice it.

#### 思路

一开始打算偷懒，直接将用户输入传给`system`函数，但事实上有些指令是无法这样执行的，比如`cd`，因为进程间并未有通信，父进程的工作目录没有更改，通过`cd`后再执行`ls`就可以看出这一点。

所以，这个shell还是要好好想想的，我的另一个思路是用`vfork`后调用`exec`去执行用户所输入的命令，当然得补全路径，可以通过处理环境变量`$PATH`来实现。

最终的做法是，`cd`和`exit`单独处理，其他的丢给`system`函数去做。事实是，手贱用`vfork`加`execl`来实现`system`，略繁琐。

#### 源文件

- 4.shell.c

#### 用法

```bash
$ ./4.shell
```
