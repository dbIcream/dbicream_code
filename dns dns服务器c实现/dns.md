<!-- TOC -->

- [dns服务器](#dns服务器)
    - [什么是DNS](#什么是dns)
    - [常用查询模式](#常用查询模式)
    - [DNS查询与通讯原理](#dns查询与通讯原理)
        - [查询模式-递归式](#查询模式-递归式)
        - [查询模式-迭代式](#查询模式-迭代式)
    - [DNS协议](#dns协议)
        - [参考链接](#参考链接)
        - [DNS协议报文格式-报头](#dns协议报文格式-报头)
        - [DNS协议报文格式-查询问题区域](#dns协议报文格式-查询问题区域)
        - [DNS协议报文格式-资源记录区域](#dns协议报文格式-资源记录区域)

<!-- /TOC -->
# dns服务器

## 什么是DNS

- DNS（Domain Name System，域名系统），万维网上作为域名和IP地址相互映射的一个分布式数据库，能够使用户更方便的访问互联网，而不用去记住能够被机器直接读取的IP数串。通过域名，最终得到该域名对应的IP地址的过程叫做域名解析（或主机名解析）。

- DNS协议运行在UDP协议之上，使用端口号53。

## 常用查询模式

- nslookup, 显示dns服务器的ip； 然后输入域名进行查询，如果DNS服务正常，就能够正常返回ip

## DNS查询与通讯原理

DNS分为Client和Server，Client扮演发问的角色，也就是问Server一个Domain Name，而Server必须要回答此Domain Name的真正IP地址。而当地的DNS先会查自己的资料库。如果自己的资料库没有，则会往该DNS上所设的DNS服务器询问，依此得到答案之后，将收到的答案存起来，并回答客户。  

### 查询模式-递归式

递归式(Recursive):DNS客户端向DNS Server的查询模式，这种方式是将要查询的封包送出去问，就等待正确名称的正确响应，这种方式只处理响应回来的封包是否是正确响应或是说是找不到该名称的错误讯息。  

### 查询模式-迭代式

迭代式(Iterative):DNS Server间的查询模式，由Client端或是DNS Server上所发出去问，这种方式送封包出去问，所响应回来的资料不一定是最后正确的名称位置，但也不是如上所说的响应回来是错误讯息，他响应回来的是部分信息，告诉你所查询域名中的下一级域的域名服务器的地址信息，然后再到此域名服务器上去查询所要解析的名称，反复动作直到找到最终信息。  

## DNS协议

### 参考链接

- DNS协议详解及报文格式分析: <https://blog.csdn.net/tianxuhong/article/details/74922454>
- DNS协议学习与实现: <https://www.cnblogs.com/dongkuo/p/6714071.html>

### DNS协议报文格式-报头

- 头部报文

|         协议区域-2字节         |         协议区域-2字节          |
| ------------------------------ | ------------------------------- |
| Transaction(会话标识)          | Flags(标志)                     |
| Questions(问题数)              | Answer RRs(回答 资源记录数)     |
| Authority RRs(授权 资源记录数) | Additional RRs(附加 资源记录数) |

```c
struct dns_pkt_header_s {   /* 2+2+2*4=12字节 */
    unsigned short id;  /* 会话标识ID */
    unsigned short flag;            /* 标志位 */
    unsigned short questions_count; /* 请求数 */
    unsigned short answer_RRs;      /* 回答 资源记录数 */
    unsigned short auth_nameserers; /* 授权 资源记录数 */
    unsigned short addition_RRs;    /* 附加 资源记录数 */
};
```

- flags标志位

```c
struct flag_s {
    unsigned short rcode:4; /* 返回码: rcode_return_type */
    unsigned short zero:3;  /* 预留位 */
    unsigned short RA:1;    /* 是否支持递归查询 */
    unsigned short RD:1;    /* 期望服务器递归查询，服务器不一定支持递归查询 */
    unsigned short TC:1;    /* 消息是否因为传输大小限制而被截断 */
    unsigned short AA:1;    /* 是否来自权威应答 */
    unsigned short opcode:4;    /* 指示请求类型：opcode_type */
    unsigned short QR:1;    /* 指示该消息是请求还是响应 */
} flag;
```

### DNS协议报文格式-查询问题区域

|        可变长区域         |       含义        |
| ------------------------- | ----------------- |
| Queries                   | 查询问题区域      |
| Answers                   | 回答 资源记录区域 |
| Authoritative nameservers | 授权 资源记录区域 |
| Additional recoreds       | 附加 资源记录区域 |

|  字段  |                    含义                     |
| ------ | ------------------------------------------- |
| QNAME  | 查询的主机名，长度标签+长度标签，以0x00结束 |
| QTYPE  | 2个字节，表示RR的类型                       |
| QCLASS | 2个字节，表示RR的分类                       |

### DNS协议报文格式-资源记录区域

|        可变长区域         |       含义        |
| ------------------------- | ----------------- |
| Queries                   | 查询问题区域      |
| Answers                   | 回答 资源记录区域 |
| Authoritative nameservers | 授权 资源记录区域 |
| Additional recoreds       | 附加 资源记录区域 |

|   字段   |       含义        |
| -------- | ----------------- |
| NAME     | 域名              |
| TYPE     | 类型              |
| CLASS    | 类                |
| TTL      | 生存时间          |
| RDLENGTH | RDATA所占的字节数 |
| RDATA    | 数据              |

- NAME和RDATA表示的含义根据TYPE的取值不同而不同
- TYPE共16种

| TYPE  |                value-meaning                |
| ----- | ------------------------------------------- |
| A     | 1  由域名获得的IPV4地址                     |
| NS    | 2  查询域名服务器                           |
| MD    | 3  a mail destination (Obsolete - use MX)   |
| MF    | 4  a mail forwarder (Obsolete - use MX)     |
| CNAME | 5  the canonical name for an alias          |
| SOA   | 6  开始授权y                                |
| MB    | 7  a mailbox domain name (EXPERIMENTAL)     |
| MG    | 8  a mail group member (EXPERIMENTAL)       |
| MR    | 9  a mail rename domain name (EXPERIMENTAL) |
| NULL  | 10 a null RR (EXPERIMENTAL)                 |
| WKS   | 11 熟知服务                                 |
| PTR   | 12 把ip地址转换成域名                       |
| HINFO | 13 主机信息 host information                |
| MINFO | 14 mailbox or mail list information         |
| MX    | 15 邮件交换 mail exchange                   |
| TXT   | 16 text strings                             |
| AAAA  | 28 由域名获得的IPV6地址                     |
| AXFR  | 252    传送整个区的请求                     |
| ANY   | 255     对所有记录的请求                    |
