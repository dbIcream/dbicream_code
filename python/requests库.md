<!-- TOC -->

- [获取一个网页内容](#获取一个网页内容)
- [内置json解析器](#内置json解析器)
- [添加data构造post请求](#添加data构造post请求)

<!-- /TOC -->
# 获取一个网页内容
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
# 内置json解析器
```
r = requests.get('https://api.github.com/events')
r.json()
```

# 添加data构造post请求
```
payload = (('key1', 'value1'), ('key1', 'value2'))
r = requests.post('http://httpbin.org/post', data=payload)
print(r.text)
```