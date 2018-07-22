#安装CodeViz
基本思路：安装Graphviz -> 安装gcc（修改gcc） -> 安装codeViz
参考链接：http://blog.csdn.net/lianshaohua/article/details/51380994

##安装Graphviz
使用yum直接安装！！
在centos6.5的环境使用时，遇到校验算法不匹配。附上解决方法：[http://blog.sina.com.cn/s/blog_49b6a14b0102ye1r.html](http://blog.sina.com.cn/s/blog_49b6a14b0102ye1r.html)
其中url已经发生了变更，所以路径也要对应变更才能下载到rpm包。
```
rpm -ivh http://archives.fedoraproject.org/pub/archive/epel/5/x86_64/epel-release-5-4.noarch.rpm
yum install python-hashlib
```
如果依然还找不到的话，可以试试下面的方法来安装http://blog.csdn.net/mtawaken/article/details/12832897



##安装gcc
###下载依赖包
几个依赖最好不要装在/usr目录下面，后面卸载不好删除，应该配置--prefix，几个下载包可以通过gcc目录自带的下载依赖包脚本来获取。
```
sh download_prerequisites 
```
###复制到gcc的目录下
```
rm -f mpc gmp mpfr
mv mpc-0.8.1 ../mpc
mv gmp-4.3.2 ../gmp
mv mpfr-2.4.2 ../mpfr
```
###然后就可以编译gcc
继续执行编译gcc的命令，这样子就可以不用配置依赖包的路径
```
sh install_gcc-4.6.2.sh /usr/local /usr/local/gcc-graph
```
###gcc编译遇到的-fPIC的问题和texinfo问题

![Paste_Image.png](http://upload-images.jianshu.io/upload_images/8416343-681b452e21f5245a.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)
修复方法：把 install_gcc-4.6.2.sh 这两行修改一下就能让这里构建通过，主要是添加 --disable-bootstrap
```
../gcc-4.6.2/configure --prefix=$INSTALL_PATH --enable-shared --enable-languages=c,c++ || exit
make bootstrap
```
修改为：
```
CFLAGS="-O2 -fPIC" ../gcc-4.6.2/configure --prefix=$INSTALL_PATH --disable-bootstrap --enable-shared --enable-languages=c,c++ || exit
make -j 4
```
再接下来直接编译gcc，这个过程很漫长，所以可以找点其他的事情干了。


##安装codeviz
因为我没有将gcc安装在/usr下面，所以编译codeviz的时候，要临时设置gcc环境，否则还是会使用系统默认的gcc版本，通过gcc -v就可以查看当前使用的gcc版本。
````
export LD_LIBRARY_PATH=/usr/local/gcc-graph/lib:$LD_LIBRARY_PATH 
export PATH=/usr/local/gcc-graph/bin:$PATH 
````
再安装codeviz：
这个源码比较难找，我直接在github上找到了一个，这里也复制出来了：
https://github.com/dbIcream/codeviz
```
./configure && make install-codeviz
```
>注1：不需要 make ，因为make的作用就是检测是否有gcc若没有则下载源码包，所以这里只要安装 codeviz 即可。具体查看 Makefile 文件。
>注意：这里为什么不是通常用的make install，因为这里make install的作用是先安装gcc再安装codeviz，而前面已经安装了 gcc，所以这里只需要安装 codeviz ，即make install-codeviz脚本，该脚本也就是将genfull 和 gengraph 复制到/usr/local/bin 目录下。

目前为止,CodeViz 安装完成了。

##卸载CodeViz
因为安装时，只是把文件拷到目录下，所以直接删除即可
```
rm -rf /usr/local/lib/CodeViz/
```


##使用codevz生成函数调用图
graphviz较低的版本有BUG（我的是2.1.2），是在设置生成格式--output-type的时候，安装graphviz-gd并不能解决，也就没办法生成gif和png和html的格式，只能生成ps的文件。


使用选项生成更加多样的调用图
        gengraph 支持的选项可以通过 gengraph -h 查看，（鄙人认为）需要注意的选项有下面几个：

-f      指定分析的函数
-t      忽略 Linux 的内核函数
-i      忽略 -i 之后指定的函数，用单引号包含，多个函数间用分号隔开
-s      只显示函数名，不分析其调用情况，函数名用红色方框强调。
-d     调用图的最大深度
-o     指定输出文件的名字
--output-type         输出文件的格式：ps, png, gif。默认 ps
--output_layout      绘图的方向：LR, RL, TB, BT。默认 TB
下面是一个具体的例子：


>gengraph -f sim_main -t --output-type png -o sim_main_level1.png -d 1 -i 'fprintf;printf;__builtin_fwrite;__builtin_puts' --output-layout LR -s 'ss_writeback;ss_memory;ss_execute;ss_dispatch;ss_fetch'


看一个例子：
```
gengraph -f doDomainReplaceLog -t --output-type ps -o doDomainReplaceLog.ps -e 2
```
![Paste_Image.png](http://upload-images.jianshu.io/upload_images/8416343-02bb0c97fdd5b052.png?imageMogr2/auto-orient/strip%7CimageView2/2/w/1240)

###查看生成的函数调用图
默认生成的图是需要使用ps cs2来查看的，格式是.ps。由于BUG问题，生成html和png的方式会失败，可以通过.ps用ps cs2来再生成图片。

##参数链接
- centos下安装Graphviz：http://blog.csdn.net/mtawaken/article/details/12832897
- Codeviz+Graphviz+gcc的安装及使用： http://blog.csdn.net/lianshaohua/article/details/51380994
- gcc升级：http://ayuepm.blog.51cto.com/8738658/1382240
- makeinfo is missing on your system：http://blog.csdn.net/xuezhimeng2010/article/details/49070169
- 用 CodeViz 分析函数调用关系：http://linhan.blog.ustc.edu.cn/?p=497
- Graphviz "gif/png" not recognized问题解决方案 ：http://blog.sina.com.cn/s/blog_b09d4602010195ky.html
- ps cs2下载：http://www.9ht.com/xz/16253.html
