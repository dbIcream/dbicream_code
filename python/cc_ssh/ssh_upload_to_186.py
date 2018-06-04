# -*- coding:utf-8 -*-
#!/usr/local/bin/python3

import cc_ssh
import sys
import os
import getopt


ssh_info_dict = {}
ssh_info_dict['ip'] = '10.10.10.10'
ssh_info_dict['port'] = 22
ssh_info_dict['user'] = 'XXX'
ssh_info_dict['password'] = 'password'
ssh_info_dict['src_file'] = ''
ssh_info_dict['dst_file'] = ''
base_dir = '/data/DIR/'

def usage():
    print('''usage: 
    -h : help
    -ip : ip
    --src-file=: src-file，locate file
    -m/--module= :module-name，like DIR_1/DIR_2
    example: python3 /home/XXX/python/ssh_186/ssh_upload_to_186.py --src-file=build/x86_64/DIR_1.rpm  --module=DIR_1
    ''')

# python ssh_upload_to_186.py --src-file=DIR_1.rpm  --module=DIR_1
if __name__ == '__main__':
    opts, args = getopt.getopt(sys.argv[1:], 'hm:',\
        ['src-file=', 'module='])
    module = ''
    base_name = ''
    dst_file_format = '{}/{}/{}' #base_dir/mudule/filename
    #print(sys.argv[1:])
    try:
        for op, value in opts:
            #print('op={0},value={1}'.format(op, value))
            if op == '-h':
                usage()
                sys.exit()
            elif op == '-m' or op == '--module':
                module = value
                print('set module = {}'.format(value))
            elif op == '--src-file':
                ssh_info_dict['src_file'] = value
                print('set src-file = {}'.format(value))
            else:
                print('unsupport opt:{}'.format(op))
    except Exception as err:
        print('param parse err, err={}'.format(str(err)))
        usage()
        sys.exit()

    src_file = ssh_info_dict['src_file']
    if src_file == '':
        print('src_file is null')
        usage()
        exit()
    else:
        base_name = os.path.basename(src_file)
    
    module_valid = False
    if module == '':
        print('mudule must has value')
    elif module == 'DIR_1' or \
           module == 'DIR_3' or \
           module == 'DIR_2' or \
           module == 'DIR_4' or \
           module == 'DIR_5' :
        module_valid = True
    
    if module_valid == False:
        usage()
        sys.exit()
    ssh_info_dict['dst_file'] = os.path.join(base_dir, module, base_name)
    print('dst file=' + ssh_info_dict['dst_file'])
    
    # start to copy
    cc_ssh.ssh_copy_file(ssh_info_dict)