'''
@date: Created on 2018年4月28日
@author: caiyx1
'''
import os
from _overlapped import NULL

def show_help():
    str = '''
    create_dir: 创建目录，如果是多层的目录，逐级创建上一级目录
    create_file: 创建文件，如果文件已经存在则不再创建；如果文件不存在，则新建对应目录，然后再新建文件
    get_filelist：获取到当前目录下的文件列表，不包含子目录
    get_all_file：获取到当前目录下的文件列表，包含子目录
    '''
    print(str)

'''
如果目录不存在时，创建对应的目录
'''
def create_dir(new_dir):
    sub_dir = os.path.dirname(new_dir)  #获取到上一级目录
    if not os.path.exists(sub_dir):     #上一级目录不存在时，递归创建上一级目录
        print('mkdir: {0}'.format(sub_dir))
        create_dir(sub_dir)      #先创建上一级目录
        os.mkdir(new_dir)        #再创建当前目录
    else:
        os.mkdir(new_dir)        #上一级目录存在时，直接创建新目录
        print('mkdir: {0}'.format(new_dir))


'''
创建文件，如果文件已经存在则不再创建；如果文件不存在，则新建对应目录，然后再新建文件
'''
def create_file(file_name):
    if not os.path.exists(file_name):   #文件不慧时才创建
        sub_dir = os.path.dirname(file_name) #获取到上一级的目录
        if not sub_dir: #上一级不是目录时，且文件已经存在
            return
        
        if not os.path.exists(sub_dir): #目录不存在时
            print('mkdir: {0}'.format(sub_dir))
            create_dir(sub_dir)
        
        #os.mknod(file_name) #linux下使用
        #创建文件，windows下没办法直接创建，只好用open来创建
        with open(file_name, 'a') as fd_tmp:
            print('touch file: {0}'.format(file_name))
            pass
    else:
        print('file is already exists!')
        


'''
获取到一个目录下的所有文件，不包含子目录下的文件
'''
def get_filelist(inquiry_dir):
    if not os.path.isdir(inquiry_dir):
        return []
    
    all_device = os.listdir(inquiry_dir) #返回目录下的所有文件/目录列表
    file_list = []               #有效的文件列表
    
    for each_file in all_device:
        if os.path.isfile(os.path.join(inquiry_dir, each_file)):
            file_list.append(each_file)   # 添加文件
    return file_list
'''
获取到一个目录下的所有文件，包含子目录下的文件
'''
def get_all_file(inquiry_dir):
    if not os.path.isdir(inquiry_dir):
        return []
    
    all_device = os.listdir(inquiry_dir) #返回目录下的所有文件/目录列表
    file_list = []               #有效的文件列表
    
    for each_file in all_device:
        full_path = os.path.join(inquiry_dir, each_file)
        if os.path.isfile(full_path):
            file_list.append(each_file)   #添加文件
        elif os.path.isdir(full_path):
            file_list += get_filelist(full_path) #添加子目录
    return file_list


if __name__ == '__main__':
    pass






