'''
@date: Created on 2018年4月28日
@author: caiyx1
@function:开发一个日志系统， 既要把日志输出到控制台， 还要写入日志文件
@statement
    外部使用示例
    logger = cc_log.CC_Log(log_file).get_log()
    logger.debug('some data')
'''

import logging
import os

class CC_Log(object):
    '''
    指定保存日志的文件路径，日志级别，以及调用文件,将日志存入到指定的文件中
    '''
    def __init__(self, log_file, log_name = 'cc_log', log_level=logging.DEBUG):
        # 创建一个logger
        self.logger = logging.getLogger(log_name)
        self.logger.setLevel(logging.DEBUG)
        
        #定义handler的输出格式
        formatter = logging.Formatter('%(asctime)s [%(levelname)s]: %(message)s')

        #创建一个handler，用于输出到控制台
        ctrl_handler = logging.StreamHandler()
        ctrl_handler.setLevel(log_level)
        ctrl_handler.setFormatter(formatter) #设置输出格式
        self.logger.addHandler(ctrl_handler) #给logger添加handler
        
        # 创建一个handler，用于写入日志文件
        file_handler = logging.FileHandler(log_file)
        file_handler.setLevel(log_level)
        file_handler.setFormatter(formatter)
        self.logger.addHandler(file_handler) #给logger添加handler
        
    def get_log(self):
        return self.logger
    

if __name__ == '__main__':
    logger = CC_Log(log_file='debug.log').get_log()
    logger.info('foorbar')
    
    
        