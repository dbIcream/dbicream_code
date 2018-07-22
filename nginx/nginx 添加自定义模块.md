
<!-- TOC -->

- [添加一个新模块](#添加一个新模块)
    - [创建一个新模块的代码存放目录](#创建一个新模块的代码存放目录)
    - [添加新模块的代码和config](#添加新模块的代码和config)
    - [添加新模拟的config文件](#添加新模拟的config文件)
    - [编译时添加新模块的目录](#编译时添加新模块的目录)
    - [配置使用新模块](#配置使用新模块)
    - [访问测试新模块](#访问测试新模块)
    - [参考链接](#参考链接)

<!-- /TOC -->

# 添加一个新模块

## 创建一个新模块的代码存放目录

```shell
# 创建模块目录
mkdir mytest_module
# pwd
/home/xxx/nginx-1.13.7/src/mytest_modul
```

##　添加新模块的代码和config

- [ngx_http_mytest_module.c](https://blog.csdn.net/tao_627/article/details/60957718)

##　添加新模拟的config文件

./configure时添加新模块目录，会自动解析config文件并加载模块  

```conf
# config 文件
ngx_addon_name=ngx_http_mytest_module
HTTP_MODULES="$HTTP_MODULES ngx_http_mytest_module"
NGX_ADDON_SRCS="$NGX_ADDON_SRCS $ngx_addon_dir/ngx_http_mytest_module.c"
```

## 编译时添加新模块的目录

```shell
./configure --prefix=/usr/local/nginx-debug --with-debug --add-module=/home/xxx/nginx-1.13.7/src/mytest_module
make -j4 && make install -j4
```

## 配置使用新模块

在server中配置对应的location，如下面配置会将/test这一类的请求转到mytest模块。这样我们在对应的处理函数中就可以执行相应的操作。  

```conf
location /test {
     mytest;
}
```

## 访问测试新模块

```shell
#将应答保存到请求文件中，即test
curl -x 127.1:80 http://www.mytest.module.com/test -O

# cat test
Hello World!
```

## 参考链接

- [ nginx新增模块](http://www.cnblogs.com/Buggo/p/5503635.html)
- [实现第一个自定义nginx模块](https://blog.csdn.net/tao_627/article/details/60957718)
