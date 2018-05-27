'''
Created on 2018年4月28日

@author: caiyx1
'''


import json
import time
import urllib
from urllib import request

city_list = ["北京"]
#city_list = ["北京", "上海", "厦门"]
weather_url_format = 'https://www.sojson.com/open/api/weather/json.shtml?city={0}'
for each_city in city_list:
    city_url = weather_url_format.format(urllib.parse.quote(each_city))
    print(each_city)
    
    req = request.Request(city_url)
    resp = request.urlopen(req)
    
    #用于解码json数据，输出为dict
    js_load = json.loads(resp.read().decode('utf-8'))
    
    #按四层json来打印数据,输出为str
    #js_data = json.dumps(js_load, sort_keys=True, indent=4)
    #print(js_data)
    
    try:
        forecast = js_load['data']['forecast']
        cur_time = time.strftime("%d", time.localtime()) #获取到当前日期的时间
        #print("current date = {}".format(cur_time))
        for cur_date in forecast:   #each str is dict
            if cur_time in cur_date['date']:
                #print(cur_date)
                print(cur_date['date'])
                print(cur_date['type'])
                print(cur_date['high'])
                print(cur_date['low'])
                print("{0}:{1}".format(cur_date['fx'], cur_date['fl']))
                print(cur_date['notice'])
                #print(cur_date['error']) #获取到异常时抛出
    except:
        print("天气格式获取异常")  
