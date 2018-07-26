
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
 
#define MAXLINE 4096
#define SEND_HTTP_HEAD "GET http://www.mytest.com/index.html HTTP/1.1\r\n\
Host: www.mytest.com\r\n\
Accept: text/html,image/webp,*/*;q=0.8\r\n\
User-Agent: Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.153 Safari/537.36\r\n\
Accept-Encoding: gzip,deflate,sdch\r\n\r\n"

 
int main()
{
	int sockfd, n;
	char recvline[MAXLINE];

	struct sockaddr_in servaddr;

	char *IP = "218.244.133.30";
	int port = 80;
	char *buf = SEND_HTTP_HEAD;

	// TODO: 设置ip和端口信息

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket error\n");
		exit(0);
	}
		
	/* 初始化socket  */
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(port);

	/* 将ip信息初始化到 sockaddr_in 结构体中 */
	if (inet_pton(AF_INET, IP, &servaddr.sin_addr) <= 0) {
		printf("inet_pton error\n");
	}

	/* socket 连接 */
	if (connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
		printf("connect error\n");
	}

	/* 写入http的请求头 */
	write(sockfd, buf, strlen(buf));
	printf("SEND HEADER: \n%s\n\n", buf);

	/* 读应答数据 */
	while((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;

		/* 数据输出到终端 */
		if(fputs(recvline, stdout) == EOF) {
			printf("fputs error\n");
		}	
	}

	/* 读数据异常时输出 */
	if(n < 0) {
		printf("read error\n");
	}
	
	/* 关闭socket */
	close(sockfd);
	printf("all ok now\n");

	return 1;
}

