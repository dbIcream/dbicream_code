<!-- TOC -->

- [参考链接](#参考链接)
- [属性](#属性)
- [方法](#方法)
- [实例](#实例)
    - [获取一个网页内容](#获取一个网页内容)
    - [内置json解析器](#内置json解析器)
    - [添加data构造post请求](#添加data构造post请求)
    - [设置代理连接](#设置代理连接)
- [Response对象](#response对象)
    - [属性](#属性-1)

<!-- /TOC -->

## 参考链接
[入门介绍-Requests库介绍](https://blog.csdn.net/shanzhizi/article/details/50903748)
## 属性


## 方法
|        方法        |              说明              |
| ------------------ | ------------------------------ |
| requests.request() | 构造一个请求，支撑以下各种方法 |
| requests.get()     | Get                            |
| requests.head()    | HEAD                           |
| requests.post()    | POST                           |
| requests.put()     | PUT                            |
| requests.patch()   | 提交局部修改请求PATCH          |
| requests.delete()  | DELETE                         |


## 实例
### 获取一个网页内容
```
resp = requests.get(url_of_all, headers = custome_headers)
content = resp.content
```
等价于用urllib的命令
```
# req = urllib.request.Request(url_of_all, headers = custome_headers)
# resp = urllib.request.urlopen(req)
# content = resp.read()
```
### 内置json解析器
```
r = requests.get('https://api.github.com/events')
r.json()
```

### 添加data构造post请求
```
payload = (('key1', 'value1'), ('key1', 'value2'))
r = requests.post('http://httpbin.org/post', data=payload)
print(r.text)
```

### 设置代理连接
[参考链接](https://blog.csdn.net/lw_power/article/details/77946852)
```
proxies = {
  "http": "http://10.10.1.10:3128",
  "https": "http://10.10.1.10:1080",
}
requests.get("http://www.zhidaow.com", proxies=proxies)
```

## Response对象
### 属性
|        属性         |              说明              |
| ------------------- | ------------------------------ |
| r.status_code       | 状态码                         |
| r.text              | 响应内容的字符串形式           |
| r.encoding          | header中猜测的响应内容编码方式 |
| r.apparent_encoding | 内容中分析中的响应编码方式     |
| r.content           | 二进制的内容                   |