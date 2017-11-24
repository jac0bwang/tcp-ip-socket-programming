# 协议族（Protocol Family）
名称      |协议族
:-------:|:-------:
PF_INET|IPv4互联网协议族
PF_INET6|IPv6互联网协议族
PF_LOCAL|本地通信的UNIX协议族
PF_PACKET|底层套接字的协议族
PF_IPX|IPX Novell协议族

# 套接字类型
## 套接字类型1：面向连接的套接字（SOCK_STREAM)
- 可靠性（传输过程中数据不会消失）
- 按序传输数据
- 传输的数据不存在数据边界

## 套接字类型2：面向消息的套接字（SOCK_DGRAM)
- 强调快速传输而非传输顺序
- 传输的数据可能丢失也可能损毁
- 传输的数据有数据边界
- 限制每次传输数据的大小

## 套接字使用时，可以通过 man 命令查看函数帮助

```
$ man socket
```

## 协议的最终选择通过第三个参数确定
- 大部分情况下第三参数设置为 0
- 同一协议族中存在多个数据传输方式相同的协议，设置不同的值
	```
		int tcp_socket = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
		int udp_socket = socket (PF_INET, SOCK_STREAM, IPPROTO_UDP);
	```
