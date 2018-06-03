<!-- TOC -->

- [json使用](#json使用)
    - [js.loads()导出字典](#jsloads导出字典)
    - [js.dumps()导出字符串](#jsdumps导出字符串)
        - [输出层数](#输出层数)
        - [输出特定编码的字符串](#输出特定编码的字符串)

<!-- /TOC -->

# json使用
[参考链接](https://www.cnblogs.com/wangyayun/p/6699184.html?utm_source=tuicool&utm_medium=referral)

## js.loads()导出字典
json.loads(conent)

## js.dumps()导出字符串
json.dumps(obj)，通常用来将字典数据转换成python的数据，参数还有其他类型。

### 输出层数
输出四层：indent = 4
js_data = json.dumps(js_load, sort_keys=True, indent=4)

### 输出特定编码的字符串
涉及中文编码问题，所以如果不是要使用分层来显示数据，还是直接输出json.loads之后的字典数据就好了。
js_str = json.dumps(js_all)


