# -*- coding:utf-8 -*-
#!/usr/local/bin/python3


'''
1、先指定要取文件的目录，以及要复制到机器的目标目录
2、取出所有的文件列表
3、登陆机器或者scp复制到另外一台机器上
4、

paramiko 基于SSH用于连接服务器并执行相关操作
pip install paramiko
或者： pip3 install paramiko
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

'''
@fuction: copy src-file from current machine to remote server
@param: dict of scp base data
    dict must has key: ip, port, user, password, src-file, dst-file
@return: 
    True: copy success 
    False: copy failed
'''
def ssh_copy_file(ssh_info):
    # 脚本名：sys.argv[0]
    # 参数1： sys.argv[1]
    # 参数2： sys.argv[2]
    # h表示开关选项，p:表示后面要跟一个附加参数,ip=表示--ip='10'
    if isinstance(ssh_info, dict) == False:
        print('ssh_copy_file: param error!')
        return False
    
    key_list = ssh_info.keys()
    if 'ip' not in key_list or \
            'port' not in key_list or \
            'user' not in key_list or \
            'password' not in key_list or \
            'src_file' not in key_list or \
            'dst_file' not in key_list:
        print('ssh_copy_file: for lack of some key')
        return False
    if os.path.exists(ssh_info['src_file']) == False:
        print('ssh_copy_file: src_file:{0} is not exits'.format(ssh_info['src_file']))
        return False
    try:
        ssh_tools = SSH_TOOLS(ssh_info['ip'], ssh_info['port'],\
                ssh_info['user'] , ssh_info['password'])
        ssh_tools.connect()
        ssh_tools.upload_file(ssh_info['src_file'], ssh_info['dst_file'])
        ssh_tools.close()
    except Exception as err:
        print('ssh_copy_file: some err occur' + str(err))
        return False
    return True


def test_main():
    ssh_info_dict = {}
    ssh_info_dict['ip'] = '10.10.10.10'
    ssh_info_dict['port'] = 22
    ssh_info_dict['user'] = 'root'
    ssh_info_dict['password'] = 'password'
    ssh_info_dict['src_file'] = 'to.md'
    ssh_info_dict['dst_file'] = '/home/xxx/to.md'
    ssh_copy_file(ssh_info_dict)


def usage():
    print('''
    -h : help
    -ip : ip
    -p/--port= : port
    --user= :user
    --password= :password
    --src-file= :srcfile
    --dst-file= :dstfile
    ''')
# python3 test.py --password=password --ip=10.10.10.10 --port=22 --user=root --src-file=test.py --dst-file=/home/xxx/test.py
if __name__ == '__main__':
    ssh_info_dict = {}
    #print(sys.argv[1:])
    opts, args = getopt.getopt(sys.argv[1:], 'hr:p:',
                    ['ip=', 'port=', 'user=', 'password=', \
                        'src-file=', 'dst-file='])
    #获取到参数
    try:
        for op, value in opts:
            if op == '-h':
                usage()
                sys.exit()
            elif op == '--ip':
                ssh_info_dict['ip'] = value
                print('set ip = {}'.format(value))
            elif op == '-p' or op == '--port':
                ssh_info_dict['port'] = int(value)
                print('set port = {}'.format(value))  
            elif op == '--user':
                ssh_info_dict['user'] = value
                print('set user = {}'.format(value))
            elif op == '--password':
                ssh_info_dict['password'] = value
                print('set password = {}'.format(value))
                
            elif op == '--src-file':
                ssh_info_dict['src_file'] = value
                print('set src-file = {}'.format(value))
            elif op == '--dst-file':
                ssh_info_dict['dst_file'] = value
                print('set dst-file = {}'.format(value))
            else:
                print('unsupport opt:{}'.format(op))
    except Exception as err:
        print('param err    or!\n' + str(err))
        sys.exit()
    ## start to copy
    ssh_copy_file(ssh_info_dict)




