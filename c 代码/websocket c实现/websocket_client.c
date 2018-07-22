#include <netinet/in.h> // for sockaddr_in
#include <sys/types.h>  // for socket
#include <sys/socket.h> // for socket
#include <stdio.h>      // for printf
#include <stdlib.h>     // for exit
#include <string.h>     // for bzero
#include <assert.h>
#include <errno.h>

/*
./a (squid IP) (squid port) (额外增加的header name) (header len) (add times) (waittime  after send request)
./a 127.0.0.1 3128 aa 10 50 50
*/
const char request0[] = "GET ws://www.ng2.com/ HTTP/1.1\r\nHost: www.ng2.com\r\nSec-WebSocket-Key: sBcNTmACQ0ui3zHHn4T5aA==\r\nSec-WebSocket-Protocol: chat, superchat\r\nSec-WebSocket-Version: 13\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nPragma: no-cache\r\n";

int main(int argc, char **argv)
{
    if (argc <= 5)
    {
        printf("Usage: ./%s ServerIPAddress\n", argv[0]);
        exit(1);
    }

    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));    /* 置字节字符串s的前n个字节为零且包括‘\0’ */
    server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &server_addr.sin_addr); /* 初始化服务端Ip, sin_addr */
    server_addr.sin_port = htons(atoi(argv[2]));
    socklen_t server_addr_length = sizeof(server_addr);

    struct sockaddr_in client_addr;
    bzero(&client_addr, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    inet_pton(AF_INET, "10.8.111.11", &client_addr.sin_addr);  /* 初始化客户端ip, sin_addr */
    client_addr.sin_port = htons(0);
    socklen_t client_addr_length = sizeof(client_addr);

    /* 创建socket */
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    int bind_result = bind(client_socket, (struct sockaddr *)&client_addr, sizeof(client_addr));
    printf("client_socket: %d\tbind_resutl: %d\n", client_socket, bind_result);

    if (connect(client_socket, (struct sockaddr *)&server_addr, server_addr_length) < 0)
    {
        printf("Can Not Connect To %s:%s!\nerrno:%d\n", argv[1], argv[2], errno);
        exit(1);
    }

    char *header_add;
    unsigned header_len = atoi(argv[4]);
    unsigned header_add_time = atoi(argv[5]);
    unsigned header_name_len = strlen(argv[3]);
    assert(header_len > 0 && header_len > header_name_len + 4 && header_add_time > 0);
    header_add = malloc(header_len * sizeof(char));
    memset((void *)header_add, '1', header_len);
    memcpy((void *)header_add, (void *)argv[3], header_name_len);
    memcpy(&header_add[header_len - strlen("\r\n")], (void *)"\r\n", strlen("\r\n"));

    unsigned request_len = strlen(request0) + header_len * header_add_time + strlen("\r\n");
    char *request = malloc((request_len + 1) * sizeof(char));
    unsigned offset = 0;

    memcpy((void *)request, request0, strlen(request0));
    offset += strlen(request0);
    int i;
    for (i = 0; i < header_add_time; i++)
    {
        char string[32] = {'\0'};
        int len = sprintf(string, "%d", i);
        assert(len < 32 && len > 0 && (len + header_name_len + 3) < header_len);
        //		printf("%d %d %s\n", i, len, string);
        memcpy((void *)&header_add[header_name_len], string, len);
        header_add[len + header_name_len] = ':';
        memcpy((void *)&request[offset], header_add, header_len);
        //		printf("%s\n\n", header_add);
        offset += header_len;
    }
    memcpy((void *)&request[offset], "\r\n", strlen("\r\n"));
    request[request_len] = '\0';

    printf("%d bytes send.\n", write(client_socket, request, request_len));
    free(header_add);
    free(request);

    usleep(atoi(argv[6]));
    char readbuf[1000];
    int readlen = 0;
    int sum = 0;
    while ((readlen = read(client_socket, readbuf, 999)) > 0)
    {
        sum += readlen;
        readbuf[readlen] = '\0';
        printf("%s", readbuf);
    }
    printf("%d bytes recv.\n", sum);
    close(client_socket);
    //system("killall nc");
    return 0;
}
