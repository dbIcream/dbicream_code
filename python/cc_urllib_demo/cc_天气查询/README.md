<!-- TOC -->

- [天气查询](#天气查询)
    - [使用到的库](#使用到的库)
    - [查询的网站](#查询的网站)
    - [获取到json数据](#获取到json数据)
    - [将数据转换成字典](#将数据转换成字典)
    - [json数据分析](#json数据分析)
        - [分析数据结构](#分析数据结构)
        - [要输出的内容](#要输出的内容)
    - [查询过于频繁时的异常](#查询过于频繁时的异常)

<!-- /TOC -->

# 天气查询

## 使用到的库
- json
- requests
 
## 查询的网站
www.sojson.com提供的查询接口，返回数据是json数据，所以只要针对json数据进行转换成字典数据之后就可以得到我们想要的数据了。
查询接口示例：https://www.sojson.com/open/api/weather/json.shtml?city=北京'

## 获取到json数据
如果用的是urllib库，可能要对url进行encode之后才能够正常识别
```
resp = requests.get(city_url)
content = resp.content  #bytes类型
```

## 将数据转换成字典
```
js_dict = json.loads(content)
```

## json数据分析
### 分析数据结构
```
city:
count:
data:
    forecast:
            0:{date:, sunrise:, high:, low:, sunset:, fi:, fx:, notice:, type:}
            1,2,3,4
date:
message:
status:
```
### 要输出的内容
我们需要的天气信息，都在forecast的数据中，这是一个列表，里面有从今天算起，总共5天的天气数据，每个天气数据又是一个字典。所以我们要循环获取到每个数据，js_dict['data']['forecast'][0] - js_dict['data']['forecast'][4]。
```
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
```

## 查询过于频繁时的异常
当请求过于频繁时，这个网站会返回其他的错误信息。练习的时候可以使用其他的天气查询网站的接口来练习，效果好一点。