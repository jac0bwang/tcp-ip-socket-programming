# 分配给套接字的IP地址与端口号 （IP 由网络地址和主机地址组成）
## 网络地址
- IPv4:4字节地址
- IPv6:16字节地址

- A类网络地址首字节范围：0~127     (1字节)
- B类网络地址首字节范围：128~191   (2字节)
- C类网络地址首字节范围：192~223   (3字节)
- D类 被用于多播

## 端口号
- 端口号用于表示数据去向那个应用
- TCP/UDP套接字不会公用端口号
- TCP使用的端口号9190，UDP也可以使用9190

# 地址信息的表示
## 表示IPv4地址的结构体
```
struct sockaddr_in
{
    sa_family_t sin_family; //地址族
    uint16_t sin_port;      //16位端口号
    struct in_addr sin_addr;//32位IP地址
    char zero[8];           //无含义，只是为了和sockaddr结构保持一致，必须填充0
}

struct in_addr
{
    in_addr_t s_addr;   //32位IP地址
}

struct sockaddr
{
    sa_family_t sin_family;
    char sa_data[14];
}
```

# 网络字节序列与地址转换
## 字节序与网络字节序列
- 大端序（Big Endian）：低位地址存储高位字节
- 小端序(Little Endian)：高位地址存储高位字节
- 网络字节序列(Network Byte Order)：统一为大端序

## 字节序列转换(Endian Conversions)
- 数据传输的过程中字节序是自动转换的，除了在填充 sockaddr_in 的时候，其他无需考虑字节序问题
```
unsigned short htons(unsigned short);    //主机字节序->网络字节序
unsigned short ntohs(unsigned short);    //网络字节序列->主机字节序列
unsigned long htonl(unsigned long);      
unsigned long ntohl(unsigned long);
// h --- host 
// n --- network
// s --- short (2byte)
// l --- long (4byte)
```

# 网络地址的初始化与分配 （bind）
## 将字符串信息转换为网络字节序列的整数型
```
#include<arpa/inet.h>

in_addr_t inet_addr(const char* string);
//成功时返回32位大端序列整型数值，失败时返回INADDR_NONE
//可以验证无效IP地址

int inet_aton(const char* string, struct in_addr* addr);
//成功时返回true，失败时返回false
// 和inet_addr功能完全相同，只是利用了 in_addr 结构体，其实用频率更高
// 将转换结果放进 addr

char* inet_ntoa(struct in_addr addr);
// 把网络字节序列的整数型转换为字符串信息

// n --- network
// a --- char*
```

## 网络地址初始化
```
struct sockaddr_in addr;
char *srev_ip = "211.217.168.13";  
char * serv_port = "9190";
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr(srev_ip);
addr.sin_port = htons(atoi(serv_port));
// atoi 字符串 转为 整数
```

## INADDR_ANY
- INADDR_ANY 可以自动获取运行服务器端的IP地址
- 服务器端优先考虑这种方式
- 客户端不会使用
```
struct sockaddr_in addr;
char *srev_ip = "211.217.168.13";  
char * serv_port = "9190";
memset(&addr, 0, sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_addr.s_addr = inet_addr(srev_ip);
addr.sin_port = htons(atoi(serv_port));
```

## sockaddr_in
- 服务器端设置该结构体后使用 bind 函数
- 客户端设置该结构体后使用 connect 函数