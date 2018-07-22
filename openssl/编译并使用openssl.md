##下载openssl
下载地址：https://www.openssl.org/source/
linux下可以直接下载指定版本
```
wget https://www.openssl.org/source/openssl-1.1.0g.tar.gz
```

##编译openssl
解压，使用--prefix指定目录安装。这样不会与系统原本的openssl冲突，但是后面使用时就需要指定openssl的目录
```
tar -zxvf openssl-1.1.0g.tar.gz
cd openssl-1.1.0g
./config --prefix=/usr/local/openssl && make -j4 && make rpm -j4
```

##如何使用新版本的openssl
通过修改环境，使得我们在编译程序时，可以使用到我们需要的openssl版本。
###通过外部配置使用
```
#先查看PKG_CONFIG_PATH是否有值，方法是echo $PKG_CONFIG_PATH
#如果PKG_CONFIG_PATH有值
export PKG_CONFIG_PATH=usr/local/openssl/lib/pkgconfig:$PKG_CONFIG_PATH
#如果PKG_CONFIG_PATH没有值
export PKG_CONFIG_PATH=usr/local/openssl/lib/pkgconfig
```
###通过脚本调用时直接指定目录
假设当前使用的编译方式是gen.sh来调用configure，可以如下修改，使得我们可以获取到正确的路径。下面是我编译nghttp2时候使用到的命令：
```
PKG_CONFIG_PATH=/usr/local/lib/pkgconfig:/usr/local/openssl/lib/pkgconfig
./configure --disable-examples --enable-hpack-tools=no --with-spdylay LDFLAGS=" -ldl"

```


##使用openssl发送ssl请求
发https相对路径的请求到源/代理服务器
```
openssl s_client  -connect 127.0.0.1:443
GET /static/images/public/about-us/company-banner.png HTTP/1.1
HOST: www.dianrong.com
```

