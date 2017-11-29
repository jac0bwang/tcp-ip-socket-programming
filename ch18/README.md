1. 理解线程的概念
=================

### 多进程模型的缺点
- 创建进程的过程会带来一定的开销
- 进程间完成数据交换，需要用到特殊的IPC技术
- 进程的**上下文切换**带来巨大的开销

### 线程相比于进程具有如下的优点：
- 线程的创建和上下文的切换比进程的创建和上下文切换速度更快
- 线程间的数据交换不需要用到特殊的技术

### 进程和线程的差异
每个进程间的内存空间都是独立的，内存空间包括三个部分：数据区（保存全局变量）、堆区域（动态分配内存）、栈区域（函数运行时使用、局部变量）。<br>
多个线程间的静态数据区和堆区域是共享的，只有栈区域时独立的。这种方式可以获得如下优势：
- 上下文切换时不需要切换数据区和堆区域
- 可以通过数据区和堆交换数据

进程 ： 在操作系统构成单独执行流的单位
线程 ： 在进程构成单独执行执行流的单位

2. 线程创建及运行(线程在进程中创建并运行)
=========================================
```
#include<pthread.h>
int pthread_create(
    pthread_t* restrict thread, const pthread_attr_t* restrict attr, 
    void* (*start_routine)(void*), void* restrict arg
);
//成功时返回0，失败时返回其他值

//thread：保存新创建进程ID的变量地址值。线程与进程相同，也需要用于区分不同线程的ID
//attr：用于传递线程属性的参数，NULL表示创建默认属性的线程
//start_routine：线程的执行流函数指针(函数指针)
//arg：第三个参数函数指针的参数信息的变量地址值
```

调用 pthread_join 的进程(或线程)将进入等待状态，直到第一个参数为ID的线程终止为止
```
#include<pthread.h>
int pthread_join(pthread_t p_id, void** status);
//成功时返回0，失败时返回-1
//	thread：该参数值ID的线程终止后才会从该函数返回
//	status：保存线程的main函数返回值的指针变量地址值
```
## 可在临界区内调用的函数----临界区 (Critical Section)
根据临界区是否引起问题，函数可以分为2类：
- 线程安全函数 (Thread-safe function)
- 非线程安全函数 (Thread-unsafe function)

gethostbyname 是非线程安全函数， gethostbyname_r 是线程安全函数。
线程安全函数的名称通常为 **_r**

声明头文件前定义 **_REENTRANT** 宏，可以自定将gethostbyname函数调用改为 gethostbyname_r
```
$ gcc -D_REENTRANT mythread.c -o mythread -lpthread
```

## 工作(Worker)线程模型


3. 线程存在的问题和临界区
=========================

## 多个线程访问同一变量

## 临界区位置
函数内同时运行多个线程时引起问题的多条语句构成的代码块

4. 线程同步
===========

线程同步用于解决线程访问顺序引发的问题，需要同步的情况可以从如下两方面考虑：
- 同时访问同一内存空间时发生的情况
- 需要指定访问同一内存空间时线程的执行顺序的情况

## 互斥量
```
#include<pthread.h>
int pthread_mutex_init(pthread_mutex_t* mutex, const pthread_mutexattr_t* attr);
int pthread_mutex_destroy(pthread_mutex_t* mutex);
//成功时返回0，失败时返回其他值
```
- mutex:保存互斥量的变量地址值，销毁时传递需要销毁的互斥量地址值
- attr:传递创建互斥量属性，没有特别需要指定的属性时传递NULL
```
#include<pthread.h>
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```

## 信号量
```
#include<semaphore.h>
int sem_init(sem_t* sem, int pshared, unsigned int value);
int sem_destroy(sem_t* sem);
//成功时返回0，失败时返回其他值
```
- sem: 保存信号量的变量地址值
- pshared:传递其他值时，创建多个进程共享的信号量，传递0时，创建只允许一个进程使用的信号量
- value:指定初始值

```
#include<semaphore.h>
int sem_post(sem_t* sem);
int sem_wait(sem_t* sem);
//成功时返回0，失败时返回其他值
```
- sem:传递给sem_post时信号量增加1，传递给sem_wait时信号量减少1

5. 线程的销毁和多线程并发服务器端的实现
=======================================

## 线程销毁的3种方法
- 调用 pthread_join 函数
- 调用 pthread_detach 函数

pthread_join： 不仅会等待线程终止，还回引导线程销毁。问题是，线程终止前，调用该函数的线程将进入阻塞状态

pthread_detach ： 不会引起线程终止或进入阻塞状态，可以通过该函数引导销毁线程创建的内存空间。该线程运行结束后会自动释放所有资源

```
#include<pthread.h>
int pthread_detach(pthread_t thread);
//成功时返回0，失败时返回其他值
```
调用此函数后不能再调用pthread_join,调用该函数的线程不会阻塞，该函数引导线程结束之后销毁线程空间。