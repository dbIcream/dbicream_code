#!/usr/bin/python
# -*- coding: UTF-8 -*-


'''
pip的安装使用
不需要安装，在python的安装目录下找到Scripts，并添加到系统变量，就可以使用如：D:\Env\python-3.6.2\Scripts
使用requests模块：http://blog.csdn.net/shanzhizi/article/details/50903748
python3.5使用beautifulsoup4使用lxml解析库报错？  https://www.zhihu.com/question/49221958/answer/115712155

pip install lxml
pip install beautifulsoup4
pip install html5lib
如果pip直接装lxml不行的话，lxml安装的方法：http://blog.csdn.net/yueyuedabaobei/article/details/68491461
soup的使用介绍：http://cuiqingcai.com/1319.html

======================================================================
文档说明：
    文件名：express.py
    简述：输入快递单号，查找并显示出快递的物流情况
    设计：
        1、通过快递100的接口查询：http://www.kuaidi100.com/?from=openv
        2、
======================================================================
'''

import requests

class SIMPLE_EXPRESS:
    def __init__(self):
        self.param = {}

    # 函数: 承运公司名到文本
    def GetComName(self, comCode):
        if comCode == 'shentong':
            return '申通快递'
        elif comCode == 'zhontong':
            return '中通快递'
        elif comCode == 'ems':
            return 'EMS'
        elif comCode == 'huitongkuaidi':
            return '汇通快运'
        elif comCode == 'yuantong':
            return "圆通"
        else:
            return comCode

    # 函数: 获取到取状态文本
    def GetStateText(self, num):
        if num==0:
            return '运输中'
        elif num==1:
            return '揽件'
        elif num==2:
            return '疑难'
        elif num==3:
            return '已签收'
        elif num==4:
            return '退回签收'
        elif num==5:
            return '派送中'
        elif num==6:
            return '退回中'

    #获取到用户输入的信息
    def get_user_input(self):
        #in_str = input("请输入快递运单编号: ")  #比如: 813401221774
        #self.param['text'] = "resultv2=1&text={}".format(in_str)
        self.express_num = "813401221774"
        self.param['text'] = "resultv2=1&text=" + self.express_num

    def is_express_legal(self):
        autoComNum = requests.get("http://www.kuaidi100.com/autonumber/autoComNum", params=self.param)
        self.com = autoComNum.json()
        if self.com['auto'] == []:
            print("这是一个错误的运单编号!")
            return False
        return True

    def do_analyse_com(self):
        #print(self.com)
        com_code = ""
        for this in self.com['auto']:
            com_code = this['comCode']
            print("承运公司:" + self.GetComName(com_code))

        #构造查询队列
        data = {}
        data['type'] = com_code
        data['postid'] = self.express_num
        #data['temp'] = '0.2922539343671937'        #temp参数非必须

        #查询快递具体物流信息状态
        query = requests.get("http://www.kuaidi100.com/query", params=data)
        res = query.json()
        print(res)
        print("运单编号:" + res['nu'])
        print("承运公司:" + self.GetComName(res['com']))
        print("当前状态:" + self.GetStateText(int(res['state'])))
        print("---------------- 跟踪信息 ------------------")
        for this in res['data']:
            print(this['time'] + "\t" + this['context'])

    def search(self):
        self.get_user_input()
        if (self.is_express_legal() == True):
            self.do_analyse_com()


simple_search_express = SIMPLE_EXPRESS()
simple_search_express.search()