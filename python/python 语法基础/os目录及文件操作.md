<!-- TOC -->

- [文件操作](#文件操作)
    - [读写的模式](#读写的模式)
    - [文件的内嵌函数](#文件的内嵌函数)
    - [文件读写](#文件读写)
    - [位置查找](#位置查找)
    - [os文件夹操作](#os文件夹操作)

<!-- /TOC -->

# 文件操作

## 读写的模式

[参考链接](http://www.runoob.com/python3/python3-inputoutput.html)
r r+ rb rb+ w w+ wb wb+ a a+ ab+

## 文件的内嵌函数

file.flush(): 直接将缓存区的数据写入到文件
file.fileno(): 返回一个文件描述符

## 文件读写

read()： 读取全部
readLine()： 读取一行
readLines(num)：读取指定行数
file.truncate(size): 文件截断
file.write(str)： 写入字符串，写入长度为str的长度
file.writeLines(seq)：写入列表，**需要换行时，需要自己添加**

## 位置查找

f.seek(offset, from_what): 返回当前的位置 ，from_what 的值, 如果是 0 表示开头, 如果是 1 表示当前位置, 2 表示文件的结尾  
seek(x,0) ： 从起始位置即文件首行首字符开始移动 x 个字符  
seek(x,1) ： 表示从当前位置往后移动x个字符  
seek(-x,2)：表示从文件的结尾往前移动x个字符  

## os文件夹操作

os.access(path.mode): 权限验证  
os.chdir(path): 改变当前的工作目录  
os.chmod(path, mod): 更改权限  
os.getcwd()  
os.mkdir(path, mode)  
os.rmdir(dir)：删除空目录  
os.removedirs(dir)：递归删除目录  