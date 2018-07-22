#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

#define buf_len 1024
const char reply0[] = "HTTP/1.0 503 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\n";
const char reply1[] = "HTTP/1.0 503 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 0\r\n";
const char reply2[] = "HTTP/1.0 503 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 10\r\n";
const char reply3[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply4[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nContent-length: 0\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply5[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nContent-length: 10\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply6[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nContent-length: 10\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\nConnection: Upgrade\r\n";
const char reply7[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply8[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\nConnection: Upgrade\r\n";
const char reply9[] = "HTTP/1.0 404 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\n";
const char reply10[] = "HTTP/1.0 404 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 0\r\n";
const char reply11[] = "HTTP/1.0 404 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 10\r\n";
const char reply12[] = "HTTP/1.0 302 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\n";
const char reply13[] = "HTTP/1.0 302 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 0\r\n";
const char reply14[] = "HTTP/1.0 302 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 10\r\n";
const char reply15[] = "HTTP/1.0 200 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\n";
const char reply16[] = "HTTP/1.0 200 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 0\r\n";
const char reply17[] = "HTTP/1.0 200 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: close\r\nContent-length: 10\r\n";
const char reply18[] = "HTTP/1.0 200 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nUpgrade: websocket\r\nContent-length: 0\r\n";
const char reply19[] = "HTTP/1.0 200 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nContent-length: 0\r\n";
const char reply20[] = "HTTP/1.0 200 Service Unavailable\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nUpgrade: websocket\r\nContent-length: 0\r\n";
const char reply21[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nContent-length: 0\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply22[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nContent-length: 0\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply23[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nContent-length: 0\r\nUpgrade: websocket\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply24[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nContent-length: 0\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\n";
const char reply25[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nContent-length: 0\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat\r\n";
const char reply26[] = "HTTP/1.0 101 Switching Protocols\r\nDate: Wed, 28 Sep 2016 09:14:41 GMT\r\nServer: Nginx Server V2.0\r\nContent-Type: text/html\r\nConnection: Upgrade\r\nContent-length: -10\r\nUpgrade: websocket\r\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\r\nSec-WebSocket-Protocol: chat, superchat\r\n";
const char reply27[] = "HTTP/1.0 101 Switching Protocols\nUpgrade: websocket\nSec-WebSocket-Accept: HSmrc0sMlYUkAGmm5OPpG2HaGWk=\nSec-WebSocket-Protocol: chat\nConnection: Upgrade\n";

const char* pathname_recieve = "/tmp/websock.recieve";
const char* pathname_send = "/tmp/websock.send";
const char *reply = NULL;
char buf[buf_len];
int num = 0;

int init_file_send(int fd);
int read_and_store_accept(int store_in_fd, int read_from_fd);
int send_reply(int send_to_fd, int send_from_fd);

int main(int argc, char* argv[])
{
	if ( argc <= 5 )
	{
		printf( "usage: %s ip_address port_number\n", basename(argv[0]) );
		return 1;
	}

	switch (*argv[3]) {
	case '0': reply = reply0; break;
	case '1': reply = reply1; break;
	case '2': reply = reply2; break;
	case '3': reply = reply3; break;
	case '4': reply = reply4; break;
	case '5': reply = reply5; break;
	case '6': reply = reply6; break;
	case '7': reply = reply7; break;
	case '8': reply = reply8; break;
	case '9': reply = reply9; break;
	case 'a': reply = reply10; break;
	case 'b': reply = reply11; break;
	case 'c': reply = reply12; break;
	case 'd': reply = reply13; break;
	case 'e': reply = reply14; break;
	case 'f': reply = reply15; break;
	case 'g': reply = reply16; break;
	case 'h': reply = reply17; break;
	case 'i': reply = reply18; break;
	case 'j': reply = reply19; break;
	case 'k': reply = reply20; break;
	case 'l': reply = reply21; break;
	case 'm': reply = reply22; break;
	case 'n': reply = reply23; break;
	case 'o': reply = reply24; break;
	case 'p': reply = reply25; break;
	case 'q': reply = reply26; break;
	case 'r': reply = reply27; break;
	default:;
	}

	size_t wait_times = atoi(argv[4]);
	size_t wait_times_before_reply = atoi(argv[5]);
	
	//int fd_rcv = open(pathname_recieve, O_WRONLY|O_APPEND|O_CREAT, 0666);
	//assert( fd_rcv >= 0);
	//int fd_sd = open(pathname_send, O_RDWR|O_TRUNC|O_CREAT, 0666);
	//assert( fd_sd >= 0 );

	//assert( !init_file_send(fd_sd) );

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero( &address, sizeof(address) );
	address.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &address.sin_addr );
	address.sin_port = htons( port );

	int sock = socket( PF_INET, SOCK_STREAM, 0);
	assert( sock >= 0);

	int ret = bind( sock, (struct sockaddr*)&address, sizeof(address) );
	assert( ret != -1 );
	ret = listen( sock, 5 );
	assert( ret != -1 );

	time_t now;
	struct tm *timenow;
	struct sockaddr_in client;
	socklen_t client_addrlen = sizeof(client);
	while (  ret = accept( sock, (struct sockaddr*)&client, &client_addrlen ) )
	{
		if ('y' == *argv[7]) exit(1);
		//int read_len = read_and_store_accept(fd_rcv, ret);		
	/*	
		int send_len = send_reply(ret, fd_sd);
	*/
		if ( !reply ) {
			sleep(10);
			printf("disconnect.\n");
			close(ret);
			continue;
		}
		strcpy( buf, reply );
		char temp[20];
		sprintf( temp, "Number: %d\r\n\r\n\0" );
		strcat( buf, temp );
		int send_len = 0;
		send_len = strlen( buf );
		sleep(wait_times_before_reply);
		assert( write( ret, buf, send_len ) == send_len );
		//exit(1);			
		//printf("%d  read length: %d, send_length: %d\n", num, read_len, send_len);	
		if ('y' == *argv[8]) exit(1);
		sleep(wait_times);
		printf("%d  sleep end.\n", num);	
			int i = atoi(argv[6]);
			while (i--) {
				sleep(1);
				write(ret, "hi\n", 3);
				printf("%d hi sent\n", i);
			}
		close( ret );
	}
	
	printf("accept error. errno = %d\n", errno);	
	system("pause");
}

int init_file_send(int fd)
{
	int len = strlen(reply);
	if ( write(fd, reply, len) != len )
		return 1;
	return 0;
}

int read_and_store_accept(int store_in_fd, int read_from_fd)
{
	int sum = 0;
	int recv_len = 0;
	time_t now;
        struct tm *timenow = NULL;
	
	while( 0 < (recv_len = recv(read_from_fd, buf, buf_len, 0)) )
	{
		if ( write( store_in_fd, buf, recv_len ) != recv_len )
		{
			printf("write error. errno = %d\n", errno);
			return -1;
		}
		sum += recv_len;
		if ( buf_len != recv_len )
			break;
	}
	
	num++;
	time( &now );
        timenow = localtime( &now );
        sprintf( buf, "%d\n%s\n\n\n\n", num, asctime(timenow) );
	write( store_in_fd, buf, 30 );
	return sum;
}

int send_reply(int send_to_fd, int send_from_fd)
{
	int sum = 0;
	int read_len = 0;

	lseek( send_from_fd, 0, SEEK_SET );
	
	while( 0 < (read_len = read(send_from_fd, buf, buf_len)) )
	{
		if ( write( send_to_fd, buf, read_len ) != read_len )
		{
			printf("write error. errno = %d\n", errno);
			return -1;
		}
		sum += read_len;
	}
	
	return sum;
}