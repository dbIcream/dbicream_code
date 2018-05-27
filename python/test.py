# -*- coding:utf-8 -*-
#!/usr/bin/python


'''
1、先指定要取文件的目录，以及要复制到机器的目标目录
2、取出所有的文件列表
3、登陆机器或者scp复制到另外一台机器上
4、

paramiko 基于SSH用于连接服务器并执行相关操作
pip install paramiko

'''

import paramiko
import os
import sys
import getopt
import time


class SSH_TOOLS(object):
    def __init__(self, ip, port, user, password):
        self.ip = ip
        self.port = port
        self.user = user
        self.password = password
    
    def connect(self):
        try:
            # 创建SSH对象
            self.ssh = paramiko.SSHClient()
            # 允许连接不在know_hosts文件中的主机
            self.ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            self.ssh.connect(self.ip, self.port, self.user, self.password)
            self.sftp = paramiko.SFTPClient.from_transport(self.ssh.get_transport())
            self.sftp = self.ssh.open_sftp()
            print('connect success!')
        except Exception as err:
            print('cannot connect to ' + self.ip + str(err))
    
    def upload_file(self, local_file, remote_file):
        try:
            self.sftp.put(local_file, remote_file)
            print(local_file + ' upload success')
        except Exception as e:
            print('upload error.' + str(e))
    
    def download_file(self, remote_file, local_file):
        try:
            self.sftp.get(remote_file, local_file)
            print(remote_file + ' download success')
        except Exception as e:
            print('download_file error.' + str(e))
        
    def close(self):
        self.ssh.close()
        print('close connection!')
    
    def cmd(self, command):
        # 执行命令
        stdin, stdout, stderr = self.ssh.exec_command(command)
        # 获取命令结果
        result = stdout.read()
        print(result)
        return result

    
def usage():
    print('''
    -h : help
    -ip : ip
    -p/-port : port
    ''')


# python test.py --password=package_maa_6.5 --src-file=test.py --dst-file=/home/caiyx/test.py

if __name__ == '__main__':
    # 脚本名：sys.argv[0]
    # 参数1： sys.argv[1]
    # 参数2： sys.argv[2]
    # h表示开关选项，p:表示后面要跟一个附加参数,ip=表示--ip='10'
    print(sys.argv[1:])
    opts, args = getopt.getopt(sys.argv[1:], 'hr:p:',
                    ['ip=', 'port=', 'user=', 'password=', \
                     'src-file=', 'dst-file=', 'src-dir=', 'dst-dir='])
    
    ip = '10.8.204.144'
    port = 63501
    user = 'root'
    password = ''
    src_file = ''
    dst_file = ''
    src_dir = ''
    dst_dir = ''

    #获取到参数
    try:
        for op, value in opts:
            if op == '-h':
                usage()
                sys.exit()
            elif op == '--ip':
                ip = value
                print('set ip = {}'.format(value))
            elif op == '-p' or op == '--port':
                port = int(value)
                print('set port = {}'.format(value))
                
            elif op == '--user':
                user = value
                print('set user = {}'.format(value))
            elif op == '--password':
                password = value
                print('set password = {}'.format(value))
                
            elif op == '--src-file':
                src_file = value
                print('set src-file = {}'.format(value))
            elif op == '--dst-file':
                dst_file = value
                print('set dst-file = {}'.format(value))
            elif op == '--src-dir':
                src_dir = value
                print('set src_dir = {}'.format(value))
            elif op == '--dst-dir':
                dst_dir = value
                print('set dst_dir = {}'.format(value))
            else:
                print('unsupport opt:{}'.format(op))
    except Exception as err:
        print('param error!\n' + str(err))
        sys.exit()  

    if password == '':
        print('password is empty!')
        sys.exit() 
    if (src_file == '' and src_dir == '') or \
        (dst_dir == '' and dst_file == ''):
        print('src or dst is empty!')
        sys.exit()
    
    ssh_tools = SSH_TOOLS(ip, port, user, password)
    ssh_tools.connect()
    ssh_tools.upload_file(src_file, dst_file)
    ssh_tools.close()




