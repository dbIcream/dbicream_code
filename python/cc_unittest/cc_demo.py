# -*- coding:utf-8 -*-
#!/usr/local/bin/python3


import unittest

class TestDemo():
    def __init__(self, config_file):
        self.config_file = config_file

    '''设置配置文件'''
    def set_config(self, config_file):
        self.config_file = config_file

    '''启动程序，启动前必须指定正确的配置文件'''
    def start_demo(self):
        return False
    
    ''''''
    def do_get_visit(self, url, header={}):
        return False
    
    ''''''
    def do_post_vist(self, url, header={}):
        return False
    
    ''''''
    def do_purge_vist(self, url, header={}):
        return False
    
    ''''''
    def check_access_log(self, str):
        return False

    ''''''
    def check_cache_log(self, **kv):
        if len(kv) != 0:
            for k in kv.keys():
                print('key:{}, value:{}'.format(k, kv[k]))
        return False