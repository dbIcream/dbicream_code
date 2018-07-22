<!-- TOC -->

- [linux下切换python版本](#linux下切换python版本)
    - [参考链接](#参考链接)
    - [下载链接](#下载链接)
    - [编译安装](#编译安装)
    - [其他修改](#其他修改)
        - [配置python3环境](#配置python3环境)
        - [修改yum使用旧python版本](#修改yum使用旧python版本)

<!-- /TOC -->

# linux下切换python版本

## 参考链接

[Linux更换python版本](https://www.cnblogs.com/zrz43/p/4895635.html)  

## 下载链接

[官网下载链接](https://www.python.org/ftp/python)  
选择合适的版本进行下载  

## 编译安装

```shell
# 编译安装
./configure && make all -j4 && make install -j4
# 安装完成时，查看python版本
/usr/local/bin/python3 --version
```

## 其他修改

### 配置python3环境

```shell
ln -s /usr/local/bin/python3.6 /usr/bin/python
# 查看是否修改成功
python --version
```

### 修改yum使用旧python版本
vi /usr/bin/yum  
把文件头部的#!/usr/bin/python改成#!/usr/bin/python2.4 //改为之前的老版本号  