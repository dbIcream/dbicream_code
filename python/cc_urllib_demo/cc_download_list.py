#!/usr/bin/python
#coding=utf-8

'''
======================================================
Author:        xiao_cc 
Date:          2018.04.30
Description:   下载list里面的url到指定文件
    1、先确保要保存的url路径是存在的
    2、获取到list中的每个url，解析出文件名
    3、将url下载保存到目录下，文件名为2中解析出的文件名
    
======================================================

'''

import os
import urllib
from urllib import request
import threading
import time
from cc_path import cc_path
from cc_log import cc_log


logger = cc_log.get_default_logger()

url_list = (
    'http://scimg.158pic.com/allimg/180423/2-1P423153R5141.jpg',
    'http://scimg.158pic.com/allimg/180423/2-1P423153R5141.jpg',
    'http://scimg.158pic.com/allimg/180423/2-1P423153R5141.jpg',
)

def save_url_to_path(url, path):
    global logger
    urllib.request.urlretrieve(url, path)  # 获取网络资源到本地
    logger.info('{0} downloaded!!'.format(url))
    
    
def download_and_save_list(url_list):
    global logger
    
    #先确保保存的文件目录存在
    save_dir = 'C:\\Users\\caiyx1\\Desktop\\aa\\bb\\cc'
    cc_path.create_dir(save_dir)
        
    for i in range(len(url_list)):
        try:
            #获取到url中的文件名
            split_list = url_list[i].split('/')
            filename = split_list[len(split_list) - 1]
            file_path = os.path.join(save_dir, filename)
            
            #判断文件是否已经下载过了，已经存在过就不再下载，不考虑上次下载不完整
            if (os.path.exists(file_path)):
                logger.info('%s is already exists, downloading next file...' % filename)
                continue
    
            logger.info('start to download: %s'.format(url_list[i]))
            logger.info('saved path: %s'.format(file_path))
    
            #开线程来下载
            t = threading.Thread(target=save_url_to_path, args=(url_list[i], file_path,))
            t.start()
            time.sleep(5)
        except Exception as err:
            logger.error('save error, error msg: {0}'.format(err))
            continue
    

download_and_save_list(url_list)






