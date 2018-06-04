<!-- TOC -->

- [ssh使用说明](#ssh使用说明)
    - [使用到的库](#使用到的库)
    - [ssh连接的基础信息](#ssh连接的基础信息)
    - [上传的服务器目录必须存在](#上传的服务器目录必须存在)
    - [ssh的接口](#ssh的接口)
        - [创建ssh对象](#创建ssh对象)
        - [连接](#连接)
            - [隐藏密码](#隐藏密码)
        - [sftp上传和下载](#sftp上传和下载)
            - [上传](#上传)
            - [下载](#下载)
        - [执行命令](#执行命令)
            - [输入数据](#输入数据)
            - [读取命令返回](#读取命令返回)
        - [关闭连接](#关闭连接)

<!-- /TOC -->

# ssh使用说明
## 使用到的库
- paramiko, 专门用来处理ssh登陆和上传的库

## ssh连接的基础信息
- ip,port, 要上传的服务器ip和ssh端口
- user,password 要上传的服务器的用户密码
- src_file,dst_file, 要上传的文件和上传到服务器的哪个文件

## 上传的服务器目录必须存在
假设我们要将to.md文件上传到服务器的/home/xxx/save_dir/save_file，这个时候我们要保证save_dir必须，否则会报错。

## ssh的接口
### 创建ssh对象
```
# 创建SSH对象
ssh = paramiko.SSHClient()
# 允许连接不在know_hosts文件中的主机
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
```

### 连接
```
ssh.connect(ip, port, user, password)
sftp = paramiko.SFTPClient.from_transport(ssh.get_transport())
sftp = ssh.open_sftp()
```
#### 隐藏密码
[参考链接](https://blog.csdn.net/y2701310012/article/details/41855171)  
如果不想每次输入时，可以参考

### sftp上传和下载
sftp只支持单个文件  
#### 上传
```
sftp.put(src_file, dst_file)
```
#### 下载
```
sftp.get(remote_file, local_file)
```
### 执行命令
```
# 执行命令
stdin, stdout, stderr = ssh.exec_command(command)
# 获取命令结果
result = stdout.read() #bytes
print(result)
```
#### 输入数据
stdin.write()  
```
ssh.connect('127.0.0.1', username='jesse', password='lol')  
stdin, stdout, stderr = ssh.exec_command("sudo fdisk -l")  
stdin.write('lol\n')  
stdin.flush()  
```

#### 读取命令返回
```
read()
readline()
readlines()
```

### 关闭连接
```
ssh.close()
```