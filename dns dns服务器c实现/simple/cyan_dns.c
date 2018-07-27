#include "cyan_dns.h"

/* socket 接收的buf大小 */
#define	MAX_SOCKET_BUF	2048
unsigned char socket_buf[MAX_SOCKET_BUF];	
char console_buf[MAX_SOCKET_BUF];

/* 设置成非阻塞模式 */
int set_non_blocking(int fd)
{
	if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK ) == -1) {
		debug_log_printf("Set blocking error:%s\n", strerror(errno));
		return -1;
	}
	return 0;
}

/* epoll 操作参数 */
int epoll_opt(int fd, int in, int out, int delete, int level)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = 0;
	if (in) {
        ev.events |= EPOLLIN;
    }
		
	if (out) {
        ev.events |= EPOLLOUT;
    }

	if (! in && ! out) {
        return -1;
    }
		
	if (! level) {
        ev.events |= EPOLLET;
    }

    //	ev.events |= EPOLLERR;
	delete = delete ? EPOLL_CTL_DEL : EPOLL_CTL_ADD;
	return epoll_ctl(g_fd_epoll, delete, fd, &ev);
}

/* 初始化socket连接 */
int init_socket(void)
{
//	int opt_val = 1;
	int i, ok, fd;
	g_fd_epoll = epoll_create(g_config.ns_server.ns_count);	/* 生成epool专用的fd */
	if (g_fd_epoll < 0) {
		debug_log_printf("epoll_create failed:%s\n", strerror(errno));
		return -1;
	}

	fd = 0;
	for (i = 0; i < g_config.ns_server.ns_count; i ++) {
		fd = socket(AF_INET, SOCK_DGRAM, 0);	/* UDP */
		if (fd < 0) {
			debug_log_printf("create socket failed: %s\n", strerror(errno));
			return -1;
		}

		/* 设置新的套接字为非阻塞模式 */
		if (set_non_blocking(fd)) {
			close(fd);
			return -1;
		}

		/* 设置端口复用 */
#if 0
		if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt_val, sizeof(opt_val))) {
			debug_log_printf("setsockopt SO_REUSEPORT failed: %s\n", strerror(errno));
			break;
		}
#endif
		/* socket bind */
		if (bind(fd, (struct sockaddr *)&(g_config.ns_server.ns[i].my_addr), sizeof(struct sockaddr)) < 0) {
			debug_log_printf("bind failed: %s\n", strerror(errno));
			close(fd);
			return -1;
		}

		/* 将新的socket添加到监听的epoll中 */
		epoll_opt(fd, 1, 0, 0, 1);	/* in = 1, out = 0, delete = 0, leverl = 1*/
		debug_log_printf("%s:%u listening ...\n", inet_ntoa(g_config.ns_server.ns[i].my_addr.sin_addr), htons(g_config.ns_server.ns[i].my_addr.sin_port));

		g_config.ns_server.ns[i].fd = fd;
		fd = 0;
	}

	/* 将ns个数添加到全局变量中 */
	if (fd) {
		close(fd);
	}

	if (0 == g_config.ns_server.ns_count) {
		return -1;
	}
	return 0;
}

unsigned int make_uint(unsigned char *data_in)
{
	unsigned int ret;
	ret = (unsigned int)data_in[0];
	ret <<= 8;
	ret += (unsigned int)data_in[1];
	ret <<= 8;
	ret += (unsigned int)data_in[2];
	ret <<= 8;
	ret += (unsigned int)data_in[3];
	return ret;
}

void uint_to_buf(unsigned int ul_value, unsigned char *data_out)
{
	data_out[3] = (unsigned char)(ul_value & 0xFF);
	ul_value >>= 8;
	data_out[2] = (unsigned char)(ul_value & 0xFF);
	ul_value >>= 8;
	data_out[1] = (unsigned char)(ul_value & 0xFF);
	ul_value >>= 8;
	data_out[0] = (unsigned char)(ul_value & 0xFF);
}

int parse_domain(int index, char *domain)
{
	domain_item_t *w;
	w = g_config.ns_server.ns[index].domain_table;
	while(w) {
		if (strcmp(domain, w->domain) == 0) {
			if (0 == w->valid) {
				debug_log_printf("find domain %s, but invalid\n", domain);
				break;
			}
			return 0;
		}
		w = w->next;
	}
	return -1;
}

char no_reocrd[]={0xc0, 0x0c, 0, 0x06, 0, 0x01, 0, 0, 0x03, 0x83, 0, 0x3d, 0x01, 0x61, 0x0c, 0x67,
				  0x74, 0x6c, 0x64, 0x2d, 0x73, 0x65, 0x72, 0x76, 0x65, 0x72, 0x73, 0x03, 0x6e, 0x65, 0x74, 0,
				  0x05, 0x6e, 0x73, 0x74, 0x6c, 0x64, 0x0c, 0x76, 0x65, 0x72, 0x69, 0x73, 0x69, 0x67, 0x6e, 0x2d,
				  0x67, 0x72, 0x73, 0xc0, 0x22, 0x5a, 0xf2, 0xbc, 0x61, 0, 0, 0x07, 0x08, 0, 0, 0x03,
				  0x84, 0, 0x09, 0x3a, 0x80, 0, 0x01, 0x51, 0x80};

void dns_resp(int index) {
	char *p;
	unsigned int pkt_len, len;
	dns_pkt_header_t *pkt;
	pkt = (dns_pkt_header_t *)socket_buf;
	s_dns_QR(pkt->flag);
	s_dns_RA(pkt->flag);
	s_dns_rcode(pkt->flag, 3);
	pkt->auth_RRs = htons(1);
	pkt_len = sizeof(dns_pkt_header_t);
#if 1
	p = (char *)(socket_buf + sizeof(dns_pkt_header_t));
	while(1) {
		len = (unsigned int)(*(unsigned char *)p);;
		pkt_len += (1 + len);
		if (0 == len) {
			break;
		}
		p += (1 +len);
	}
	pkt_len += 4;
	/* 直接添加无记录的应答 */
	memcpy(socket_buf + pkt_len, no_reocrd, sizeof(no_reocrd));
	pkt_len += sizeof(no_reocrd);
/*	int i;
	debug_log_printf("len = %u\n", pkt_len);
	for (i = 0; i < pkt_len; i ++){
		debug_log_printf("0x%02x ", socket_buf[i]);
		if (i % 16 == 15)
			putchar('\n');
	}
	putchar('\n');*/
#endif
	sendto(g_config.ns_server.ns[index].fd, socket_buf, pkt_len, 0, (struct sockaddr*)&g_config.ns_server.ns[index].your_addr, sizeof(g_config.ns_server.ns[index].your_addr));
	debug_log_printf("send pkt: %u\n", pkt_len);
}

void DoDNS(int index)
{
	unsigned int i, total_len, len, ques_cnt, answer_RRs, auth_RRs, addition_RRs;
	int error;
	char *p;                                 
	char * domain_in;
	unsigned short type, class;
	dns_pkt_header_t *pkt;
	do {
		domain_in = NULL;
		error = 0;
		pkt = (dns_pkt_header_t *)socket_buf;
		debug_log_printf("id = %u\n",	htons(pkt->id));
		if (dns_QR(pkt->flag) || dns_AA(pkt->flag) || dns_opcode(pkt->flag)) { // no query
			debug_log_printf("QR = %u, opcode = %u, AA = %u\n", dns_QR(pkt->flag), dns_opcode(pkt->flag), dns_AA(pkt->flag));
			error = 1;
			break;
		}
		ques_cnt = htons(pkt->questions_count);
		answer_RRs = htons(pkt->answer_RRs);
		auth_RRs = htons(pkt->auth_RRs);
		addition_RRs = htons(pkt->addition_RRs);
		if (answer_RRs || auth_RRs || 0 == ques_cnt) {
			debug_log_printf("questions_count = %u, answer_RRs = %u, auth_RRs = %u\n", ques_cnt, answer_RRs, auth_RRs);
			error = 1;
			break;
		}
		p = (char *)(socket_buf + sizeof(dns_pkt_header_t));
		for (i = 0; i < ques_cnt; i ++) {
			domain_in = NULL;
			total_len = 0;
			while(1) {
				len = (unsigned int)(*(unsigned char *)p ++);
				if (0 == len)
					break;
				domain_in = (char *) xrealloc(domain_in, total_len + len + 2);
				strncpy(domain_in + total_len, p, len);
				total_len += len;
				domain_in[total_len++] = '.';
				domain_in[total_len] = '\0';
				p += len;
			}
			if (NULL == domain_in) {
				debug_log_printf("no have domain\n");
				error = 1;
				break;
			}
			domain_in[total_len - 1] = '\0';
			debug_log_printf("domain = %s\n", domain_in);
			type = *((unsigned short *)p);
			type = htons(type);
			p += 2;
			class = *((unsigned short *)p);
			class = htons(class);
			p += 2;
			if (type != 1 || class != 1) {
				debug_log_printf("type = %u, class = %u\n", type, class);
				error = 1;
				break;
			}
			if (0 == g_config.ns_server.ns[index].pause) {
				if (parse_domain(index, domain_in) == -1) {
					debug_log_printf("unknow domain = %s\n", domain_in);
					error = 1;
					break;
				}
			}
		}
		if (g_config.ns_server.ns[index].pause) {
			debug_log_printf("ns[%d] is pause\n", index);
			error = 1;
			break;
		}
	} while(0);
	if (0 == error || g_config.ns_server.ns[index].error_ack) {
		dns_resp(index);
	} else {
		debug_log_printf("nack\n");
	}
	if (domain_in) {
		free(domain_in);
	}
}

int GetNsIndex(int fd)
{
	int i;
	for(i = 0; i < g_config.ns_server.ns_count; i ++) {
		if (fd == g_config.ns_server.ns[i].fd)
			break;
	}
	return i;
}

int epoll_loop()
{
	int i, fds, bytes, b_loop;
	struct tm *p_time;
	socklen_t len;
	struct timeval current_time;
	struct sockaddr_in client_addr;
	struct epoll_event ev;
	// add stdin
	set_non_blocking(STDIN_FILENO);
	epoll_opt(STDIN_FILENO, 1, 0, 0, 0);
	b_loop = 1;
	while(b_loop) {
		fds = epoll_wait(g_fd_epoll, &ev, 1, -1);
		if(fds < 0) {
			debug_log_printf("epoll_wait failed:%s\n", strerror(errno));
			return -1;
		}
		if (0 == fds)
			continue;
		fds = ev.data.fd;
		if (STDIN_FILENO == fds) {
			bytes = read(STDIN_FILENO, console_buf, sizeof(console_buf) - 1);
			console_buf[bytes] = '\0';
			if (! memcmp(console_buf, "exit", 4) || ! memcmp(console_buf, "q", 1)) {
				epoll_opt(STDIN_FILENO, 1, 0, 1, 0);
				b_loop = 0;
			} else if (! memcmp(console_buf, "list", 4)) {
				list_ns();
				sleep(1);
			} else if (! memcmp(console_buf, "nack ", 5)) {
				fds = atoi(console_buf + 5);
				if (fds < 0 || fds >= g_config.ns_server.ns_count) {
					debug_log_printf("Invalid parameters, nack 0 ~ %d\n", g_config.ns_server.ns_count);
				} else {
					g_config.ns_server.ns[fds].pause = 1;
					debug_log_printf("ns[%d] is pause\n", fds);
				}
			}
			else if (! memcmp(console_buf, "ack ", 4)) {
				fds = atoi(console_buf + 4);
				if (fds < 0 || fds >= g_config.ns_server.ns_count) {
					debug_log_printf("Invalid parameters, nack 0 ~ %d\n", g_config.ns_server.ns_count);
				} else {
					g_config.ns_server.ns[fds].pause = 0;
					debug_log_printf("ns[%d] is resume\n", fds);
				}
			}
			else if (console_buf[0] != '\r' && console_buf[0] != '\n') {
				debug_log_printf("unknow command %s", console_buf);
			}
		} else {
			socklen_t addrlen =	sizeof(struct sockaddr_in);
			len = sizeof(client_addr);
			bytes = recvfrom(fds, socket_buf, sizeof(socket_buf), 0, (struct sockaddr*)&client_addr, &len);
			if (bytes <= 0)
				continue;
			gettimeofday(&current_time, NULL);
			p_time = localtime(&(current_time.tv_sec));
			i = GetNsIndex(fds);
			printf("%02u:%02u:%02u.%06u %s:%u > %s:%u\n",
						   p_time->tm_hour, p_time->tm_min, p_time->tm_sec, current_time.tv_usec,
						   inet_ntoa(client_addr.sin_addr), htons(client_addr.sin_port),
						   inet_ntoa(g_config.ns_server.ns[i].my_addr.sin_addr), htons(g_config.ns_server.ns[i].my_addr.sin_port));
			memcpy(&g_config.ns_server.ns[i].your_addr, &client_addr, sizeof(client_addr));
			DoDNS(i);
		}
	}
	return 0;
}