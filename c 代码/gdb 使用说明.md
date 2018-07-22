<!-- TOC -->

- [gdb使用说明](#gdb使用说明)
    - [参考链接](#参考链接)
    - [基本使用方法](#基本使用方法)
    - [程序执行](#程序执行)
    - [设置断点](#设置断点)
    - [条件断点](#条件断点)
    - [查看变量值及运行状态](#查看变量值及运行状态)
    - [查看堆栈](#查看堆栈)
    - [watch监控变量值](#watch监控变量值)
    - [强制调用函数](#强制调用函数)
    - [处理信号](#处理信号)
    - [设置参数](#设置参数)

<!-- /TOC -->
*******************************************************

# gdb使用说明

## 参考链接

[参考链接：利用gdb在汇编指令级调试C程序](https://blog.csdn.net/mergerly/article/details/8538272)

## 基本使用方法

- 编译时添加调试选项 : gcc -g -o main main.c
- 启动gdb调试: gdb main
- 查看代码： l, l -, l 10

## 程序执行

运行程序：run/r  
断点之后继续执行程序： c  
退出函数： finish  
退出循环： until  
退出gdb： quit/q  

## 设置断点

按行设置断点： break/b linenum, b 10, b a.c:10  
按函数设置断点： break func  
显示断点： info b  
删除断点： delete/d num, d range  
清空某行的所有断点： clear num, clear func  
暂停/启用断点： disable/enable num  

## 条件断点

条件断点：b 7 if i == 7  

```c
#include <stdio.h>
int main()
{
        int i;
        for(i = 1; i < 10; i++) {
                printf("i = %d\n", i);
        }
        printf("Hello World\n");
}
```

## 查看变量值及运行状态

打印值： p i  
打印地址： p &i  
查看当前函数里面的变量值： inof lo / info local  
格式查看：p/a i  
    x  按十六进制格式显示变量。  
    d  按十进制格式显示变量。  
    u  按十六进制格式显示无符号整型。  
    o  按八进制格式显示变量。  
    t  按二进制格式显示变量。  
    a  按十六进制格式显示变量。  
    c  按字符格式显示变量。  
    f  按浮点数格式显示变量。  
查看寄存器的值： info registers  
修改运行时时的变量： print x=4  

## 查看堆栈

**查看当前堆栈信息**： bt  
查看当前堆栈其他位置的状态： f num  

## watch监控变量值

当要监控某一个变量值是在哪里被修改时，可以使用watch  

```shell
watch i
watch (int *)&i
```

## 强制调用函数

强制调用函数：call <expr>  

## 处理信号

很少用到

## 设置参数

set args 可指定运行时参数。（如：set args 10 20 30 40 50）  
show args 命令可以查看设置好的运行参数。  
