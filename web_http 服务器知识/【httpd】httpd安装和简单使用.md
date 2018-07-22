<!-- TOC -->

- [httpd的安装及使用](#httpd的安装及使用)
    - [安装](#安装)
        - [直接拷贝](#直接拷贝)
        - [源码安装](#源码安装)
    - [开启httpd，默认端口80运行apache httpd，默认端口80](#开启httpd默认端口80运行apache-httpd默认端口80)
    - [停止httpd](#停止httpd)
    - [启动问题解决](#启动问题解决)
        - [解决端口被占用](#解决端口被占用)
    - [配置](#配置)
        - [增加一个自定义域名](#增加一个自定义域名)
    - [简单的访问测试](#简单的访问测试)

<!-- /TOC -->

# httpd的安装及使用

## 安装

### 直接拷贝

其实最简单的方法的方式是直接把其他机器上已经装过的httpd文件夹，直接拷贝过来，然后稍稍改改配置就可以用了。

### 源码安装

```shell
# 下载解析
tar -zxvf httpd-2.0.54.tar.gz
cd httpd-2.0.54

# 编译安装
./configure --enable-dav --enable-so --prefix=/usr/local/httpd
make
make install

# 启动
/test/bin/httpd -k start
```

## 开启httpd，默认端口80运行apache httpd，默认端口80
```shell
cd /usr/local/httpd
./httpd -k start
./httpd -k restart
```

## 停止httpd

```shell
./httpd -k stop
```

## 启动问题解决

### 解决端口被占用

修改配置文件中的端口： /usr/local/httpd/conf/httpd.conf  

```conf
<VirtualHost *:80>
ServerName www.cyan123.com
ProxyPass / http://localhost:8081/
ProxyPassReverse / http://localhost:8081/
ErrorLog logs/gaofeihang.cn-error_log
CustomLog logs/gaofeihang.cn-access_log common
</VirtualHost>
```

##　配置

### 增加一个自定义域名

```conf
DocumentRoot "/www/docs"
<Directory "/www/docs">
<VirtualHost *:8088>
#ServerAdmin webmaster@dummy-host.example.com ，管理员邮箱
    ServerName www.cyan123.com
    DocumentRoot /www/docs
    <Directory /www/docs>
        Order deny,allow
        Allow from all
    </Directory>
</VirtualHost>
```

## 简单的访问测试

```shell
curl -voa http://www.cyan123.com:8888/cyan123/index.html
```
