#!/usr/bin/python
#coding=utf-8

'''
    文件名称：
    文件描述：
        脚本实现自动抓取视频网站上的图片：https://www.eporner.com/category/60fps/
    设计：
        1、获取导航第N页的所有视频链接，https://www.eporner.com/category/60fps/num
        2、筛选出第N页所有评分大于85的视频链接
        3、通过视频链接获取到播放页，并从播放页中获取到480P的下载链接
        4、通过下载链接获取到文件名，判断文件名是否已经存在，不存在时将下载链接下载下来并保存

    说明：
        1、该网站一天同一个ip最多下载30个视频，所以需要设置上限

'''

import os
import re
import urllib
from urllib import request
import threading
import time

MAX_PAGE_NUM = 20             #页码数的最大值
LOWEST_PERCENT = 90           #设置下载的最低好评率
MAX_SUCCESS_DOWNLOAD_NUM = 30 #设置一次下载最大的文件下载个数
g_downloaded_file_num = 0     #记录总共下载的文件个数
log_time = time.time()

'''
获取一个网页内容
'''
def get_page_content(page_url):
        req = request.Request(page_url)
        page = request.urlopen(req)
        html = page.read()
        content = html.decode('utf-8')
        return content

'''
添加一行数据到文件中
'''
def log_url_to_file(path, content):
    with open(path, "a") as outfile:
        outfile.write(content)


def save_video_with_relative_play_url(video_play_relative_url):
    save_dir = 'D:\\download\\fps60'
    global logger
    global log_time
    log_file = save_dir + '\\' + log_time
    video_absolute_url = "https://www.eporner.com" + video_play_relative_url
    content = get_page_content(video_absolute_url)
    pattern_href = re.compile(
        '<div.*?id="hd-porn-dload">.*?<strong>720p:.*?</strong>.*?<a.*?href="(.*?)".*?</a>.*?</div>', re.S)
    tmp_list = re.findall(pattern_href, content)
    download_relative_url = tmp_list[0]

    logger.debug(download_relative_url)
    split_list = str(download_relative_url).split('/') #获取到文件名，url中的最后一个参数
    filename = split_list[len(split_list)-1]
    logger.debug(filename)
    if (os.path.exists(os.path.join(save_dir, filename)) == False):    #判断文件是否已经下载过了，没有下载过时，下载并保存
        path = save_dir + '\\' + filename #获取到绝对路径
        absolute_down_url = "https://www.eporner.com" + download_relative_url #获取到下载链接的绝对路径
        logger.info('%s save to file %s'%(absolute_down_url, path))
        log_url_to_file(absolute_down_url, log_file)
        urllib.request.urlretrieve(absolute_down_url, path) #获取网络资源到本地
        logger.info('file "%s" downloaded!!' %filename)
    else:
        logger.info('%s is already exists, downloading next file...'%filename)


def download_each_video(video_play_relative_url):
    # 传入相对路径
    try:
        logger.info('downloading... %s!' % (video_play_relative_url))
        save_video_with_relative_play_url(video_play_relative_url)
        logger.info("downloaded videos: %s success!" % (video_play_relative_url))

    except urllib.error.URLError as url_error:
        if hasattr(url_error, "code"):
            logger.info(url_error.code)
        if hasattr(url_error, "reason"):
            logger.info(url_error.reason)
        logger.info("downloaded videos: %s failed" % (video_play_relative_url))

def download_each_page(page_num):
    global g_downloaded_file_num

    #获取到当前pagenum对应页面的所有视频链接
    base_url = 'https://www.eporner.com/category/60fps/'
    absolute_url = base_url + "%d/" % (page_num)
    content = get_page_content(absolute_url)
    pattern_href = re.compile('<div.*?class="mb".*?<div.*?</div>.*?<a.*?href="(.*?)".*?title="(.*?)".*?</a>.*?' +
                              '<div.*?<div.*?</div>.*?<div.*?class="mbrate">(.*?)</div>', re.S)
    lists = re.findall(pattern_href, content)

    down_list = []
    for each_list in lists:
        if (int(each_list[2].strip('%')) >= LOWEST_PERCENT):
            down_list.append(each_list)
    print('page%2d find %d video, %d is >= %d' %
          (page_num, len(lists), len(down_list), LOWEST_PERCENT))


    for each_list in down_list:
        # 传入相对路径
        g_downloaded_file_num = g_downloaded_file_num + 1
        if (g_downloaded_file_num > MAX_SUCCESS_DOWNLOAD_NUM):
            break
        t = threading.Thread(target=download_each_video, args=(each_list[0],))
        t.start()
        time.sleep(5)



def start_to_download():
    cur_page = 5
    while (True):
        max_page_num = 100
        if (cur_page < max_page_num and g_downloaded_file_num < MAX_SUCCESS_DOWNLOAD_NUM):
            print("downloading page%2d..." % (cur_page))
            download_each_page(cur_page)
        else:
            break
        cur_page = cur_page + 1
    logger.info("has already download %d videos"%(MAX_SUCCESS_DOWNLOAD_NUM))


start_to_download()


