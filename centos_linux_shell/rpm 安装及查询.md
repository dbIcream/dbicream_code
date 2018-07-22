<!-- TOC -->

- [rpm包的使用命令](#rpm包的使用命令)
    - [安装及卸载](#安装及卸载)
    - [查询已经安装的包的信息](#查询已经安装的包的信息)
    - [查询未安装的包的信息](#查询未安装的包的信息)

<!-- /TOC -->

# rpm包的使用命令

## 安装及卸载

安装rpm包： rpm -ivh demo_rpm-1.2-1.i386.rpm  
更新rpm包： rpm -Uvh  
卸载某个rpm： rpm -e demo_rpm  

## 查询已经安装的包的信息

查询当前安装的所有包：rpm -qa | grep demo  
查询已经安装的包中的文件：rpm -ql demo_rpm  
查询已经安装的包的信息： rpm -qi demo_rpm  
查询已经安装的包依赖信息： rpm -qR xx  
查询文件所属的包： rpm -qf /usr/local/bin/cpuCheck.sh  

## 查询未安装的包的信息

查询某个未安装的包中的文件： rpm -pql demo_rpm  
查询未安装的包的信息： rpm -pql demo_rpm  
