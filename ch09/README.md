1. 套接字的可选项和IO缓冲大小
============================
## 套接字的多种可选项

## getsockopt & setsockopt
```
#include<sys/socket.h>
int getsockopt(int sock, int level, int optname,void* optval,socklen_t* optlen);
//成功时返回0，失败时返回-1
```

- sock:套接字文件描述符
- level:要查看的协议层
- optname:要查看的可选项名
- optval:保存查看结果的缓冲地址值
- optlen:第四个参数的缓冲大小

```
#include<sys/socket.h>
int setsockopt(int sock, int level, int optname, void*optval,socklen_t optlen);
//成功时返回0，失败时返回-1
```

## SO_SNDBUF & SO_RCVBUF
```
int sock = socket(PF_INET,SOCK_STREAM,0);
int optval;
socklen_t optlen;
int state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF,(void*)&optval, &optlen);

optval = 1024*3;
optlen = sizeof(optval);
state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF,(void*)&optval,optlen);
```
2. SO_REUSEADDR
===============
## 发生地址分配错误(Binding Error)
理解  **Time-wait** 状态

- 在Time-wait 过程中，相应端口是正在使用的状态
- 客户端的端口号是任意指定的
- 服务器的端口号是固定的，当服务器先发送 FIN 信息时，要经过 3 分钟以后才可以重启服务
- 先传输 FIN 信息的主机都经过 Time-wait 过程

## 地址再分配
设置SO_REUSEADDR 为TRUE， 可将Time-wait 状态下的套接字端口号重新分配给新的套接字

```
int sock = socket(PF_INET, SOCK_STREAM, 0);
int optval = 1;
socklen_t optlen = sizeof(optval);
int state = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,(void*)&optval, optlen);
```

3. TCP_NODELAY
==============

## Nagle 算法
- **Nagle算法** 主要避免网络因为太多的小包（协议头的比例非常之大）而拥塞
- 为了防止数据包过多而发生网络过载， Nagle算法诞生了， 应用与TCP层
- TCP套接字默认使用 Nagle 算法交换数据，因此进行最大限度的缓冲
- 在用户控制的层面上，Nagle算法完全不受用户socket的控制，你只能简单的设置TCP_NODELAY而禁用它
- **CORK算法** 则是为了提高网络的利用率，使得总体上协议头占用的比例尽可能的小

根据传输数据的特性，网络流量未受太大影响时，不使用 **Nagle** 算法要比使用它传输速度快
最典型的是“传输大文件数据”，不使用 **Nagle**，也会在装满输出缓冲时传输数据包，不仅不会增加数据包的数量，可以大大提高传输速度

一般未确定判断数据特性时不应禁止 Nagle 算法

## 禁止 Nagle 算法

把 TCP_NODELAY 设为1 即可禁止 Nagle
```
int sock = socket(PF_INET, SOCK_STREAM, 0);
int optval =1;
int state = setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,(void*)&optval,sizeof(optval));
```