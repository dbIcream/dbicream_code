<!-- TOC -->

- [websocket的服务器搭建](#websocket的服务器搭建)
    - [发送websocket请求](#发送websocket请求)

<!-- /TOC -->

# websocket的服务器搭建

```shell
# IP 端口 响应序号（reply_n）  响应101后等待的时间  响应101前等待的时间  发送‘hi’的个数  建立连接后是否立即退出  响应101后是否立即退出
./websock 127.0.0.1 9100 3 0 0 6 n n
```

## 发送websocket请求

```http
GET ws://a.aaa.com/ HTTP/1.1
Host: a.aaa.com
Sec-WebSocket-Key: sBcNTmACQ0ui3zHHn4T5aA==
Sec-WebSocket-Protocol: chat, superchat
Sec-WebSocket-Version: 13
Upgrade: websocket
Connection: Upgrade
Pragma: no-cache
```
