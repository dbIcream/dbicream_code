##解压并安装
###下载相关的包
下载需要使用到的依赖包，其中mpfr的版本要跟gcc匹配。如何查看匹配呢，可以通过gcc安装包中自带的工具下载脚本来下载对应的包。脚本路径如下：
```
gcc-5.4.0/contrib/download_prerequisites
```
其中我们要用到的主要是这三个依赖库：
```
mpfr-2.4.2.tar.bz2
mpc-0.8.1.tar.gz
gmp-4.3.2.tar.bz2
```
另外下载速度可能会有点感人，所以可以通过其他途径下载。

###编译安装gcc

解压gcc-5.4.0.tar.bz2，进入目录并下载解压以下几个文件
```
tar -jxvf gcc-5.4.0.tar.bz2
cd gcc-5.4.0
mpfr-2.4.2.tar.bz2
mpc-0.8.1.tar.gz
gmp-4.3.2.tar.bz2
```
重命名或者软链接成
```
ln -s gmp-4.3.2 gmp
ln -s mpfr-2.4.2 mpfr
ln -s mpc-0.8.1 mpc
```
编译安装，-j4是指使用多线程来编译，可以更加充分利用机器性能，加快编译效率。整个编译过程会比较长，我在公司比较垃圾的机器上编译了3个小时多才完成.......
```
./configure --prefix=/usr/local/gcc-5.4.0 --enable-checking=release --enable-languages=c,c++ --disable-multilib && make -j4 && make install -j4
```

##使用gcc
首先我们要配置环境变量。另外，配置环境变量时有一个技巧，就是要先看看当前这个环境变量是不是有值，如：echo $LD_LIBRARY_PATH。
如果没有值时，就不需要再加上:$LD_LIBRARY_PATH，如export LD_LIBRARY_PATH=/usr/local/gcc-5.4.0/bin
```
export PATH=/usr/local/gcc-5.4.0/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/gcc-5.4.0/lib:/usr/local/gcc-5.4.0/lib64:$LD_LIBRARY_PATH
export C_INCLUDE_PATH=/usr/local/gcc-5.4.0/include:$C_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/usr/local/gcc-5.4.0/include:$CPLUS_INCLUDE_PATH
```
然后我们就可以用命令来判断当前使用的gcc版本了。上面的方法是临时配置gcc路径，所以如果在其他窗口上使用新版本gcc，也需要这么先配置环境变量。
```
gcc --version
```


