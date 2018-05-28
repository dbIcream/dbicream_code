<!-- TOC -->

- [rpm包的使用命令](#rpm包的使用命令)
- [基础命令](#基础命令)
    - [查询已经安装的包的信息](#查询已经安装的包的信息)
    - [查询未安装的包的信息](#查询未安装的包的信息)
- [程序生成rpm包](#程序生成rpm包)
    - [生成rpm包需要的材料](#生成rpm包需要的材料)
        - [编写源文件](#编写源文件)
        - [autoconf生成configure.ac](#autoconf生成configureac)
            - [使用autoscan生成一个模块](#使用autoscan生成一个模块)
            - [修改configure.ac文件](#修改configureac文件)
        - [Aclocal命令生成aclocal.m4](#aclocal命令生成aclocalm4)
        - [autoconf最终生成configure](#autoconf最终生成configure)
        - [Autoheader命令](#autoheader命令)
        - [创建Makefile.am](#创建makefileam)
            - [添加软件等级](#添加软件等级)
            - [定义执行文件名](#定义执行文件名)
            - [定义执行程序所需要的原始文件](#定义执行程序所需要的原始文件)
        - [automake生成configure.in](#automake生成configurein)
        - [configure生成Makefile](#configure生成makefile)
        - [make生成可执行文件](#make生成可执行文件)

<!-- /TOC -->


# rpm包的使用命令
# 基础命令
安装rpm包： rpm -ivh demo_rpm-1.2-1.i386.rpm
更新rpm包： rpm -Uvh
卸载某个rpm： rpm -e demo_rpm
查询当前安装的所有包：rpm -qa | grep demo

## 查询已经安装的包的信息
查询已经安装的包中的文件：rpm -ql demo_rpm
查询已经安装的包的信息： rpm -qi demo_rpm
查询已经安装的包依赖信息： rpm -qR xx
查询文件所属的包： rpm -qf /usr/local/bin/cpuCheck.sh

## 查询未安装的包的信息
查询某个未安装的包中的文件： rpm -pql demo_rpm
查询未安装的包的信息： rpm -pql demo_rpm

********************************************

# 程序生成rpm包
[参考链接](https://blog.csdn.net/initphp/article/details/43705765)
## 生成rpm包需要的材料
确保automake已经安装
```
yum -y install automake
```
### 编写源文件
hello.c
```
#include <stdio.h>

int main()
{
        printf("hello world!\n");
        return 0;
}
```


### autoconf生成configure.ac

configure.ac用来侦测所指定的源码文件是否存在，来确定源码目录的有效性。
#### 使用autoscan生成一个模块
autoscan自动生成configure.scan，重命名为configure.ac

#### 修改configure.ac文件
- 修改AC_INIT，修改程序名，版本号
- 添加AM_INIT_AUTOMAKE的宏来识别automake
- 修改AC_OUTPUT，最终生成Makefile文件
```
#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.69])

# 修改程序名，版本号，以及BUG联系邮箱
#AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_INIT(hello, 1.0, dbicream@163.com)
AM_INIT_AUTOMAKE(hello, 1.0)

# 程序包含的文件
AC_CONFIG_SRCDIR([hello.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# Checks for header files.
# Checks for typedefs, structures, and compiler characteristics.
# Checks for library functions.

# 最终生成的文件，这里输出Makefile
AC_OUTPUT([Makefile])
```
### Aclocal命令生成aclocal.m4
扫描configure.ac文件生成aclocal.m4文件, **该文件主要处理本地的宏定义**，它根据已经安装的宏、用户定义宏和acinclude.m4文件中的宏将configure.ac文件需要的宏集中定义到文件aclocal.m4中。

### autoconf最终生成configure
这个命令将configure.ac文件中的宏展开，生成 configure 脚本。这个过程可能要用到aclocal.m4中定义的宏。

### Autoheader命令
执行autoheader命令。该命令生成 config.h.in 文件。该命令通常会从 "acconfig.h” 文件中复制用户附加的符号定义。该例子中没有附加的符号定义, 所以不需要创建 "acconfig.h” 文件。

### 创建Makefile.am
automake要用的脚本配置文件是Makefile.am，用户需要自己创建相应的文件。之后，automake工具转换成Makefile.in。

#### 添加软件等级
添加AUTOMAKE_OPTIONS，软件的三种等级foreign、gnu和gnits，默认等级为gnu
，它只检测必须的文件
|  等级   |       说明       | 备注 |
| ------- | ---------------- | ---- |
| foreign | 只检测必须的文件 |      |

#### 定义执行文件名
bin_PROGRAMS=main，如果要产生多个执行文件，每个文件名用空格隔开。

#### 定义执行程序所需要的原始文件
main_SOURCES=main.c，如果”main”这个程序是由多个原始文件(.c,.h,.so等)所产生的，则必须把它所用到的所有原始文件都列出来，并用空格隔开。如main_SOURCES=main.c sunq.c main.h  
要注意的是，如果要定义多个执行文件，则对每个执行程序都要定义相应的file_SOURCES。

```
AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=main
main_SOURCES=hello.c
``` 

### automake生成configure.in
使用automake对其生成configure.in文件，在这里使用选项“add-missing”可以让automake自动添加有一些必需的脚本文件。
```
automake --add-missing
```

### configure生成Makefile
运行configure之后生成Makefile，然后再make生成可执行文件
通过运行自动配置设置文件configure，把Makefile.in变成了最终的Makefile。

### make生成可执行文件
make
./main

