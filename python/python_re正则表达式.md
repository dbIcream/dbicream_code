<!-- TOC -->

- [正则表达式的使用](#正则表达式的使用)
    - [匹配规则](#匹配规则)
        - [贪婪匹配](#贪婪匹配)
        - [匹配单个字符规则](#匹配单个字符规则)
        - [匹配多个字符](#匹配多个字符)
        - [边界匹配](#边界匹配)
        - [逻辑、分组匹配、特殊构造](#逻辑分组匹配特殊构造)
- [Re模块](#re模块)
    - [匹配使用的函数](#匹配使用的函数)
        - [匹配模式：flags参数](#匹配模式flags参数)
    - [match匹配结果](#match匹配结果)
        - [调用方式](#调用方式)
        - [结果的索引](#结果的索引)
        - [查看结果中的分组](#查看结果中的分组)
        - [指定分组对应的索引位置](#指定分组对应的索引位置)

<!-- /TOC -->

# 正则表达式的使用
[参考链接](https://cuiqingcai.com/977.html)

## 匹配规则
### 贪婪匹配
注意贪婪匹配和非贪婪匹配，贪婪匹配总是尝试匹配尽的字符，非贪婪则相反。例如ab*如果是想找abbbc，贪婪匹配将找到abbb，非贪婪将找到a

### 匹配单个字符规则
|  语法  |        说明         | 表达式实例 | 完整匹配的字符串 |
| ------ | ------------------- | ---------- | ---------------- |
| .      | 匹配任意字符        | a.c        | abc              |
| \\     | 转义字符            | a\\c       | a\c              |
| [...]  | 匹配字符集          | a[bcd]e    | abe ace ade      |
| \d  \D | 匹配数/非数字       | a\dc a\Dc  | a1c abc          |
| \s \S  | 空白字符/非空白字符 | a\sc a\Sc  | a c  abc         |
| \w \W  | 字词字符/非单词字符 | a\wc a\Wd  | abc  a c         |

### 匹配多个字符
| 语法  |          说明           | 表达式实例 | 完整匹配的字符串 |
| ----- | ----------------------- | ---------- | ---------------- |
| *     | 匹配前一个字符0或无限次 | abc*       | ab abccc         |
| +     | 匹配前一个字符至少1次   | abc+       | abc abccc        |
| ?     | 匹配前一个字符0或1次    | abc?       | ab abc           |
| {m}   | 匹配前一个字符m次       | ab{2}c     | abbc             |
| {m,n} | 匹配前一个字符m到n次    | ab{2,3}c   | abbc abbbc       |


### 边界匹配
| 语法 |                   说明                   | 表达式实例 | 完整匹配的字符串 |
| ---- | ---------------------------------------- | ---------- | ---------------- |
| ^    | 匹配字符串开头，多行匹配时匹配每一个结尾 | ^abc       | abc              |
| $    | 匹配字符串结尾                           | abc$       | abc              |
| \A   | 仅匹配字符串开头                         | \Aabc      | abc              |
| \Z   | 仅匹配字符串结尾                         | abc\Z      | abc              |
| \b   | 匹配\w到\W之间                           | a\b!bc     | a!bc             |
| \B   | [^\b]                                    | a\Bbc      | abc              |

### 逻辑、分组匹配、特殊构造
[参考链接](https://cuiqingcai.com/977.html)
|     语法      |          说明          |        表达式实例        | 完整匹配的字符串 |
| ------------- | ---------------------- | ------------------------ | ---------------- |
| 竖线          | 左右表达式任意匹配一个 | abc竖线def               | abc def          |
| (...)         | 分组                   | (abc){2} a(123 竖线456)c | abcabc a456c     |
| (?P<name>...) | 分组添加另名           | (?P<id>\d)abc(?P=id)     | 1abc1            |
| (?P=name)     | 引用另名               | (?P<id>\d)abc(?P=id)     | 1abc1            |
| (?#注释内容)  | 添加解析注释           | abc(?#注释内容)123       | abc123           |

***************************************************

# Re模块
## 匹配使用的函数
1、生成pattern对象，re.compile(string[,flag])  
2、匹配所有： **re.match(pattern, string[, flags])**
3、查找： re.search(pattern, string[, flags])
4、拆分： re.split(pattern, string[, maxsplit])
5、查找全部： re.findall(pattern, string[, flags])
6、返回结果的迭代器：re.finditer(pattern, string[, flags]) 
7、返回替换后的每一个字符串： re.sub(pattern, repl, string[, count])
8、添加替换次数： re.subn(pattern, repl, string[, count])
```
import re
pattern1 = re.compile('hello')
pattern2 = re.compile('.*\d')
# 有分组的时候groups才会有值，match4.groups()才有值
pattern3 = re.compile('(.*\d)(.*\d)(.*\d)')
match1 = pattern1.match('hello world!')
match2 = pattern1.match('hello1 hello2 hello345')
match3 = pattern2.match('hello1 hello2 hello345')
match4 = pattern3.match('hello1 hello2 hello345')
list1 = pattern1.findall('hello1 hello2 hello345')
list2 = re.findall(pattern2, 'hello1 hello2 hello3')
```

### 匹配模式：flags参数
参数flag是匹配模式，取值可以使用按位或运算符’|’表示同时生效，比如re.I | re.M。
可选值有：
1、忽略大小写： re.I(全拼：IGNORECASE): 
2、多行模式： re.M(全拼：MULTILINE): 改变'^'和'$'的行为图）
3、点任意匹配模式： re.S(全拼：DOTALL): 点任意匹配模式，改变'.'的行为
4、使预定字符类 \w \W \b \B \s \S 取决于当前区域设定： re.L(全拼：LOCALE): 
5、使预定字符类 \w \W \b \B \s \S \d \D 取决于unicode定义的字符属性： re.U(全拼：UNICODE):
6、详细模式： re.X(全拼：VERBOSE): 这个模式下正则表达式可以是多行，忽略空白字符，并可以加入注释。

## match匹配结果
### 调用方式
m = re.match(pattern,'hello')
m = pattern('hello')
string: 匹配时使用的文本。
re: 匹配时使用的Pattern对象。

### 结果的索引
pos: 文本中正则表达式开始搜索的索引，通常是0
endpos: 文本中正则表达式结束搜索的索引，通常为len(pattern.string)
lastindex: 最后一个分组的索引，无分组时为None
lastgroup: 最后一个被捕获的分组的**别名**，如果这个分组没有别名或者没有被捕获的分组，将为None。

### 查看结果中的分组
group: 获取一个或多个分组的字符串，指定多个参数时返回元组。
group()/group(0), group(1,2), group(2)
groups([default]):以元组形式返回全部分组截获的字符串。相当于调用group(1,2,…last)。default表示没有截获字符串的组以这个值替代，默认为None。
groupdict([default]):
返回以**有别名的组**的别名为键、以该组截获的子串为值的字典，没有别名的组不包含在内。default含义同上。
expand(template):
将匹配到的分组代入template中然后返回。template中可以使用\id或\g、\g引用分组，但不能使用编号0。\id与\g是等价的；但\10将被认为是第10个分组，如果你想表达\1之后是字符’0’，只能使用\g0。

```
p = re.compile('(?P<alias1>.*11) (?P<alias2>.*22) (?P=alias1) (.*33)')
m = p.match('hello11 h22 hello11 hello33')
print(m.lastindex)  #3
print(m.lastgroup)  #最后一个hello33没有匹配上，所以没有值，即None
print(m.group())    #'hello11 h22 hello11 hello33'
print(m.groups())   #('hello11', 'h22', 'hello33')
print(m.groupdict()) #{'alias1': 'hello11', 'alias2': 'h22'}
print(m.expand(r'\1 \2')) #hello11 h22
```

### 指定分组对应的索引位置
1、获取groups[i]的开始序号，match1.start(i)
2、获取groups[i]的结束序号，match1.start(i)
3、同时获取groups[i]的开始和结束序号，match1.span(i)
**序号要在groups()的范围内，否则会报错**









