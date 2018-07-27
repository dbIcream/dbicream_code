#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "dns.h"

typedef struct domain_item_s {
	char *domain;
    int  valid;
	struct domain_item_s *next;
} domain_item_t;

/* 每个ns服务器的配置数据 */
typedef struct ns_s {
    int fd;
    struct sockaddr_in my_addr;     /* */
    struct sockaddr_in your_addr;   /* */
    int error_ack;  /* 1: if error, ack;  0: if error, nack */
    int pause;
    domain_item_t *domain_table;
    char *domain_ip;
} ns_t;

typedef struct config_s {
    /* ns服务器列表 */
    struct {
        ns_t *ns;
        int ns_count;
    } ns_server;
    
} config_t;

#endif