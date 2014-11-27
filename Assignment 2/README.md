第二次作业
=========

## Is the COW technique same with running in the parent's address space?

这两者显然不一样。COW(Copy on Write) 是指所请求的资源在被修改时才会被复制一份，一般出现在一个资源被多个对象请求时，这样可以避免不必要的开销。运行在父进程地址空间意味着父子进程都会使用同样的一份数据，任何一方修改，另一方也能觉察到。

## What are the differences between fork and vfork? Write a program to verify your answer.

#### 用法

```bash
$ 
```

## Write a program to show the child process wait the parent process with a block style and a noblock style to terminate. Then show the changing of memory layout.

#### 用法

```bash
$ 
```

## How can you write a shell? Practice it.

#### 思路


