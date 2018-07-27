#include "cyan_dns.h"

/*
gcc -g -o main cyan_dns.c global.c main.c util.c debug.c parse_config.c 
*/

int main(int argc, char **argv)
{
	debug_log_init("debug.log");

	char *file_name = "mydns.conf";
	int ret = 0;
	if (argc > 1) {
		file_name = argv[1];
	}

	do {
        /* 读配置文件里面的dns服务器 */
		read_conf_file(file_name);
		list_ns();

        /* 初始化DNS服务器 */
		if (0 == g_config.ns_server.ns_count) {
			g_config.ns_server.ns = (ns_t *)xcalloc(1, sizeof(ns_t));
			g_config.ns_server.ns_count = 1;
			g_config.ns_server.ns[0].my_addr.sin_family = AF_INET;
			g_config.ns_server.ns[0].my_addr.sin_addr.s_addr = 0x100007f;
			g_config.ns_server.ns[0].my_addr.sin_port = htons(DEFAULT_LOCAL_PORT);
		}
		if (init_socket() == -1) {
			ret = -1;
			break;
		}

        /* 循环监听DNS请求 */
		ret = epoll_loop();
	} while(0);

	recycle_all();
	return ret;
}