# -*- coding:utf-8 -*-
#!/usr/local/bin/python3

import json
import time
import requests


# 天气查询示例： https://www.sojson.com/open/api/weather/json.shtml?city=北京
city_list = ["北京"]
#city_list = ["北京", "上海", "厦门"]
url_format = 'https://www.sojson.com/open/api/weather/json.shtml?city={0}'

for each_city in city_list:
    city_url = url_format.format(each_city)
    
    # req = request.Request(city_url)
    # resp = request.urlopen(req)
    resp = requests.get(city_url)
    content = resp.content  #bytes类型
    # print(content.decode('utf-8'))
    
    
    # 用于解码json数据，输出为dict
    js_dict = json.loads(content)
    # print(js_dict)
    
    #按四层json来打印数据,输出为str，涉及编码问题
    # js_data = json.dumps(js_dict, sort_keys=True, indent=4)
    # print(js_data)
    '''
    分析数据结构
    city:
    count:
    data:
        forecast:
                0:{date:, sunrise:, high:, low:, sunset:, fi:, fx:, notice:, type:}
                1,2,3,4
    date:
    message:
    status:

    '''
    
    try:
        forecast_dict = js_dict['data']['forecast']
        #获取到当前日期的时间，如03
        # today_time = time.strftime("%d", time.localtime())

        print(js_dict['city'])
        for i in range(len(forecast_dict)):   #each str is dict
            # print(forecast_dict[i])
            cur_day_weather = forecast_dict[i]
            print(cur_day_weather['date'], end=' : ')
            print(cur_day_weather['type'], end=',')
            print(cur_day_weather['low'], end='-')
            print(cur_day_weather['high'], end=' (')
            print(cur_day_weather['notice'], end=')\n')
            #print(each_wether['error']) #获取到异常时抛出
    except:
        print("天气格式获取异常")  
