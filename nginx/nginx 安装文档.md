<!-- TOC -->

- [linux下安装nginx及简单配置](#linux下安装nginx及简单配置)
    - [书籍及参考链接](#书籍及参考链接)
    - [安装依赖库](#安装依赖库)
    - [编译安装nginx](#编译安装nginx)
        - [编译时添加编译参数](#编译时添加编译参数)
        - [其他编译项](#其他编译项)
    - [nginx启动](#nginx启动)
    - [配置示例](#配置示例)

<!-- /TOC -->

**********************************************************

# linux下安装nginx及简单配置

##　书籍及参考链接

- 《深入解析nginx：模块开发与架构解析》在线阅读的地址：<http://yuedu.163.com/book_reader/bfd5574f74b348ceb0cfaa6052c9df33_4>
- nginx编译选项： <http://blog.csdn.net/defonds/article/details/11612247>
- nginx配置SSL模块: <https://www.cnblogs.com/saneri/p/5391821.html>
- linux下的openssl安装: <https://www.jianshu.com/p/907314d42b95>
- access日志格式设置: <http://blog.csdn.net/czlun/article/details/73251723>
- nginx添加自定义HTTP响应头 <http://www.6san.com/767/>

## 安装依赖库

```shell
# 安装gcc, gcc-c++, pcre, perl, zlib, openssl
yum install -y gcc
yum install -y gcc-c++
yum install -y pcre pcre-devel
yum install -y zlib zlib-devel
yum install -y openssl openssl-devel
```

## 编译安装nginx

官方下载地址：<http://nginx.org/en/download.html>  
下载源码后，解压安装。configure可以添加很多参数，最简单的使用就是不加参数直接编译  

```shell
tar -zxvf nginx-1.0.14.tar.gz
./configure  --with-debug --with-http_ssl_module
make
make install
```

### 编译时添加编译参数

- 添加日志调试参数: --with-debug
- 配置ssl和ssl证书: --with-http_ssl_module, 通常生成v1证书就足够了

```shell
./configure --prefix=/usr/local/nginx-debug --with-debug --with-http_ssl_module
```

### 其他编译项

```shell
./configure \
--prefix==/usr/local/nginx-1.11.1 \
--conf-path=/etc/nginx/nginx.conf \
--error-log-path=/var/log/nginx/error.log \
--http-log-path=/var/log/nginx/access.log \
--pid-path=/var/run/nginx/nginx.pid \
--lock-path=/var/lock/nginx.lock \
--user=nginx \
--group=nginx \
--with-http_ssl_module \
--with-http_flv_module \
--with-http_stub_status_module \
--with-http_gzip_static_module \
--http-client-body-temp-path=/var/tmp/nginx/client/ \
--http-proxy-temp-path=/var/tmp/nginx/proxy/ \
--http-fastcgi-temp-path=/var/tmp/nginx/fcgi/ \
--with-pcre
```

## nginx启动

- 指定配置文件启动: -c
- 指定配置文件启动: -t
- 查看编译参数信息: -V
- 快速地停止服务: -s stop
- 优雅停止服务: -s quit
- 平滑升级Nginx: kill -s SIGUSR2 pid(master)

```shell
# 启动nginx
/usr/local/nginx-debug/sbin/nginx -c /usr/local/nginx-debug/conf/nginx.conf
```

## 配置示例

```conf
#user  nobody;
#设置启动几个进程，根据cpu的核数进行设置
worker_processes  1;

#启动日志文件，及配置日志级别
#error_log  logs/error.log;
#error_log  logs/error.log  notice;
#error_log  logs/error.log  info;

#pid        logs/nginx.pid;

#设置连接数
events {
    worker_connections  1024;
}

http {
    include       mime.types;
    default_type  application/octet-stream;

    #添加自定义的conf文件，通常用于不同域名用不同文件配置
    include vhost/*.conf;

    #access.log日志的格式
    #log_format  main  '$remote_addr - $remote_user [$time_local] "$request" '
    #                  '$status $body_bytes_sent "$http_referer" '
    #                  '"$http_user_agent" "$http_x_forwarded_for"';
    #access_log  logs/access.log  main;
    error_log  logs/error.log  debug; #添加debug日志

    sendfile        on;
    #tcp_nopush     on;

    #设置长连接超时时间
    keepalive_timeout  65;

    #gzip  on;
    #一个server对应一个域名
    server {
        listen       88;        #监听端口，即nginx服务端口
        server_name  localhost; #设置服务域名
        #root /www/docs         #设置根目录，也可在location中设置

        #charset koi8-r;
        #access日志，不开启时要显示关闭: access_log off;
        #access_log  logs/host.access.log  main;

        location / {
        #    return 200;                #设置任务请求直接响应200
            root   /www/docs;
            index  index.html index.htm; #设置默认文件
        }
        #设置404时响应的文件
        #error_page  404              /404.html;

        #设置5XX时响应的文件
        error_page   500 502 503 504  /50x.html;
        location = /50x.html {
            root   /www/docs;
        }
        error_page   405 =200  /index.html;
        location = /index.html {
            root   /www/docs;
        }
    }

    #HTTPS server
    server {
        listen       443 ssl;
        server_name  www.myhttps.com;
        ssl on;  #开启ssl

        ssl_certificate      server.crt;
        ssl_certificate_key  server.key;

    #    ssl_session_cache    shared:SSL:1m;
        ssl_session_timeout  5m;

        ssl_protocols SSLv2 SSLv3 TLSv1;
        ssl_ciphers  HIGH:!aNULL:!MD5;
        ssl_prefer_server_ciphers  on;

        location / {
            #root   html;
            root   /www/docs;
            index  index.html index.htm;
        }
    }
}
