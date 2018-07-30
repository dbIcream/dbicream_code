#include "cyan_dns.h"


void read_conf_file(char *file_name)
{
	int state;  // 0:none; 1:ns
	int line_no, tmp;
	unsigned short port;
	FILE *fp;
	char *buf, *p, *token;
	domain_item_t ** head, *item;
	struct in_addr ip_addr;
    ns_t *ns = g_config.ns_server.ns;

	fp = fopen(file_name, "rt");	/* 文档模式读取文件 */ 
	if (NULL == fp) {
		debug_log_printf("open %s failed: %s\n", file_name, strerror(errno));
		exit(1);
	}

	state = 0;
	line_no = 0;
	buf = (char *) xmalloc(4096);
	while(fgets(buf, 4096, fp) != NULL) {
		p = buf;
		line_no++;

		/* 跳过空格 */
		while(*p && isspace(*p)) {
			p++;
		}

		/* 路过注释和空行 */
		if ('\0' == *p || '#' == *p) {
			continue;
		}

		/* 配置结束 */
		if (memcmp(p, "[END]", 5) == 0) {
			state = 0;
			continue;
		}

		/* 识别分频道开始位置 */
		if (0 == state) {	/* 开关 */
			if (memcmp(p, "[NAMESERVER]", 12) == 0) {
				state = 1;
				ns = (ns_t *)xrealloc(ns, sizeof(ns_t) * (g_config.ns_server.ns_count + 1));
				memset(&ns[g_config.ns_server.ns_count], 0, sizeof(ns_t));
				ns[g_config.ns_server.ns_count].error_ack = 1;
				ns[g_config.ns_server.ns_count].my_addr.sin_port = htons(DEFAULT_LOCAL_PORT);
				ns[g_config.ns_server.ns_count].pause = 0;
				g_config.ns_server.ns_count++;
			} else {    /* 跳过无效行 */
				debug_log_printf("ignore conf line %d:%s\n", line_no, p);
			}
		} else if (1 == state) {    /* 分频道内容解析 */
			if (!memcmp(p, "ip=", 3)) {
				p += 3;
				token = p;
				while (*token && !isspace(*token)) {
					token++;
				}

				/* 截断后续的内容，获取ip内容 */
				*token = 0;
				if (inet_pton(AF_INET, p, &ip_addr) == 1) {
					memcpy(&ns[g_config.ns_server.ns_count - 1].my_addr.sin_addr.s_addr, &ip_addr, sizeof(ip_addr));
				} else {
					debug_log_printf("line %d, %s is not ip\n", p);
				}
			} else if (! memcmp(p, "port=", 5)) {
				p += 5;
				token = p;
				while (*token && !isspace(*token)) {
					token++;
				}
				/* 截断后续的内容，获取port内容 */
				*token = 0;
				tmp = atoi(p);
				if (tmp < 0 || tmp >= 65536) {
					debug_log_printf("line %d, %s is not valid port number\n", token);
				} else {
					port = (unsigned short)tmp;
					ns[g_config.ns_server.ns_count - 1].my_addr.sin_port = htons(port);
				}
			} else if (! memcmp(p, "ack=", 4)) {
				p += 4;
				token = p;
				while (*token && !isspace(*token)) {
					token++;
				}
				/* 截断后续的内容，获取ack内容 */
				*token = 0;
				tmp = atoi(p);
				if (tmp != 0) {
					tmp = 1;
				}
				ns[g_config.ns_server.ns_count - 1].error_ack = tmp;
			} else if (! memcmp(p, "domain=", 7)) {
				p += 7;
				token = p;
				while (*token && !isspace(*token)) {
					token++;
				}
				/* 截断后续的内容，获取domain内容 */
				*token = 0;
				if (*p) {
					tmp = 1;
					item = (domain_item_t *)xcalloc(1, sizeof(domain_item_t));
					item->domain = xstrdup(p);
					item->valid = 1;
					head = &ns[g_config.ns_server.ns_count - 1].domain_table;
					while (*head)
						head = &(*head)->next;
					*head = item;
				}
			} else if (! memcmp(p, "domain_ip=", 10)) {
				p += 10;
				token = p;
				while (*token && !isspace(*token)) {
					token++;
				}
				/* 截断后续的内容，获取domain_ip内容 */
				*token = 0;
				ns[g_config.ns_server.ns_count - 1].domain_ip = xstrdup(p);
			} else {
				debug_log_printf("ignore conf line %d:%s\n", line_no, p);
			}
		}
	}

    g_config.ns_server.ns = ns;

	free(buf);
	fclose(fp);
}

void list_ns()
{
	int i;
    ns_t *ns = g_config.ns_server.ns;
    int ns_count = g_config.ns_server.ns_count;
    domain_item_t *head;


    if (ns != NULL && ns_count > 0) {
        for (i = 0; i < ns_count; i++) {
            head = ns[i].domain_table;

            /* ip + port*/
            debug_log_printf("list_ns: %d %s:%u\n", i, inet_ntoa(ns[i].my_addr.sin_addr), htons(ns[i].my_addr.sin_port));

            /* domain table */
            while(head != NULL) {
                debug_log_printf("list_ns: domain: %s\n", head->domain);
                head = head->next;
            }
            debug_log_printf("list_ns: domain_ip: %s\n", ns[i].domain_ip);
        }	
    }
	
}

/* 关闭打开的文件描述符 */
void recycle_all(void)
{
	int i;

	if (g_fd_epoll > 0) {
		close(g_fd_epoll);
	}

	for (i = 0; i < g_config.ns_server.ns_count; i ++) {
		if (g_config.ns_server.ns[i].fd) {
			close(g_config.ns_server.ns[i].fd);
		}	
	}
}
