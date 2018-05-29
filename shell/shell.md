<!-- TOC -->

- [网络相关](#网络相关)
    - [curl](#curl)
    - [wget](#wget)
    - [tcpflow/tcpdump](#tcpflowtcpdump)
    - [ping/dig/traceroute](#pingdigtraceroute)
- [编辑文档](#编辑文档)
    - [编辑器vi](#编辑器vi)
    - [拷贝命令cp/scp](#拷贝命令cpscp)
- [系统信息](#系统信息)
    - [日期](#日期)
    - [查看系统状态](#查看系统状态)
    - [查看磁盘使用](#查看磁盘使用)
    - [查看端口占用](#查看端口占用)
    - [进程管理Kill/killall](#进程管理killkillall)
    - [硬链接/软链接](#硬链接软链接)
- [文档查找](#文档查找)
    - [ls/ll](#lsll)
    - [查看文件内容](#查看文件内容)
    - [awk打印](#awk打印)
    - [过滤grep/fgrep](#过滤grepfgrep)
    - [sed替换](#sed替换)
- [md5生成](#md5生成)
- [crontab](#crontab)
    - [crontab过程](#crontab过程)
        - [系统任务调度](#系统任务调度)

<!-- /TOC -->

# 网络相关
## curl
**设置代理**：curl -x 192.168.100.100:1080 http://www.linux.com
**不验证https证书**: curl https://www.baidu.com/index.html -k
发送POST请求： curl -d "userName=tom&passwd=123456" -X POST http://www.example.com/login
发送DELETE请求：curl -X DELETE www.baidu.com
分段下载：curl -r 100-200 -o dodo1_part2.JPG http://www.linux.com/dodo1.JPG
仅显示HTTP头部信息: curl -I http://www.codebelief.com 
保存文件: curl -o index.html http://www.codebelief.com 
跟随链接重定向: curl -L http://codebelief.com 
指定UA:  curl -A "Mozilla/5.0 (Android; Mobile; rv:35.0) Gecko/35.0 Firefox/35.0" http://www.baidu.com 
[指定cookie](http://www.jb51.net/article/118402.htm)
发送chunk请求：curl -v -x 127.0.0.1:8123 -H "Transfer-Encoding: chunked" -F "data=@file.22M"http://www.wspxtcp10.com:4569/post -o /dev/null

## wget
wget不验证证书： wget https://www.baidu.com/index.html --no-check-certificate
添加自定义头部： wget -d --header='X-Header:myheader' -e--http_proxy=127.1:8009 http://img.lanrentuku.com/img/allimg/1612/14821292138579.jpg  -O /dev/null -t 1

## tcpflow/tcpdump
指定ip：tcpflow -cp -i eth0 host 10.8.225.64 and port 60000
指定端口：tcpflow -cp -i eth0 host 10.8.225.64 and port 60000

## ping/dig/traceroute
nslookup、dig查看域名解析
快速发10个大小为100的包：Ping –nfc 10 –s 100 36.250.74.83
隔5秒发一个包，并显示访问详细：Ping –i 5 –vc 3 36.250.74.83
显示中间访问的路由：Ping –Rc 1 36.250.74.83
路径探测： traceroute -Tn -p 80 218.85.157.99

# 编辑文档
## 编辑器vi
显示行号： set nu

## 拷贝命令cp/scp
ssh主机间拷贝scp: scp /home/daisy/full.tar.gz root@172.19.2.75:/home/root

*************************************************
# 系统信息
##日期
查看当前时间： date
显示时间戳： date +%s

## 查看系统状态
查看当前的ip： ifconfig
修改密码： passwd
查看历史登陆记录: last
查看历史的执行命令： history
查看系统版本： lsb_release -a

## 查看磁盘使用
查看磁盘使用情况：df -h

## 查看端口占用
查看端口使用情况： netstat -aux,  nestat -anpt

## 进程管理Kill/killall
强制杀死一个进程： kill -9 pid
杀死的同时生成一个core文件： kill -6 pid

## 硬链接/软链接
硬链接： ln file afile
软链接： ln -s file bfile

****************************************************
# 文档查找
## ls/ll
ls -l /tmp
ls -a /tmp(包含隐藏文件)

## 查看文件内容
cat
head -n 10
tail -f file
从小到大排列： sort -n list
从大到小排列： sort -nr list | uniq -c（显示重复行显示次数）
字符统计： cat test | wc -l显示行数

## awk打印
awk打印
cat /etc/passwd |awk '{print $1}' 分隔符空格
cat /etc/passwd |awk  -F ':'  '{print $1}'分隔符:
cat /etc/passwd |awk  -F ':'  '{print $1"\t"$2}' 
获取到eth0的IP的命令：
ifconfig eth0 | grep "inet addr"  |awk -F ':' '{print $2}' | awk '{print $1}' 

## 过滤grep/fgrep
查找多个词： -e str1 -e str2
排查词： -v str1 -v str2
显示某个词过后的n行： -A 10 "GET"

## sed替换
sed批量替换字符串
	sed 's/5/10/g' 用10替换5，g表示整行所有匹配
	sed -i "s/原/新/g" grep 原 -rl 所在目录（就地修改、操作前需备份）
	    -l输出匹配的文件名
	sed 'y/123/ABC' test_sed
	删除：sed '2，$d' example删除第二行到最后一行
		sed '/test/'d example，删除包含test的行
	sed -n 's/test/mytest/p' example含时打印


******************************************************************
# md5生成
md5sum file
echo -n str | md5sum

# crontab
[参考链接](https://www.cnblogs.com/xingzc/p/5969777.html)
crond是linux下用来周期性的执行某种任务或等待处理某些事件的一个守护进程，crond进程每分钟会定期检查是否有要执行的任务，如果有要执行的任务，则自动执行该任务。当安装完成操作系统后，默认会安装此服务工具，并且会自动启动crond进程，crond进程每分钟会定期检查是否有要执行的任务，如果有要执行的任务，则自动执行该任务。  
**任务包括：系统任务调度和用户任务调度**
## crontab过程
### 系统任务调度
对应/etc/crontab文件，就是负责系统任务调度的配置文件。


crontab -l
列出当前日程表、crontab -n、-r清空crontab文件内容
*/5 * * * * /usr/local/bin/checkCacheLog.sh		每5分钟执行一次
5 * * * * /usr/local/bin/checkCacheLog.sh		每小时的第5分钟执行






