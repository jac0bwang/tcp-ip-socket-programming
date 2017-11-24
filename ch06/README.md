1. 理解UDP
==========

## 套接字的特点
流控制是区分UDP和TCP最重要的标志

收发数据的过程中为保证可靠性而增加的流控制机制

## UDP内部工作原理
UDP最重要的作用是根据端口号将传到追的数据包交付给最终的UDP套接字

## UDP高效使用(音频/视频)
UDP并非每次都快于TCP，每次交换的数据量越大，TCP的传输速率越接近UDP的传输速率；TCP比UDP慢通常有以下两点原因：
- 如果收发的数据量小但需要频繁建立连接时，UDP比TCP更快
- 建立连接和连接断开的连接设置和清除过程

2. 基于UDP的服务器端/客户端
===========================
- UDP中的服务器端和客户端没有连接(不许要**listen, accept**函数)
- UDP中的服务器端和客户端均只需1个套接字

## 基于UDP的数据I/O函数
```
#include<sys/socket.h>
ssize_t sendto(int sock, void* buff, size_t nbytes, int flags,struct sockaddr* to, socklen_t addrlen);
//成功时返回发送的字节数，失败时返回-1

#include<sys/socket.h>
ssize_t recvfrom(int sock, void* buff, size_t nbytes, int flags, struct sockaddr* from socklen_t addrlen);
//成功时返回接收的字节数，失败时返回-1
```
## UDP客户端套接字的地址分配
调用sendto 函数时自动分配IP和端口号， bind函数不分 TCP/UDP

3. UDP的数据传输特性和调用connect函数
=====================================
TCP数据传输不存在数据边界，UDP存在

##存在数据边界的UDP套接字
> TCP数据传输中不存在边界，表示**数据传输过程中调用I/O函数的次数不具有任何意义**
> UDP具有数据边界的协议，传输中调用I/O函数的次数非常重要，输入和输出函数调用次数应一致

## 已连接UDP套接字与未连接UDP套接字

通过sendto函数传输数据会经过以下三个步骤：  
- 向UDP套接字中注册目标IP和端口信息
- 传输数据
- 清除UDP套接字中注册的目标IP和端口信息

每次调用 sendto都重复上述3个步骤，要是与同一主机通信时，将UDP变成连接套接字会提高效率

## 创建已连接UDP套接字
可以通过以下方式创建已连接UDP套接字，可以避免频繁的向UDP套接字中注册目标IP和端口信息。
```
int sock = socket(PF_INET, SOCK_DGRAM, 0);
struct sockaddr_in addr;
memset(&addr, 0, sizeof(addr));
addr.sin_family = ...
addr.sin_addr.s_addr = ...
addr.sin_port = ...
connect(sock, (struct sockaddr*)&addr, sizeof(addr));
```
以上创建的套接字方式与创建TCP客户端套接字的方式并无二致，但是此处的connect函数并没有与对方的UDP套接字连接，
这里只是向sock中注册了目标IP和端口信息，之后收发数据就可以使用`write() read()`函数来进行收发数据。