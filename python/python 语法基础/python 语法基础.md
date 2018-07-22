<!-- TOC -->

- [python](#python)
    - [执行python脚本](#执行python脚本)
    - [注释](#注释)
    - [编写方格](#编写方格)
    - [常见的执行错误](#常见的执行错误)
    - [添加语言支持和解析器](#添加语言支持和解析器)
    - [模块部分导入/全部导入](#模块部分导入全部导入)
    - [package包导入](#package包导入)
    - [模块管理的内置函数](#模块管理的内置函数)
    - [数据类型判断](#数据类型判断)
    - [数据类型转换](#数据类型转换)
    - [查看某个属性是否为类的成员属性](#查看某个属性是否为类的成员属性)
    - [数值类型](#数值类型)
    - [string字符串类型](#string字符串类型)
        - [将字符串当成表达式](#将字符串当成表达式)
        - [字符串拼接](#字符串拼接)
    - [list列表](#list列表)
    - [tuple元组](#tuple元组)
    - [sets集合](#sets集合)
    - [dict字典](#dict字典)
    - [运算符](#运算符)
    - [随机函数](#随机函数)
    - [参数作用域](#参数作用域)

<!-- /TOC -->

# python

## 执行python脚本

- 通用启动方式： python a.py
- 直接执行： ./a.py 前提是配置了解析器时

## 注释

- 单行注释： 以#开始
- 多行注释用''' '''，或者""" """来包含

##　编写方格

- 缩进统一用四个空格。　可以将编辑器的tag替换成四个空格
- 多行语句用\来放在上一行末尾，作为衔接

## 常见的执行错误

- IndentationError，缩进格式错误。 IndentationError: unindent does not match any outer indentation level
- KeyError: 'Alice'。 字典索引的key不匹配

## 添加语言支持和解析器

```shell
# 在文件首部添加文档编码说明，并设置python解析器的路径
#!/usr/bin/python
# -*- coding: utf-8 -*-
```

## 模块部分导入/全部导入

整个模块导入时： import module  
导入模块中的某个函数： from module import func1, func2, func3  
模块名过长时，可以添加别名导入：import module as alias_name  
使用模块： run_main = cyan_array.test_func()  
仅在该模块测试时使用： if __name__ == '__main__': do_something()

## package包导入

文件夹下添加__init__.py文件就会被识别成包  
导入包里面的模块方法：from mydir import mymodule，其中mydir是目录，mymodule是模块名，模块即对应一个mymodule.py文件  
子目录下也有文件夹导入方法：from mytools.A improt mymodule2，或者import mytools.A.mymodule2  
导入包里面的全部模块：from sound.effects import *  

## 模块管理的内置函数

dir()：可以找到模块内定义的所有名称， dir(mymodule)

## 数据类型判断

- 查看数据类型： type() 显示当前的数据类型，如type(a)
- 判断是不是某种类型： isinstance(a, int)，返回True/False
- **type()不认为子类是父类的一种，isinstance()则认为**

##　数据类型转换

- 转换成十进制整数： a =  int(str1, 10)
- 转换成八进制整数： a =  int(str1, 8)
- 转换成十六进制的字符串： str1 = hex(100)
- 转换成八进制的字符串： str1 = hex(100)
- 将一个整数转换为一个字符： ch = chr(x)
- 将一个字符转换为它的整数值: a = ord(x)  

## 查看某个属性是否为类的成员属性

- dir(obj), 返回成员属性的列表，如dir(request)
- hasattr(obj, attr)，如hasattr(request, 'url')
- getattr(obj, attr), 获取成员属性的值，如getattr(request, 'url')
- setattr(obj, attr),设置某个属性的值

## 数值类型

- int整数： python3中没有long型
- bool布尔值： True/False 区分大小写，要首字母大写
- float浮点数
- complex复数： 如： 1 + 2j， 1.1 + 2.2j , comp1 = complex(1, 2)  

## string字符串类型

- 用'', "", """括起来的数据， 比较常使用的是单引号。 """ """多行字符串时，原样输出
- 用r来表示反斜杠不是代表转义不生效，r'this is a line\n'，\n会显示，而不是换行
- 用*来表示重复输出多少次，如print('a'*8)输出aaaaaaaa
- Unicode字符串， u'this is string'
- 输出子串，从0到倒数最后一个字符串： print(str[0:-1])， -1表示倒数第二位
- 输出子串，如果范围异常，返回空值： str[5:-5]

### 将字符串当成表达式

- 将对象x转换为表达式字符串： repr('1+1')，返回"'1+1'"
- 将字符串转成真实的表达式并计算出结果： eval('1+1')，返回2

### 字符串拼接

print('str = {}, float = {}'.format('python', 3.6))
print('str = {0}, float = {1}'.format('python', 3.6))

## list列表

- 删除列表元素： del list1[2]

## tuple元组

- tuple不可修改, 单个元素时，要在元素后面加,，如tup = (20,)

## sets集合

集合是一个无序不重复元素的序列，如果添加了重复的元素，会自动去重
set()
student = {'stu1', 'stu2', 'stu3'}
集合可以进行，- | & ^操作、
将元素转成集合：frozenset(s)

## dict字典

- 取值： dict['key1'] = 'value1' 值不存在时会抛出异常
- 查看key是否存在： key_in_dict（）
- 遍历字典：for k, v in knights.items(): print(k, v)

## 运算符

- is
- in, not in
- and
- 取整除: //
- 幂： **
- 逻辑运算符: and or not

****************************************************

## 随机函数

choice(seq)，从序列中随机取一个数  
randrange(start, stop, step)，从指定范围取随机数  
random()，随机生成[0, 1)之间的数  

## 参数作用域

nonlocal：外部非全局  
global: 全局作用域  
当函数内要使用全局变量时，要使用到global关键字  
