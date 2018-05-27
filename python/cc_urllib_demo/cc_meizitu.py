#!/usr/bin/python
# -*- coding: UTF-8 -*-
'''
    文件名称：
    文件描述：
        脚本实现自动抓取图片网站上的图片：http://www.mzitu.com/all
    设计：
        1、构造请求获取http://www.mzitu.com/all内容
        2、从all的内容中解析出第一页的图片主题
        3、从第一个主题中去下载对应主题下的所有图片
        4、将下载下来的图片保存到指定目录
        
    说明：
        库安装：
        pip install lxml
        pip install beautifulsoup4
'''

import requests
from bs4 import BeautifulSoup
import os
import traceback
import threading
import time

class DownLoadMeizitu():
    def __init__(self):
        #UA头，源站有校验图片的UA，所以需要伪造UA头
        self.headers = {'User-Agent': "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/535.24 (KHTML, like Gecko) Chrome/19.0.1055.1 Safari/535.24"}

        #默认的保存目录
        self.base_save_dir = "E:\python_code\Download\mzitu"

    '''
        函数功能：保证保存目录存在，当保存目录不存在时，通过创建多级目录的方式创建该目录
    '''
    def create_save_dir(self):
        isExists = os.path.exists(self.base_save_dir)
        if not isExists:
            os.makedirs(self.base_save_dir)
            print("创建文件夹：" + self.base_save_dir)
        else:
            print(self.base_save_dir + "文件夹已经存在了！")

    '''
        函数功能：在保存目录下创建新的目录
    '''
    def create_new_dir(self, path): ##这个函数创建文件夹
        path = path.strip()
        isExists = os.path.exists(os.path.join(self.base_save_dir, path))
        if not isExists:
            print("创建文件夹：" + path)
            os.makedirs(os.path.join(self.base_save_dir, path))
            os.chdir(os.path.join(self.base_save_dir, path)) ##切换到目录
            return True
        else:
            print(path + "文件夹已经存在了！")
            return False

    def start_to_download(self, url):
        self.create_save_dir()
        self.download_all_url(url)


    def get_request_html(self, url): ##这个函数获取网页的response 然后返回
        content = requests.get(url, headers=self.headers)
        return content

    '''
        函数功能：下载并保存url对应的图片
    '''
    def save_img(self, url): ##这个函数处理图片页面地址获得图片的实际地址
        img_html = self.get_request_html(url)
        img_url = BeautifulSoup(img_html.text, 'lxml').find('div', class_='main-image').find('img')['src']
        name = img_url[-9:-4]
        img = self.get_request_html(img_url)
        with open(name + '.jpg', "ab") as outfile:
            outfile.write(img.content)

    '''
        函数功能：下载每个主题的所有图片
    '''
    def download_all_theme_picture(self, url):   ##这个函数是处理套图地址获得图片的页面地址
        print("download_all_theme_picture: " + url)
        html = self.get_request_html(url)
        self.headers['referer'] = url
        max_span = BeautifulSoup(html.text, 'lxml').find('div', class_='pagenavi').find_all('span')[-2].get_text()
        for page in range(1, int(max_span) + 1):
            page_url = url + '/' + str(page)
            self.save_img(page_url) ##调用img函数

    def download_all_url(self, url):
        html = self.get_request_html(url)##调用request函数把套图地址传进去会返回给我们一个response
        all_a = BeautifulSoup(html.text, 'lxml').find('div', class_='all').find_all('a')
        first_flag = 1
        for a in all_a:
            if (first_flag):
                first_flag = 0
                continue
            title = a.get_text()

            #开始下载主题
            pic_theme = str(title).replace("?", '_')
            print("开始保存主题的图片：" + pic_theme)
            href = a['href']

            #使用序号来作为文件夹的名称，这样不会因为分组名称出错而导致程序崩溃
            url_layer_list = href.split('/')
            dir_new_created_flags = self.create_new_dir(url_layer_list[len(url_layer_list) - 1])
            if (dir_new_created_flags == False ):
                print("download_all_url: 该主题已存在！")
                continue

            try:
                print("download_all_url: downloding..." + href)
                #self.download_all_theme_picture(href)
                #通过线程启动下载函数，有_thread和threading两种方式
                #_thread.start_new_thread(self.download_all_theme_picture, (href))
                t = threading.Thread(target=self.download_all_theme_picture, args=(href,))
                t.start()
                time.sleep(2)
            except:
                print("download_all_url: " + href + "-->download Fail!")
                traceback.print_exc()
            print("download_all_url: main process end!")

Mzitu = DownLoadMeizitu() ##实例化
Mzitu.start_to_download('http://www.mzitu.com/all')

