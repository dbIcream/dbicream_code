#ifndef __CYAN_DNS_H__
#define __CYAN_DNS_H__

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <sys/mman.h>
#include <errno.h>
#include <time.h>

#define DEFAULT_LOCAL_PORT 53   /* 设置默认端口 */

#pragma pack(push)  /* 保存当前的字节对齐方式 */
#pragma pack(1)     /* 将字节对齐设置为1 */

/* RCODE 返回状态 */
typedef enum {
    RCODE_OK = 0,               /* 0 OK */
    RCODE_SERVER_FAILURE = 2,   /* 2 域名出错 */
    RCODE_NAME_ERROR = 3        /* 3 服务器出错 */
} rcode_return_type;

/* 请求类型 */
typedef enum {
    OPCODE_STARDARD = 0,    /* 0 标准查询 */
    OPCODE_REVERSAL,        /* 1 反转查询 */
    OPCODE_SERVER_STATUS,   /* 2 服务器状态查询 */
    OPCODE_NAME_ERROR,      /* 3 域名不存在，权威DNS服务器才有意义 */
    OPCODE_NOT_COMPLETE,    /* 服务器不支持该请求类型 */
    OPCODE_REFUSED,         /* 服务器拒绝执行请求操作 */
    OPCODE_RESERVE          /* 6-15 预留位 */
} opcode_type;

/* 消息类型 */
typedef enum {
    PKT_TYPE_REQ = 0,   /* 0 请求 */
    PKT_TYPE_REP        /* 1 应答 */
} pkt_type;

/* DNS头部的结构体 */
typedef struct dns_pkt_header_s dns_pkt_header_t;
struct dns_pkt_header_s {   /* 2+2+2*4=12字节 */
    unsigned short id;  /* 会话标识ID */
#if 0
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
#endif  
    unsigned short flag;            /* 标志位 */
    unsigned short questions_count; /* 请求数 */
    unsigned short answer_RRs;      /* 回答资源记录数 */
    unsigned short auth_nameserers; /* 授权区域 */
    unsigned short addition_RRs;    /* 附加资源记录数 */
};


#endif