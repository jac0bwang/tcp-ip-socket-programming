1. 基于IO 复用的服务器端
========================

## 多进程服务器端的缺点和解决方法
- 进程增多，数据交换变的复杂
- IO 复用就是解决该问题的一种方法 （不能过于依赖该模型）

2. 理解 select 函数并实现服务器端
=================================
select 是具有代表性的实现复用服务器端方法

## select 函数的功能和调用顺序
使用 select 函数可以同时监视多个文件描述符集，监视项目如下：
- 是否存在套接字接收数据
- 无需阻塞传输数据的套接字有哪些
- 哪些套接字发生了异常
监视项称为 “事件” (event)

select 函数的调用方法和顺序
步骤一 ：
- 设置文件描述符
- 指定监视范围
- 设置超时
步骤二：
- 调用 select 函数
步骤三：
- 查看调用结果

## 设置文件描述符
- `FD_ZERO(fd_set* fdset)`: 将fdset变量的所有位初始化位0
- `FD_SET(int fd, fd_set* fdset)`: 向fdset变量中注册文件描述符fd
- `FD_CLR(int fd, fd_set* fdset)`: 清除fdset变量中的文件描述符fd
- `FD_ISSET(int fd, fd_set* fdset)`: fdset变量中是否存在fd文件描述符

## 设置监视范围及超时
```
#include<sys/select.h>
#include<sys/time.h>

int select(int maxfd, fd_set* readset, 
            fd_set* writeset,fd_set* exceptset, 
            const struct timeval* timeout
            );
//失败时返回-1，超时返回0，成功时返回发生事件的文件描述符数量

struct timeval
{
    long tv_sec;
    long tv_usec;
}
```
- maxfd: 监视的文件描述符数量（最大的文件描述符+1）
- readset: 将关注“是否存在待读取数据”的文件描述符存放在readset变量中
- writeset: 将关注”是否可写“的文件描述符存放在writeset变量中
- exceptset: 将关注”是否有异常“的文件描述符放在exceptset变量中
-timeout: 为了防止调用select函数后陷入无限阻塞状态，可以传递超时信息
