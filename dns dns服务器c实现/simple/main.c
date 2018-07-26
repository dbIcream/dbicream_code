#include "structs.h"
#include "protos.h"

void read_conf_file(char *file_name)
{
	int state;  // 0:none; 1:ns
	int line_no, tmp;
	unsigned short port;
	FILE *fp;
	char *buf, *p, *token;
	domain_item_t ** head, *item;
	struct in_addr ip_addr;

	fp = fopen(file_name, "rt");	/* 文档模式读取文件 */ 
	if (NULL == fp) {
		fprintf(stderr, "open %s failed: %s\n", file_name, strerror(errno));
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
				g_ns = (ns_t *)xrealloc(g_ns, sizeof(ns_t) * (g_ns_count + 1));
				memset(&g_ns[g_ns_count], 0, sizeof(ns_t));
				g_ns[g_ns_count].error_ack = 1;
				g_ns[g_ns_count].my_addr.sin_port = htons(DEFAULT_LOCAL_PORT);
				g_ns[g_ns_count].pause = 0;
				g_ns_count ++;
			} else {
				/* 跳过无效行 */
				fprintf(stderr, "ignore conf line %d:%s\n", line_no, p);
			}
		} else if (1 == state) {
			/* 分频道内容解析 */
			if (! memcmp(p, "ip=", 3)) {
				p += 3;
				token = p;
				while (*token && !isspace(*token)) {
					token++;
				}

				/* 截断后续的内容，获取ip内容 */
				*token = 0;
				if (inet_pton(AF_INET, p, &ip_addr) == 1) {
					memcpy(&g_ns[g_ns_count - 1].my_addr.sin_addr.s_addr, &ip_addr, sizeof(ip_addr));
				} else {
					fprintf(stderr, "line %d, %s is not ip\n", p);
				}
			} else if (! memcmp(p, "port=", 5)) {
				p += 5;
				tmp = atoi(token);
				if (tmp < 0 || tmp >= 65536) {
					fprintf(stderr, "line %d, %s is not valid port number\n", token);
				} else {
					port = (unsigned short)tmp;
					g_ns[g_ns_count - 1].my_addr.sin_port = htons(port);
				}
			} else if (! memcmp(p, "ack=", 4)) {
				p += 4;
				tmp = atoi(token);
				if (tmp != 0)
					tmp = 1;
				g_ns[g_ns_count - 1].error_ack = tmp;
			} else if (! memcmp(p, "domain=", 7)) {
				p += 7;
				token = p;
				while (*token && !isspace(*token))
					token ++;
				*token ++ = 0;
				if (*p) {
					tmp = 1;
					if (*token) {
						tmp = atoi(token);
						if (tmp != 0)
							tmp = 1;
					}
					item = (domain_item_t *)xcalloc(1, sizeof(domain_item_t));
					item->domain = xstrdup(p);
					item->valid = tmp;
					head = &g_ns[g_ns_count - 1].domain_table;
					while (*head)
						head = &(*head)->next;
					*head = item;
				}
			} else {
				fprintf(stderr, "ignore conf line %d:%s\n", line_no, p);
			}
		}
	}
	free(buf);
	fclose(fp);
}

/* 关闭打开的文件描述符 */
void recycle_all(void)
{
	int i;

	if (g_fd_epoll > 0) {
		close(g_fd_epoll);
	}

	for (i = 0; i < g_ns_count; i ++) {
		if (g_ns[i].fd) {
			close(g_ns[i].fd);
		}	
	}
}

int main(int argc, char **argv)
{
	char *file_name = "mydns.conf";
	int ret = 0;
	if (argc > 1) {
		file_name = argv[1];
	}

	do {
        /* 读配置文件里面的dns服务器 */
		read_conf_file(file_name);

        /* 初始化DNS服务器 */
		if (0 == g_ns_count) {
			g_ns = (ns_t *)xcalloc(1, sizeof(ns_t));
			g_ns_count = 1;
			g_ns[0].my_addr.sin_family = AF_INET;
			g_ns[0].my_addr.sin_addr.s_addr = 0x100007f;
			g_ns[0].my_addr.sin_port = htons(DEFAULT_LOCAL_PORT);
		}
		if (init_socket()) {
			ret = -1;
			break;
		}

        /* 循环监听DNS请求 */
		ret = epoll_loop();
	} while(0);

	recycle_all();
	return ret;
}