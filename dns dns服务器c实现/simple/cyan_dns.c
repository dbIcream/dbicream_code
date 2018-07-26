# include "structs.h"

/* net */

int fd_epoll, ns_count;

// common
unsigned char socket_buf[2048];
char console_buf[2048];

/* 设置成非阻塞模式 */
int set_non_blocking(int fd)
{
	if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK ) == -1) {
		fprintf(stderr, "Set blocking error:%s\n", strerror(errno));
		return -1;
	}
	return 0;
}

int epoll_opt(int fd, int in, int out, int delete, int level)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = 0;
	if (in)
		ev.events |= EPOLLIN;
	if (out)
		ev.events |= EPOLLOUT;
	if (! in && ! out)
		return -1;
	if (! level)
		ev.events |= EPOLLET;
//	ev.events |= EPOLLERR;
	delete = delete ? EPOLL_CTL_DEL : EPOLL_CTL_ADD;
	return epoll_ctl(fd_epoll, delete, fd, &ev);
}

int init_socket(void)
{
//	int opt_val = 1;
	int i, ok, fd;
	fd_epoll = epoll_create(ns_count);
	if (fd_epoll < 0) {
		fprintf(stderr, "epoll_create failed:%s\n", strerror(errno));
		return -1;
	}
	for (fd = i = 0; i < ns_count; i ++) {
		fd = socket(AF_INET, SOCK_DGRAM, 0);	/* UDP */
		if (fd < 0) {
			fprintf(stderr, "create socket failed: %s\n", strerror(errno));
			break;
		}
		if (set_non_blocking(fd)) {
			break;
		}
/*		if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &opt_val, sizeof(opt_val))) {
			fprintf(stderr, "setsockopt SO_REUSEPORT failed: %s\n", strerror(errno));
			break;
		}*/
		if (bind(fd, (struct sockaddr *)&(g_ns[i].my_addr), sizeof(struct sockaddr)) < 0) {
			fprintf(stderr, "bind failed: %s\n", strerror(errno));
			break;
		}
		epoll_opt(fd, 1, 0, 0, 1);
		printf("%s:%u listening ...\n", inet_ntoa(g_ns[i].my_addr.sin_addr), htons(g_ns[i].my_addr.sin_port));
		g_ns[i].fd = fd;
		fd = 0;
	}
	if (fd) {
		close(fd);
		ns_count = i;
	}
	if (0 == ns_count)
		return -1;
	return 0;
}

void recycle_all(void)
{
	int i;
	// socket
	if (fd_epoll > 0)
		close(fd_epoll);
	for (i = 0; i < ns_count; i ++) {
		if (g_ns[i].fd)
			close(g_ns[i].fd);
	}
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

void list_ns()
{
	int i;
	for (i = 0; i < ns_count; i ++)
		printf("%d %s:%u\n", i, inet_ntoa(g_ns[i].my_addr.sin_addr), htons(g_ns[i].my_addr.sin_port));
}

int parse_domain(int index, char *domain)
{
	domain_item_t *w;
	w = g_ns[index].domain_table;
	while(w) {
		if (strcmp(domain, w->domain) == 0) {
			if (0 == w->valid) {
				fprintf(stderr, "find domain %s, but invalid\n", domain);
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
#if 0
	p = (char *)(socket_buf + sizeof(dns_pkt_header));
	while(1) {
		len = (unsigned int)(*(unsigned char *)p);;
		pkt_len += (1 + len);
		if (0 == len)
			break;
		p += (1 +len);
	}
	pkt_len += 4;
	memcpy(socket_buf + pkt_len, no_reocrd, sizeof(no_reocrd));
	pkt_len += sizeof(no_reocrd);
/*	int i;
	printf("len = %u\n", pkt_len);
	for (i = 0; i < pkt_len; i ++){
		printf("0x%02x ", socket_buf[i]);
		if (i % 16 == 15)
			putchar('\n');
	}
	putchar('\n');*/
#endif
	sendto(g_ns[index].fd, socket_buf, pkt_len, 0, (struct sockaddr*)&g_ns[index].your_addr, sizeof(g_ns[index].your_addr));
	printf("send pkt: %u\n", pkt_len);
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
		printf("id = %u\n",	htons(pkt->id));
		if (dns_QR(pkt->flag) || dns_AA(pkt->flag) || dns_opcode(pkt->flag)) { // no query
			printf("QR = %u, opcode = %u, AA = %u\n", dns_QR(pkt->flag), dns_opcode(pkt->flag), dns_AA(pkt->flag));
			error = 1;
			break;
		}
		ques_cnt = htons(pkt->questions_count);
		answer_RRs = htons(pkt->answer_RRs);
		auth_RRs = htons(pkt->auth_RRs);
		addition_RRs = htons(pkt->addition_RRs);
		if (answer_RRs || auth_RRs || 0 == ques_cnt) {
			printf("questions_count = %u, answer_RRs = %u, auth_RRs = %u\n", ques_cnt, answer_RRs, auth_RRs);
			error = 1;
			break;
		}
		p = (char *)(socket_buf + sizeof(dns_pkt_header_t));
		/*for (i = 0; i < ques_cnt; i ++)*/ {
			domain_in = NULL;
			total_len = 0;
			while(1) {
				len = (unsigned int)(*(unsigned char *)p ++);
				if (0 == len)
					break;
				domain_in = xrealloc(domain_in, total_len + len + 2);
				strncpy(domain_in + total_len, p, len);
				total_len += len;
				domain_in[total_len ++] = '.';
				domain_in[total_len] = '\0';
				p += len;
			}
			if (NULL == domain_in) {
				printf("no have domain\n");
				error = 1;
				break;
			}
			printf("domain = %s\n", domain_in);
			type = *((unsigned short *)p);
			type = htons(type);
			p += 2;
			class = *((unsigned short *)p);
			class = htons(class);
			p += 2;
			if (type != 1 || class != 1) {
				printf("type = %u, class = %u\n", type, class);
				error = 1;
				break;
			}
			if (0 == g_ns[index].pause) {
				if (parse_domain(index, domain_in)) {
					printf("unknow domain = %s\n", domain_in);
					error = 1;
					break;
				}
			}
		}
		if (g_ns[index].pause) {
			printf("ns[%d] is pause\n", index);
			error = 1;
			break;
		}
	} while(0);
	if (0 == error || g_ns[index].error_ack) {
		dns_resp(index);
	} else {
		fprintf(stderr, "nack\n");
	}
	if (domain_in)
		free(domain_in);
}

int GetNsIndex(int fd)
{
	int i;
	for(i = 0; i < ns_count; i ++) {
		if (fd == g_ns[i].fd)
			break;
	}
	return i;
}

int loop()
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
		fds = epoll_wait(fd_epoll, &ev, 1, -1);
		if(fds < 0) {
			fprintf(stderr, "epoll_wait failed:%s\n", strerror(errno));
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
				if (fds < 0 || fds >= ns_count) {
					fprintf(stderr, "Invalid parameters, nack 0 ~ %d\n", ns_count);
				} else {
					g_ns[fds].pause = 1;
					fprintf(stderr, "ns[%d] is pause\n", fds);
				}
			}
			else if (! memcmp(console_buf, "ack ", 4)) {
				fds = atoi(console_buf + 4);
				if (fds < 0 || fds >= ns_count) {
					fprintf(stderr, "Invalid parameters, nack 0 ~ %d\n", ns_count);
				} else {
					g_ns[fds].pause = 0;
					fprintf(stderr, "ns[%d] is resume\n", fds);
				}
			}
			else if (console_buf[0] != '\r' && console_buf[0] != '\n') {
				fprintf(stderr, "unknow command %s", console_buf);
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
						   inet_ntoa(g_ns[i].my_addr.sin_addr), htons(g_ns[i].my_addr.sin_port));
			memcpy(&g_ns[i].your_addr, &client_addr, sizeof(client_addr));
			DoDNS(i);
		}
	}
	return 0;
}

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
		if (0 == state) {{	/* 开关 */
			if (memcmp(p, "[NAMESERVER]", 12) == 0) {
				state = 1;
				g_ns = (ns_t *)xrealloc(g_ns, sizeof(ns_t) * (ns_count + 1));
				memset(&g_ns[ns_count], 0, sizeof(ns_t));
				g_ns[ns_count].error_ack = 1;
				g_ns[ns_count].my_addr.sin_port = htons(DEFAULT_LOCAL_PORT);
				g_ns[ns_count].pause = 0;
				ns_count ++;
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
					memcpy(&g_ns[ns_count - 1].my_addr.sin_addr.s_addr, &ip_addr, sizeof(ip_addr));
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
					g_ns[ns_count - 1].my_addr.sin_port = htons(port);
				}
			} else if (! memcmp(p, "ack=", 4)) {
				p += 4;
				tmp = atoi(token);
				if (tmp != 0)
					tmp = 1;
				g_ns[ns_count - 1].error_ack = tmp;
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
					head = &g_ns[ns_count - 1].domain_table;
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

int main(int argc, char **argv)
{
	char *file_name = "mydns.conf";
	int ret = 0;
	if (argc > 1) {
		file_name = argv[1];
	}

	do {
		read_conf_file(file_name);	/* 读配置文件里面的dns服务器 */
		if (0 == ns_count) {
			g_ns = (ns_t *)xcalloc(1, sizeof(ns_t));
			ns_count = 1;
			g_ns[0].my_addr.sin_family = AF_INET;
			g_ns[0].my_addr.sin_addr.s_addr = 0x100007f;
			g_ns[0].my_addr.sin_port = htons(DEFAULT_LOCAL_PORT);
		}
		if (init_socket()) {
			ret = -1;
			break;
		}
		ret = loop();
	} while(0);
	recycle_all();
	return ret;
}
