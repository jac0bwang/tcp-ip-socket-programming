1. HTTP 概要
============

HTTP：Hypertext Transfer Protocol超文本传输协议。超文本是可以根据客户端请求而跳转的结构化信息。

HTTP协议是以超文本传输为目的而设计的应用层协议，是基于TCP/IP实现的协议，实现该协议就相当于实现了Web服务器端。

- HTTP 协议又称为无状态的stateless协议

服务器端响应客户端请求后立即断开，不会维持连接状态。即使同一个客户端再次发送请求，服务器端也无法辨认，而是以同等方式对待。
为了弥补HTTP无法保持连接的缺点，Web编程中通常会使用cookie和session。

- 请求消息(Request Message)的结构
- 响应消息(Respinse Message)的结构

