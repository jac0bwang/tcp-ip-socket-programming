1. 多播(基于UDP)
=======
可以同时向多个主机传递数据

## 多播的数据传输方式及流量方面的优点
- 多播服务器端针对特定多播组，只发送1次数据
- 即使只发送1次数据，但改组内的所有客户端都会接受数据
- 多播组数可在IP地址范围内任意增加
- 加入特定组即可接受发往该多播组的数据

## 路由(Routing) 和 TTL (Time to Live, 生存时间), 以及加入组的方法

## 设置生存时间TTL
决定“数据包传递距离”的主要因素
```
#include<sys/socket.h>
#include<arpa/inet.h>

int sock = socket(PF_INET, SOCK_DGRAM, 0);

int timeLive = 64;

setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void*)&timeLive, sizeof(timeLive));
```

> TTL 即Time To Live（生存时间）,决定了数据包传递的距离；TTL用整数表示，数据包每经过一个路由器时TTL就减一，当TTL为0时销毁数据包。

## 加入多播组
```
#include<sys/socket.h>
#include<arpa/inet.h>

int sock = socket(PF_INET, SOCK_DGRAM, 0);

struct ip_mreq joinAddr;
joinAddr.imr_multiaddr.s_addr = "多播组地址信息"
joinAddr.imr_interface.s_addr = "本机地址信息"

setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void*)&joinAddr, sizeof(joinAddr));
```
```
struct ip_mreq
{
    struct in_addr imr_multiaddr;
    struct in_addr imr_interface;
}
```

2. 广播(UDP)
=======
只能向同一网络中的主机传输数据

- 直接广播：直接广播的IP地址除了网络地址外其余的所有主机地址全部设置为1.例如：向网络地址为192.168.8网络地址中所有主机发送数据时，可以向IP地址为192.168.8.255传输数据。

- 本地广播：本地广播中限定IP地址为255.255.255.255.例如：在网络地址为192.168.8的主机向ip地址为255.255.255.255发送数据，数据讲传送到192.168.8网络地址下的所有主机中。

## 更改套接字默认值以允许广播
> 默认生成的套接字会阻止广播，我们需要按照以下方法修改默认值。
```
#include<sys/socket.h>
#include<arpa/inet.h>

int sock = socket(PF_INET, SOCK_DGRAM, 0);

int broadcast = 1;

setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void*)&broadcast, sizeof(broadcast));
```