<!-- TOC -->

- [urllib使用](#urllib使用)
    - [加载模块](#加载模块)
    - [request](#request)
        - [添加自定义头部](#添加自定义头部)
        - [设置请求的方法](#设置请求的方法)
        - [添加请求的参数信息](#添加请求的参数信息)
        - [通过urlopen(req)来打开一个request类型](#通过urlopenreq来打开一个request类型)
    - [response](#response)
        - [基础的应答信息](#基础的应答信息)
    - [请求示例](#请求示例)
        - [通过url简单访问get请求](#通过url简单访问get请求)
        - [添加自定义头部的post请求](#添加自定义头部的post请求)
- [修改openner属性](#修改openner属性)
    - [debug调试模式](#debug调试模式)
        - [修改openner的属性](#修改openner的属性)
        - [使用opener来访问](#使用opener来访问)
    - [设置代理](#设置代理)
    - [使用cookie来访问url](#使用cookie来访问url)
        - [添加urllib中相应的库](#添加urllib中相应的库)
        - [访问数据时，将源站返回的cookie保存下来](#访问数据时将源站返回的cookie保存下来)
        - [将cookie保存到文件](#将cookie保存到文件)
        - [从文件中取用cookie](#从文件中取用cookie)
- [异常捕获](#异常捕获)
    - [添加相应的库](#添加相应的库)
    - [异常分类](#异常分类)

<!-- /TOC -->

******************************************************
# urllib使用
[参考链接]()
## 加载模块
import urllib
from urllib import request

## request
request数据可以携带url信息，自定义头部信息，以及需要上传的数据信息
可以直接使用urlopen(req)来打死一个url类型
其实headers是一个字典类型，应该包含key:value的具体头部
### 添加自定义头部
如：headers = {'x-mark': 'value1'}
### 设置请求的方法
```
req = request.Request(url, method='PUT')
```
### 添加请求的参数信息
### 通过urlopen(req)来打开一个request类型
```
values = {
    'from': 'zh',
    'to': 'en',
    'query': '中文',
    'transtype': 'translang',
    'simple_means_flag': '3'
}
data = urllib.parse.urlencode(values).encode('utf-8')
req = request.Request(post_url, data, headers)
resp = request.urlopen(req)
```

## response
### 基础的应答信息
urlopen()函数返回的类型就是response
返回应答码: resp.getcode()
返回请求的url: resp.geturl()
返回应答头部: resp.info()
返回实体内容： resp.read()

*******************************************************
## 请求示例
### 通过url简单访问get请求
```
get_url = "http://www.baidu.com/index.html"
resp =  request.urlopen(get_url) #返回一个：response类型的数据
print(resp.getcode())
```
### 添加自定义头部的post请求
**数据内容要使用urlencode(values).encode('utf-8')来先转换成url的参数类型**，其中values是指字典数据的具体内容。
```
post_url = "http://fanyi.baidu.com/"
headers = {
    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 \
        (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36'
}
values = {
    'from': 'zh',
    'to': 'en',
    'query': '中文',
    'transtype': 'translang',
    'simple_means_flag': '3'
}
data = urllib.parse.urlencode(values).encode('utf-8')
data = urllib.parse.urlencode(values).encode('utf-8')
req = request.Request(post_url, data, headers)
resp = request.urlopen(req)
```


***************************************************
# 修改openner属性
## debug调试模式
### 修改openner的属性
主要是通过修改opener的debug等级属性来实现
```
httpHandler = request.HTTPHandler(debuglevel=1)
httpsHandler = request.HTTPSHandler(debuglevel=1)
#设置新的openner
opener = request.build_opener(httpHandler, httpsHandler)
```
### 使用opener来访问
```
#直接通过opener来访问url
resp = opener.open(url)
# 通过加载到标准的open中来实现
#request.install_opener(opener)
#resp = request.urlopen('http://www.baidu.com')
```

## 设置代理
设置代理主要是要通过设置ProxyHandler，来传入代理服务器的Ip和端口，然后也是通过修改opener的属性来修改urlopen()的行为状态
```
enable_proxy = False
proxy_handler = urllib.request.ProxyHandler({"http" : "http://some-proxy.com:8080"})
null_proxy_handler = urllib.request.ProxyHandler({})

if enable_proxy:
    opener = urllib.request.build_opener(proxy_handler)
else:
    opener = urllib.request.build_opener(null_proxy_handler)
urllib.request.install_opener(opener)
response = urllib.request.urlopen(url)
print(response.read().decode("utf8"))
```

*****************************************************
## 使用cookie来访问url
### 添加urllib中相应的库
from urllib import request
from urllib import parse
from http import cookiejar

### 访问数据时，将源站返回的cookie保存下来
1、声明一个CookieJar对象实例来保存cookie
2、HTTPCookieProcessor对象来创建cookie处理器
3、通过handler来构建opener
4、此处的open方法同request的urlopen方法，也可以传入request
```
cookie = cookiejar.CookieJar()
handler = request.HTTPCookieProcessor(cookie)
opener = request.build_opener(handler)
resp = opener.open(url)
for item in cookie:
    print("name = {0} ".format(item.name), end="")
    print("name = {0} ".format(item.value))
```

### 将cookie保存到文件
使用MozillaCookieJar来传入要保存的文件路径
```
filename = "cookie.txt"
cookie = cookiejar.MozillaCookieJar(filename)
handler = request.HTTPCookieProcessor(cookie)
opener = request.build_opener(handler)
resp = opener.open(url)
cookie.save(ignore_discard=True, ignore_expires=True)
```

### 从文件中取用cookie
```
cookie = cookiejar.MozillaCookieJar()
cookie.load(filename, ignore_discard=True, ignore_expires=True)

req = request.Request(url)
opener = request.build_opener(request.HTTPCookieProcessor(cookie))
resp = opener.open(req)
```

# 异常捕获
## 添加相应的库
from urllib import error

## 异常分类
URLError, HTTPError,
```
url = "http://blog.csdn.net/cqcrejjj"
req = urllib.request.Request(url)
try:
    resp = urllib.request.urlopen(req)
except error.URLError as e:
    if (hasattr(e, "reason")):  #加入 hasattr属性提前对属性进行判断
        print("URLError:{0},{1}".format(e.code, e.reason))
except error.HTTPError as e:
    print("HTTPError:{0},{1}".format(e.code, e.reason))
else:
    print("OK:" + resp.geturl())
```