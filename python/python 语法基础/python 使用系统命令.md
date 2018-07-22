<!-- TOC -->

- [调用系统命令](#调用系统命令)
    - [参考链接](#参考链接)
    - [os.system("cmd")](#ossystemcmd)
    - [os.popen()](#ospopen)
    - [commands.getstatusoutput](#commandsgetstatusoutput)

<!-- /TOC -->

# 调用系统命令

## 参考链接

[参考链接](https://www.cnblogs.com/bergus/p/4811291.html)

## os.system("cmd")

该方法在调用完shell脚本后，返回一个16进制数，低位为杀死所调用脚本的信号号码，高位为脚本的退出状态码，即脚本中的exit 1的代码执行后，os.system函数返回值的高位数就是1，如果低位数是0的情况下，则函数返回的值是0x100，换算成十进制得到256。
要得到os.system返回值时，可以用>>8的位运算获取。**但是，这个命令不法获得返回信息**，示例os.system('ls')时，只能得到返回码，而获取不到ls的列表。

## os.popen()

实现方式是管道，函数返回一个file-like的对象，里面的内容是脚本输出的内容。  
**os.Popen()是阻塞的方法执行的，所以容易阻塞住**，解决的方法是不使用wait()方法，但是也不能获得执行的返回值了  

```shell
# 函数原型 subprocess.Popen(args, bufsize=0, executable=None, stdin=None, stdout=None, stderr=None, preexec_fn=None, close_fds=False, shell=false)
ret_str =  os.Popen('ls').readlines()
```

## commands.getstatusoutput

这个方法也不会打印出comd在linux上执行的信息，**优点是非阻塞的方法**  

```shell
status, output = commands.getstatusoutput("ls")  
commands.getoutput("ls")  
commands.getstatus("ls")
```