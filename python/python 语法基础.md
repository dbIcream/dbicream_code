<!-- TOC -->

- [语法](#语法)
    - [基础知识](#基础知识)
        - [添加语言支持](#添加语言支持)
        - [设置解析器](#设置解析器)
        - [执行python脚本](#执行python脚本)
        - [注释](#注释)
        - [多行语句](#多行语句)
        - [常见解析错误](#常见解析错误)
            - [IndentationError，格式错误](#indentationerror格式错误)
            - [KeyError: 'Alice'](#keyerror-alice)
    - [数据类型](#数据类型)
        - [查看数据的类型](#查看数据的类型)
        - [int整数](#int整数)
        - [bool布尔值](#bool布尔值)
        - [float浮点数](#float浮点数)
        - [complex复数](#complex复数)
        - [string字符串类型](#string字符串类型)
            - [显示字符串](#显示字符串)
        - [list列表](#list列表)
            - [字符串转成命令](#字符串转成命令)
            - [删除列表元素](#删除列表元素)
            - [列表操作函数](#列表操作函数)
            - [](#)
        - [tuple元组](#tuple元组)
        - [sets集合](#sets集合)
        - [dict字典](#dict字典)
            - [字典函数](#字典函数)
    - [运算符](#运算符)
        - [算术运算符](#算术运算符)
        - [比较运算符](#比较运算符)
        - [赋值运算符](#赋值运算符)
        - [位运算符](#位运算符)
        - [逻辑运算符](#逻辑运算符)
        - [成员运算符](#成员运算符)
        - [身份运算符](#身份运算符)
    - [输出](#输出)
        - [print()](#print)
            - [不输出换行](#不输出换行)
            - [字符串格式化](#字符串格式化)
            - [字符串拼接](#字符串拼接)
- [import导入模块](#import导入模块)
    - [模块部分导入/全部导入](#模块部分导入全部导入)
    - [调用模块](#调用模块)
    - [仅在该模块测试时使用](#仅在该模块测试时使用)
    - [package包导入](#package包导入)
    - [模块管理的内置函数](#模块管理的内置函数)
- [内嵌函数](#内嵌函数)
    - [数字函数](#数字函数)
    - [随机函数](#随机函数)
    - [字符串内建函数](#字符串内建函数)
- [迭代器和生成器](#迭代器和生成器)
    - [迭代器](#迭代器)
    - [生成器](#生成器)
        - [生成器函数](#生成器函数)
        - [生成器用于列表解析](#生成器用于列表解析)
- [函数](#函数)
        - [可变参数、不可变参数](#可变参数不可变参数)
        - [不定长参数](#不定长参数)
        - [存在不存在的key值时的容错](#存在不存在的key值时的容错)
        - [匿名函数](#匿名函数)
        - [参数作用域](#参数作用域)
- [文件IO](#文件io)
    - [普通文件文件读写](#普通文件文件读写)
    - [二进制文件pickle读写](#二进制文件pickle读写)
    - [读写的模式](#读写的模式)
    - [文件的内嵌函数](#文件的内嵌函数)
        - [读写](#读写)
        - [位置查找](#位置查找)
- [其他函数](#其他函数)
- [异常及异常捕获](#异常及异常捕获)
    - [使用系统异常](#使用系统异常)
    - [自定义异常](#自定义异常)
- [类](#类)
    - [定义类](#定义类)

<!-- /TOC -->
********************************************
# 语法
## 基础知识
### 添加语言支持
在文件首部添加编码支持，
```
# -*- coding: utf-8 -*-
```
### 设置解析器
```
#!/usr/bin/python
```

### 执行python脚本
通用启动方式： python a.py
配置了解析器时也可以使用的方法： ./a.py

### 注释
单行注释以#开始
多行注释用''' '''，或者""" """来包含
缩进统一用四个空格来代码tab键，可以将编辑器的tag替换成四个空格

### 多行语句
多行语句用\来放在上一行末尾，作为衔接

### 常见解析错误
#### IndentationError，格式错误
IndentationError: unindent does not match any outer indentation level
#### KeyError: 'Alice'
字典索引的key不匹配

## 数据类型
### 查看数据的类型
a = 111
查看类型type： print(type(a))
查看是不是某种类型： isinstance(a, int)，返回True/False
**type()不认为子类是父类的一种，isinstance()则认为**

### int整数
python3中没有long型
转换成整数： int(str1, 10)十进制,int(str2, 8)八进制
转成成十六进制的字符串： hex(100)，输出'0x64'，oct(x)八进制
将一个整数转换为一个字符: chr(x)
将一个字符转换为它的整数值: ord(x)


### bool布尔值
如： True False

### float浮点数

### complex复数
如： 1 + 2j， 1.1 + 2.2j
comp1 = complex(1, 2)

### string字符串类型
1、用'',"","""括起来的数据
2、用r来表示反斜杠不是代表转义生效，r'this is a line\n'，\n会显示，而不是换行
3、用*来表示重复输出多少次，如print('a'*8)输出aaaaaaaa
4、""" """多行字符串时，原样输出
5、Unicode字符串， u'this is string'

#### 显示字符串
str = 'abcdef'
输出完整字符串： print(str)
输出子串，从0到倒数最后一个字符串： print(str[0:-1])
输出子串，如果范围异常，返回空值： str[5:-5]


### list列表
输出完整列表： print(list1)
输出子列表，从0到倒数最后一个元素： print(list1[0:-1])
输出子列表，如果范围异常，返回空值： list1[5:-5]
**定义时使用[]**
#### 字符串转成命令
将对象x转换为表达式字符串： repr('1+1')，返回"'1+1'"
将字符串转成真实的表达式并计算出结果： eval('1+1')，返回2

#### 删除列表元素
del list1[2]
####  列表操作函数
append()
extend(seq), 用新列表扩展原来的列表
index()， insert(), pop(), remove(), reverse(), sort(), clear(), copy()

#### 

### tuple元组
输出方法同str和list，但是**tuple不可修改**
**定义时使用()**
单个元素时，要在元素后面加,，如tup = (20,)

### sets集合
集合是一个无序不重复元素的序列，如果添加了重复的元素，会自动去重
set()
student = {'stu1', 'stu2', 'stu3'}
集合可以进行，- | & ^操作、
将元素转成集合：frozenset(s)

### dict字典
字典是键值对，key必须是唯一的
dict = {}
dict['key1'] = 'value1'
输出所有的key： print(dict.keys())
输出所有的值：print(dict.values())

#### 字典函数
key_in_dict（）
```
#遍历字典：
knights = {'gallahad': 'the pure', 'robin': 'the brave'}
for k, v in knights.items():
    print(k, v)
```

****************************************************
## 运算符
优先级要注意的几个，is 高于 in 高于 and
### 算术运算符
```
+ - * / %
**幂
//取整除
```
### 比较运算符
== != > < >= <=

### 赋值运算符
= += -= *= /= %= **= //=

### 位运算符
& | ^ ~ << >>

### 逻辑运算符
and or not

### 成员运算符
in not in

### 身份运算符
is is not
相当于id(x) = id(y)

*********************************************************
## 输出
### print()
#### 不输出换行
print()默认输出字符串之后会换行，如果想不换行时，使用print(str, end='')，也可以用其他字符代替换行输出，如使用#号结尾时，print(str, end='#')
#### 字符串格式化
跟C语言的sprintf()基本相同
print('str = %s, float = %.2f' % ('python', 3.6))

#### 字符串拼接
print('str = {}, float = {}'.format('python', 3.6))
print('str = {0}, float = {1}'.format('python', 3.6))

******************************************************
# import导入模块

## 模块部分导入/全部导入
导入模块时，使用import或者from...import来导入相应的模块
整个模块导入时： import module
导入模块中的某个函数： from module import func1, func2, func3
导入某个模块中的全部函数： from module import *
模块名过长时，可以添加别名导入：import module as alias_name

## 调用模块
调用模块时，如果要使用模块里面的函数，要使用mymodule.func()来调用
```
import cyan_array
run_main = cyan_array.test_func()
```

## 仅在该模块测试时使用
如果仅想在本模块测试时使用某个特定的测试函数，而在被当前模块加载时不会被执行
```
if __name__ == '__main__':
    do_something()
```

## package包导入
文件夹下添加__init__.py文件就会被识别成包
导入包里面的模块方法：from mydir import mymodule，其中mydir是目录，mymodule是模块名，模块即对应一个mymodule.py文件
子目录下也有文件夹导入方法：from mytools.A improt mymodule2，或者import mytools.A.mymodule2
导入包里面的全部模块：from sound.effects import *

## 模块管理的内置函数
dir()：可以找到模块内定义的所有名称， dir(mymodule)


****************************************************
# 内嵌函数
## 数字函数
abs(x)
ceil(x)，返回上位函数，如ceil(4.1) 返回 5
floor(x)，返回上位函数，如ceil(4.1) 返回 4
max(), min()
round(x, n)四舍五入，保留小数点后N位

## 随机函数
choice(seq)，从序列中随机取一个数
randrange(start, stop, step)，从指定范围取随机数
random()，随机生成[0, 1)之间的数

## 字符串内建函数
capitalize()， 首字母大写
bytes.decode(encoding = 'utf-8', errors = 'strict')
encode(encoding = 'utf-8', errors = 'strict')
endswith(suffix, beg=0, end=len(string))
find(str, beg=0, end=len(string)), rfind()
isalnum(), isalpha(), islower(), isnumeric(), isupper(), isdecimal()是否只含有十进制字符串
join(seq), 用指定的字符串将所有元素串在一起并返回
lstrip(), rstrip(), strip(), 截掉前面的空格字符
**replace(old, new, max)，替换字符串**
**split(str="", num)，截取字符串**

************************************************************

# 迭代器和生成器
## 迭代器
用来访问集合、字符串、列表、元组
**只能前进，不能后退**
有两个基础方法，iter()和next()
```
list = [1, 2, 3, 4]
iterator1 = iter(list)
for value in iterator1:
    print(value, end = ' ')

iterator1 = iter(list)
while True:
    try:
        print (next(iterator1))
    except StopIteration:
        sys.exit()
```

## 生成器
使用了 yield 的函数被称为生成器，生成器是一个返回迭代器的函数，只能用于迭代操作，更简单点理解生成器就是一个迭代器。

虽然执行流程仍按函数的流程执行，但每执行到一个 yield 语句就会中断，并返回一个迭代值，下次执行时从 yield 的下一个语句继续执行。
看起来就好像一个函数在正常执行的过程中被 yield 中断了数次，每次中断都会通过 yield 返回当前的迭代值。
yield 的好处是显而易见的，把一个函数改写为一个 generator 就获得了迭代能力，
比起用类的实例保存状态来计算下一个 next() 的值，不仅代码简洁，而且执行流程异常清晰。
### 生成器函数

```
#生成器使用，使用fab.next()
def fab(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        # print b
        a, b = b, a + b
        n = n + 1
f = fab(5)
while True:
    try:
        print (next(f), end=" ")
    except StopIteration:
        sys.exit()
        pass
```
### 生成器用于列表解析
```
generator_35 = (i for i in range(1, 10) if (i % 3 == 0 or i % 5 == 0))

for i in generator_35:
    print(i)
```
列表解析
格式： 
    [expr for iter_var in itcrable]
    [expr for iter_var in itcrable if cond_expr]

# 函数
### 可变参数、不可变参数
不可变类型：类似 c++ 的值传递，如 整数、字符串、元组。如fun（a），传递的只是a的值，没有影响a对象本身。
可变类型：类似 c++ 的引用传递，如 列表，字典。
```
a = 10
l = [1, 2, 3]
def func1(a):
    a = 12  #a的值不会改变
def func2(l):
    l[0] = 10 #l[0]的值发生改变
```

### 不定长参数
存在可变长参数
```
def func1(a, b, *args, c):
    print('{},{},{}'.format(a, b, c))
    for value in args:
        print(value)
func1(1,2,3,4, c=5)
```
### 存在不存在的key值时的容错
```
# kv用来存储不同
def func2(p1 = "p1", p2 = "p2", *args, **kv):
    print("p1={0}, p2={1}".format(p1, p2))
    print("args={0}".format(args))
    print("kv={0}".format(kv))

p1 = "参数1"
p2 = "参数2"
p3 = "参数3"
func2(p1 = p1, p2 = p2, a='abc', b='cde', z = p3)
```

### 匿名函数
lambda 只是一个表达式，函数体比def简单很多
lambda 函数拥有自己的命名空间，且不能访问自己参数列表之外或全局命名空间里的参数。
语法就是一个表达式： lambda [arg1 [,arg2,.....argn]]:expression
```
num_list = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]
func1 = (lambda x: x % 3 == 0)
for i in num_list:
    func1(i)
print([x for x in num_list if x % 3 == 0])

#过滤一个序列，并返回过滤后的序列
print(filter(func1, num_list))
#将序列中的所有元素执行某个操作，并返回执行过后的序列
print(map(lambda x: x + 10, num_list))
print(reduce(lambda x,y: x + y, num_list))
```

### 参数作用域
nonlocal：外部非全局
global: 全局作用域
当函数内要使用全局变量时，要使用到global关键字
**全局变量的定义，最好是g_name定义**

*******************************************************
# 文件IO
## 普通文件文件读写
推荐使用with的方式打开，这样就不用怕忘记关闭了，否则一个open()都要对应一个close()
```
file_name = test.txt
with open(file_name) ad fd_test:    #open不加参数，默认是r只读模式
    # 按行读文件
    print(fd_test.readline(), end='')
    print(fd_test.readline()) 

    # 读所有文件
    for each_line in fd_test:
        print(each_line, end='')
#fd_test.close()

# 写文件
with open(self.out_file_name, 'w+') as fd_test: # 默认是r模式
    fd_test.write("first line\n")
    fd_test.write("second line\n")

```

## 二进制文件pickle读写
```
in_file = out_file = test.dat
a_list[]
with open(out_file, "wb") as outfile:
    pickle.dump([1, 2, 'three'], outfile)
    pickle.dump(['fee', 'fie', 'foe', 'fum'], outfile)
    pickle.dump(['12', '34', '56'], outfile)

with open(in_file, "rb") as infile:
    a_list = pickle.load(infile)
    print(a_list)
    a_list = pickle.load(infile)
    print(a_list)
    a_list = pickle.load(infile)
    print(a_list)
```

## 读写的模式
[参考链接](http://www.runoob.com/python3/python3-inputoutput.html)
r r+ rb rb+ w w+ wb wb+ a a+ ab+

## 文件的内嵌函数
file.flush(): 直接将缓存区的数据写入到文件
file.fileno(): 返回一个文件描述符

### 读写
read()： 读取全部
readLine()： 读取一行
readLines(num)：读取指定行数
file.truncate(size): 文件截断
file.write(str)： 写入字符串，写入长度为str的长度
file.writeLines(seq)：写入列表，**需要换行时，需要自己添加**

### 位置查找
file.seek(): 设置文件的位置,
f.seek(offset, from_what): 返回当前的位置
from_what 的值, 如果是 0 表示开头, 如果是 1 表示当前位置, 2 表示文件的结尾，例如：
seek(x,0) ： 从起始位置即文件首行首字符开始移动 x 个字符
seek(x,1) ： 表示从当前位置往后移动x个字符
seek(-x,2)：表示从文件的结尾往前移动x个字符

*********************************************************
 # os操作
 ## 常用的方法
[参考链接](http://www.runoob.com/python3/python3-os-file-methods.html)
os.access(path.mode): 权限验证
os.chdir(path): 改变当前的工作目录
os.chmod(path, mod): 更改权限
os.getcwd()
os.mkdir(path, mode)
os.rmdir(dir)：删除空目录
os.removedirs(dir)：递归删除目录

# 其他函数
os.fchmod(fd, mod)
os.chflags(path, flags):
os.chown(path, uid, gid), os.fchown(), os.fdatasync(fd)
os.chroot(path): 改变当前进程的根目录
os.close(), os.closerange(), os.dup(), os.dup2(fd, fd2), 

***************************************************

# 异常及异常捕获
## 使用系统异常
1、捕获异常，如果明确知道是什么类型的异常，可以直接获取该类型
2、捕获异常，如果不清楚异常类型，可以使用使用Exception来代替
3、获取全部异常，但是不处理时，只要except:也是可以的
4、如果捕获到异常，且异常要向上一层抛出的话，可以用raise()
5、如果没有捕获到异常时添加一些操作时，可以使用else:
6、如果是无论是不是异常都要执行时，可以使用finally:

```
try:
    do_somthing()
except errtype:
    print('some warning')
except Exception as err:
    print(err)
    raise()
#except:
#    print("common exception")
#else:
#   do_something()
#finally:
#   do_something()
#
```

## 自定义异常
```
class MyError(Exception):
    def __init__(self, value):
        self.value = value
    def __str__(self):
        return repr(self.value)
   
try:
    raise MyError(2*2)
except MyError as e:
    print('My exception occurred, value:', e.value)
```


******************************************************

# 类
## 定义类
1、建议命名，首字母大写
2、构造函数： __init__(self)，self后面可以跟其他参数
3、定义成员函数：def func(self), self是指身类的实例本身，**self必须添加**
4、继承时，直接在类后加父类名称，class Child_A(Father_A)
5、多继承时，注意函数查找的顺序，先找该类的方法，没有找到时从左到右去查找父类中的方法
6、重载函数
7、私有变量和私有方法，在变量/函数定义前加两个下划线，如__pri_name, __pri_func(self)
8、运算符重载，不展开，遇到再查资料吧


```
class Father_A():
    __init__(self):
        self.name = 'this is father class'
    def print_name(self):
        print(self.name)

class Child_A(Father_A):
    __init__(self):
        Father_A.__init__(self) #调用父的构造函数
        self.name = 'this is child class'
    def print_name(self):
        super()     #调用父类的方法
        print(self.name)
```