<!-- TOC -->

- [bs4库介绍](#bs4库介绍)
- [soup类型](#soup类型)
    - [使用解析器创建BeautifulSoup对象](#使用解析器创建beautifulsoup对象)
    - [soup主要的数据类型](#soup主要的数据类型)
    - [返回所有文字内容](#返回所有文字内容)
    - [获取到标准的缩进格式的输出](#获取到标准的缩进格式的输出)
    - [unicode压缩输出](#unicode压缩输出)
- [soup的解析器](#soup的解析器)
- [Tag类型](#tag类型)
    - [属性列表](#属性列表)
    - [函数列表](#函数列表)
        - [tag.get()获取标签里面具体值](#tagget获取标签里面具体值)
        - [查找父/兄弟标签节点](#查找父兄弟标签节点)
- [NavigableString字符串](#navigablestring字符串)
    - [属性及方法](#属性及方法)
- [注释类型comment](#注释类型comment)
- [查找Tag的方法](#查找tag的方法)
    - [按标签查找](#按标签查找)
    - [按keyword参数查找](#按keyword参数查找)
    - [按css类名的tag](#按css类名的tag)
    - [按文本内容查找](#按文本内容查找)
    - [限制层级查找](#限制层级查找)
    - [只查找直接子节点](#只查找直接子节点)
    - [正则表达式查找](#正则表达式查找)
    - [按自定义方法查找](#按自定义方法查找)
    - [css选择器select](#css选择器select)
- [修改soup](#修改soup)
    - [修改节点属性](#修改节点属性)
    - [增加子节点](#增加子节点)
    - [增加注释](#增加注释)
    - [清空内容](#清空内容)

<!-- /TOC -->

# bs4库介绍
Beautiful Soup 是一个可以从HTML或XML文件中提取数据的Python库.它能够通过你喜欢的转换器实现惯用的文档导航,查找,修改文档的方式.
说明文档： [BeautifulSoup](https://www.crummy.com/software/BeautifulSoup/bs4/doc/index.zh.html)


# soup类型
## 使用解析器创建BeautifulSoup对象
soup = BeautifulSoup(content, 'lxml')

## soup主要的数据类型
- Tag，标签
- NavigableString，封装的字符串
- BeautifulSoup，类本身
- Comment，注释类
基本都会接触的是Tag和NavigableString

## 返回所有文字内容
soup.get_text()

## 获取到标准的缩进格式的输出
通常用来格式化输出一个html的数据，无缩进格式的html数据，可以通过这种方式来缩进排序
soup.prettify()
```
<html>
    <head>
        ...
    </head>
</html>
```
## unicode压缩输出
unicode(soup.a)

# soup的解析器
BeautifulSoup(markup, "html.parser"),推荐使用lxml替代，需要安装Car语言库
BeautifulSoup(markup, "lxml")，唯一支持xml的解析器
BeautifulSoup(markup, ["lxml", "xml"])
BeautifulSoup(markup, "xml")
BeautifulSoup(markup, "html5lib")




# Tag类型
tag类型，即第一个标签组成的一个结构，bs4.element.Tag，如soup.p,soup.a。**Tag数据可以被修改。**。特别的，使用soup.p只能获取到第一个p的tag数据
## 属性列表
- name
- string
- strings，生成器，如果tag含有很多字符串，可以用.strings来循环获取
- stripped_strings可以去掉多余空白内容
- parent(tag类型), parent.name，父标签的Tag类型数据
- p['class'] = 'title',p后面的标签值<p class='title'>，获取异常时，返回KeyError错误类型。
- contents，将tag的子节点以列表的方式输出，**仅包含直接节点**
- children, 生成器，用来生成tag的子节点进行循环，for child in tag.children.**仅包含直接节点**
- descendants: 生成器，用来生成**子孙节点**进行循环。
- next_sibling和previous_sibling，兄弟节点，同一层级的兄弟节点
- .next_siblings 和 .previous_siblings, 生成器，循环获取兄弟节点
- .next_element 和 .previous_element，指向下一个被解析的对应（字符串或tag），不一定与.next_sibling相同
- .next_elements 和 .previous_elements


## 函数列表
### tag.get()获取标签里面具体值
tag_a.get('href') = 'url', <a href='url' title='title'></a>
tag_a.get('title') = 'title', <a href='url' title='title'></a>
tag_a.attrs，显示所有属性

### 查找父/兄弟标签节点
find_parents()和find_parent()
find_next_siblings() 和 find_next_sibling()
find_previous_siblings() 和 find_previous_sibling()
find_all_next() 和 find_next()
find_all_previous() 和 find_previous()

# NavigableString字符串
tag.string，封装之后的字符串，类型是bs4.element.NavigableString。

## 属性及方法
unicode()，直接转换成unicode字符串
replace_with(),替换函数

# 注释类型comment
```
"<b><!--Hey, buddy. Want to buy a used parser?--></b>"
soup.b.string的值就是'Hey, buddy. Want to buy a used parser?'
```
由开始的数据，soup.b.string就是comment类型，bs4.element.Comment

# 查找Tag的方法
## 按标签查找
find()查找返回第一个tag类型的数据，find_all()返回一个tag的list列表。
**find_all()，可以同时跟多种属性来混合查找**，最终查找到的结果是最外层的标签。
- soup.fild_all('a')
- soup.find('p', 'title') ,查找标签和子标签，如
```
<p class="title"><b>The Dormouse's story</b></p>
#soup.find('p', 'title')查找到的是<p>...</p>的整个串
```

## 按keyword参数查找
soup.find(id = 'link3')
```
<a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>
```

## 按css类名的tag
soup.find_all("a", class_="sister")
```
<a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>
```
## 按文本内容查找
soup.find_all("a", text="Elsie")
```
<a href="http://example.com/elsie" class="sister" id="link1">Elsie</a>
```

## 限制层级查找
soup.find_all("a", limit=2)

## 只查找直接子节点
soup.html.find_all("title", recursive=False)

## 正则表达式查找
for tag in soup.find_all(re.compile("^b"))
for tag in soup.find_all(re.compile(['a', 'b']))

## 按自定义方法查找
```
def has_class_but_no_id(tag):
    return tag.has_attr('class') and not tag.has_attr('id')
soup.find_all(has_class_but_no_id)
```

## css选择器select
通过tag标签逐层查找，soup.select("body a")
找到某个tag标签下的直接子标签，soup.select("head > title")
找到兄弟节点标签,soup.select("#link1 ~ .sister")
通过CSS的类名查找,soup.select(".sister")
通过tag的id查找,soup.select("#link1")
通过属性的值来查找,soup.select('a[href="http://example.com/elsie"]')


# 修改soup
## 修改节点属性
修改tag的名称和属性
修改 .string
## 增加子节点
append()
Tag.insert() 
insert_before() 和 insert_after()
BeautifulSoup.new_string() 和 .new_tag()
```
tag.insert(1, "but did not endorse ")
```
## 增加注释
```
new_comment = soup.new_string("Nice to see you.", Comment)
tag.append(new_comment)
```
## 清空内容
清空tag的内容，clear()
将tag移除文档树，extract()
移除节点并完全销毁，decompose()
替换某段内容，replace_with()
包装和解包装，wrap() unwrap()


