<!-- TOC -->

- [用于调试进程和定位问题的配置项](#用于调试进程和定位问题的配置项)
- [正常运行的配置项](#正常运行的配置项)
- [事件类配置项](#事件类配置项)
- [配置一个静态web服务器](#配置一个静态web服务器)
    - [内存及磁盘资源的分配](#内存及磁盘资源的分配)
    - [连接管理](#连接管理)

<!-- /TOC -->

[配置解析](http://yuedu.163.com/book_reader/bfd5574f74b348ceb0cfaa6052c9df33_4)
###用于调试进程和定位问题的配置项
- 是否以守护进程方式运行Nginx
daemon on|off ，默认on

- 是否以master/worker方式工作
master_process on|off ，默认on

- error日志的设置
error_log pathfile level ，默认error_log logs/error.log error;
**如果日志级别设定到debug，必须在configure时加入--with-debug配置项**

- 仅对指定的客户端输出debug级别的日志
debug_connection[IP|CIDR]
events {
    debug_connection 10.224.66.14;
    debug_connection 10.224.57.0/24;
}

- 限制coredump核心转储文件的大小
worker_rlimit_core size
- 指定coredump文件生成目录
working_directory path

###正常运行的配置项
- 嵌入其他配置文件
include pathfile
```
#它的参数既可以是绝对路径，也可以是相对路径（相对于Nginx的配置目录，即nginx.conf所在的目录）
include mime.types;
include vhost/*.conf;
```
- 指定Nginx worker进程可以打开的最大句柄描述符个数
worker_rlimit_nofile limit

- Nginx worker进程个数
worker_processes number;
- 绑定Nginx worker进程到指定的CPU内核
worker_cpu_affinity cpumask[cpumask...] ，**仅对linux有效**
```
worker_processes 4;
worker_cpu_affinity 1000 0100 0010 0001;
```

###事件类配置项
- 是否打开accept锁
accept_mutex[on|off] ， 默认on
- lock文件的路径
lock_file path/file;
- 使用accept锁后到真正建立连接之间的延迟时间
accept_mutex_delay Nms;

- 选择事件模型
use[kqueue|rtsig|epoll|/dev/poll|select|poll|eventport] ，默认Nginx会自动使用最适合的事件模型

- 每个worker的最大连接数
worker_connections number

###配置一个静态web服务器
- 主机名称
server_name name[...];
server_name后可以跟多个主机名称，如server_name www.testweb.com 、
download.testweb.com;

- 重定向主机名称的处理
server_name_in_redirect on|off;
该配置需要配合server_name使用。在使用on打开时，表示在重定向请求时会使用server_name里配置的第一个主机名代替原先请求中的Host头部，而使用off关闭时，表示在重定向请求时使用请求本身的Host头部

- **location**
location[=|~|~*|^~|@]/uri/{...}
location会尝试根据用户请求中的URI来匹配上面的/uri表达式，如果可以匹配，就选择location{}块中的配置来处理用户请求。
location是有顺序的，当一个请求有可能匹配多个location时，实际上这个请求会
被第一个location处理。
```
location / {
# /可以匹配所有请求
location ~* \.(gif|jpg|jpeg)$ {
# 匹配以
.gif、
.jpg、
.jpeg结尾的请求
…
}
```

- 文件路径的定义
语法： root path;
默认： root html;
配置块： http、server、location、if
```
location /download/ {
root optwebhtml;
}
```

- 访问首页
语法： index file...;
默认： index index.html;
配置块： http、server、location
```
location {
root path;
index index.html htmlindex.php /index.php;
}
location / (
error_page 404 @fallback;
) location @
fallback (
proxy_pass http://backend
;)
```
- 根据HTTP返回码重定向页面
语法： error_page code[code...][=|=answer-code]uri|@named_location
配置块： http、server、location、if
```
error_page 404 404.html;
error_page 502 503 504 50x.html;
error_page 403 http://example.com/forbidden.html
```

- try_files
语法： try_files path1[path2]uri;
配置块： server、location
try_files后要跟若干路径，如path1 path2...，而且最后必须要有uri参数，意义如下：尝试按照顺序访问每一个path，如果可以有效地读取，就直接向用户返回这个path对应的文件结束请求，否则继续向下访问。如果所有的path都找不到有效的文件，就重定向到最后的参数uri上。因此，最后这个参数uri必须存在，而且它应该是可以有效重定向的。

####内存及磁盘资源的分配
- 存储HTTP头部的内存buffer大小
语法： client_header_buffer_size size;
默认： client_header_buffer_size 1k;
配置块： http、server
- 存储超大HTTP头部的内存buffer大小
语法： large_client_header_buffers number size;
默认： large_client_header_buffers 48k;
配置块： http、server
**如果HTTP请求行（如GET/index HTTP/1.1）的大小超过上面的单个buffer，则返回"Request URI too large"**
- 存储HTTP包体的内存buffer大小
语法： client_body_buffer_size size;
默认： client_body_buffer_size 8k/16k;
配置块： http、server、location

- connection_pool_size ，TCP连接预先分配一个内存池
- request_pool_size ，每个请求都分配一个内存池

####连接管理
- 读取HTTP头部的超时时间， client_header_timeout time
- 读取HTTP包体的超时时间， client_body_timeout time
- 发送响应的超时时间， send_timeout time;
- reset_timeout_connection
连接超时后将通过向客户端发送RST包来直接重置连接。这个选项打开后，Nginx会在某
个连接超时后，不是使用正常情形下的四次握手关闭TCP连接，而是直接向用户发送RST重置包，不再等待用户的应答，直接释放Nginx服务器上关于这个套接字使用的所有缓存

- 对某些浏览器禁用keepalive功能
语法： keepalive_disable[msie6|safari|none]...
默认： keepalive_disablemsie6 safari
配置块： http、server、location
- keepalive超时时间， keepalive_timeout time
- 一个keepalive长连接上允许承载的请求最大数， keepalive_requests n;
- tcp_nodelay， 确定对keepalive连接是否使用TCP_NODELAY选项
