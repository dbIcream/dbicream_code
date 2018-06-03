# -*- coding: utf-8 -*-
#!/usr/local/bin/python3

import requests
import urllib
import os
import sys
from bs4 import BeautifulSoup
import lxml
import threading
import time
import re

try:
    # analyze page of http://www.mzitu.com/all
    url_of_all = 'http://www.mzitu.com/all'
    custome_headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/535.24 (KHTML, like Gecko) Chrome/19.0.1055.1 Safari/535.24'}
    resp = requests.get(url_of_all, headers = custome_headers)
    content = resp.content
    # print(content)
except Exception as err:
    print('get page of all err, msg:' + str(err))

# 使用BeautifulSoup得到BeautifulSoup对象
soup = BeautifulSoup(content, 'lxml')
# 获取到年的节点位置，因为year和arch是两个并列书写，所以不好同时获取
arch_tags = soup.find_all('ul', 'archives')
# print(arch_tags)

year_attrs = []
each_year_attr = []
each_month_attrs = []
first_flag = True
for each_arch_tag in arch_tags:
    # 获取到月的节点位置
    # print(each_arch_tag)
    each_year_attr = []
    month_tags = each_arch_tag.find_all('p', re.compile('month|url'))
    if month_tags == None:
        continue
    # print(month_tags)
    for each_month_tag in month_tags:
        # print(each_month_tag)
        if each_month_tag == None:
            continue
        if 'month' in each_month_tag['class']:
            if first_flag == True:
                each_month_attrs = []
                first_flag = False
            else:
                # print(each_month_attrs)
                each_year_attr.append(each_month_attrs)
                each_month_attrs = []
        # 获取到月下面的<a href="">的所有链接
        a_tags = each_month_tag.find_all('a')
        # print(a_tags)

        for each_tag in a_tags:
            # print(each_tag)
            each_url = {}
            each_url['url'] = each_tag.get('href')
            tpm_str = each_url['url']
            each_url['id'] = tpm_str[tpm_str.rfind('/') + 1 :]
            each_url['name'] = each_tag.string
            each_month_attrs.append(each_url)
            # print(each_url)
    year_attrs.append(each_year_attr)

def download_each_month_picture(each_month):
    print('download_each_year_picture called')
    global custome_headers
    base_dir = 'F:\\download\\meizitu'
    for each_url in each_month:
        save_dir = '{}\\{}'.format(base_dir, each_url['id'])
        if (os.path.exists(save_dir) == False):
            os.mkdir(save_dir)
        else:
            continue
        # print(each_url)
        # 获取到最大页数
        content = requests.get(each_url['url'], custome_headers).content
        max_span = BeautifulSoup(content, 'lxml').find('div', class_='pagenavi').find_all('span')[-2].get_text()
        for page in range(1, int(max_span) + 1):
            # page_url = os.path.join(each_url['url'], str(page))
            page_url = '{}/{}'.format(each_url['url'], page)
            content = requests.get(page_url, custome_headers).content
            img_url = BeautifulSoup(content, 'lxml').find('div', 'main-image').find('img').get('src')
            print(img_url)
            name = '{}\\{}'.format(save_dir, img_url[img_url.rfind('/') + 1 :])
            print(name)

            # save to dir
            content = requests.get(img_url, custome_headers).content
            with open(name, "ab") as outfile:
                outfile.write(content)

# 开始下载图集, 数据结构，年-月-url列表
# print(len(year_attrs))
for each_year in year_attrs:
    for each_month in each_year:
        t = threading.Thread(target=download_each_month_picture, args=(each_month,))
        t.start()
        time.sleep(2)
