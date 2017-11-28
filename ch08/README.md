1. 域名系统
===========

## 什么是域名
网络服务器端地址的形式，容易记，容易表述的域名取代IP

## DNS服务器
 DNS （Domain Name System）是对IP地址和域名进行相互转换的系统，
 核心是DNS服务器。所有计算机都记录着默认DNS服务器地址，通过这
 个DNS服务器得到相应域名的IP地址信息。一般服务器域名不会轻易改变，
 但会相对频繁地改变服务器IP地址。可以通过ping www.baidu.com 
 查看对应的IP地址。也可以通过nslookup命令查看计算机中注册的默认DNS服务器地址。


2. IP地址和域名之间的转换
======================

## 利用域名获取IP地址
```
#include<netdb.h>
struct hostent* gethostbyname(const char* hostname);
//成功时返回hostent结构体指针，失败时返回NULL指针
```

```
struct hostent{
    char* h_name;       //官方域名
    char** h_aliases;   //别名列表
    int h_addrtype;     //ip地址类型
    int h_length;       //IP地址长度
    char** h_addr_list; //IP地址列表
}
```

## 利用IP地址获取域名
```
#include<netdb.h>
struct hostent* gethostbyaddr(const char* addr, socklen_t len, int family);
//成功时返回hostent结构体的指针，失败时返回NULL指针
```