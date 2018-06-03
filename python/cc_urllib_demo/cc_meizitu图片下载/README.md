<!-- TOC -->

- [项目介绍](#项目介绍)
- [用到的第三方库](#用到的第三方库)
- [分析网页结构](#分析网页结构)
    - [下载all页面](#下载all页面)
    - [分析结构](#分析结构)
        - [获取到每个图集的标题和url](#获取到每个图集的标题和url)
            - [图集页的层次分析](#图集页的层次分析)
            - [获取到年月标签的实现](#获取到年月标签的实现)
            - [按月份获取到图集列表](#按月份获取到图集列表)
            - [最后我们将每年的列表加入到年列表中](#最后我们将每年的列表加入到年列表中)
    - [下载列表中的每个图集](#下载列表中的每个图集)
        - [按月的粒度来创建线程下载](#按月的粒度来创建线程下载)
        - [分析下载的页面](#分析下载的页面)
            - [获取每个图集的最大页码](#获取每个图集的最大页码)
            - [获取到第个图集的第n页路径](#获取到第个图集的第n页路径)
            - [分析并获取到图片的url](#分析并获取到图片的url)
            - [下载url到指定目录](#下载url到指定目录)

<!-- /TOC -->

# 项目介绍
自动抓取并下载妹子图网站上的图片内容，详细图片可以直接上官网上查看。官网地址：www.mzitu.com。抓取的入口网页：http://www.mzitu.com/all    
介绍一下项目的主要实现过程：
- 先分析网站的格式，抓取到每个图集的网页资源
- 获取到图集的每张图片第n页的图片链接
- 多线程保存每张图片到本地目录下

# 用到的第三方库
- requests
- BeautifulSoup
- lxml解析器

# 分析网页结构
看网页的结构，层次比较明显，大致分为
```
- 年： year，对应标签<div class="year">2018年</div>
- 月： month，对应标签<div class="month">06月</div>
- 每日+图集名称： <a href="url" target="_blank">标题</a>
```

## 下载all页面
该网站在使用时，要添加有效的User-agent头部，否则无法返回正确的数据，所以我们需要自己构造一个字典类型的自定义头部列表。这里我们直接截取了一个chrome的UA头并添加
```
url_of_all = 'http://www.mzitu.com/all'
custome_headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/535.24 (KHTML, like Gecko) Chrome/19.0.1055.1 Safari/535.24'}
resp = requests.get(url_of_all, headers = custome_headers)
    content = resp.content
```

## 分析结构
### 获取到每个图集的标题和url
#### 图集页的层次分析
- year和archives竟然是分开的~~这个要按年获取就比较麻烦了,所以直接按月存取数据。
```
<div class="year">2018年</div>
<div class="archives">2018年</div>
    <p class="month">06月</p>
    <p class="url on"><a href="图集的url">图集说明</a></p>
    <p class="url"><a href="另一种图集的url">图集说明</a></p>
```

#### 获取到年月标签的实现
```
# 使用BeautifulSoup得到BeautifulSoup对象
soup = BeautifulSoup(content, 'lxml')
# 获取到年的节点位置，因为year和arch是两个并列书写，所以不好同时获取
arch_tags = soup.find_all('ul', 'archives')
for each_arch_tag in arch_tags:
    # 获取到月的节点位置
    each_year_attr = []
    month_tags = each_arch_tag.find_all('p', re.compile('month|url'))
    for each_month_tag in month_tags:
        # 获取到每月中的url， 并存入数组
        a_tags = each_month_tag.find_all('a')
        for each_tag in a_tags:
            # print(each_tag)
            each_url = {}
            each_url['url'] = each_tag.get('href')
            tpm_str = each_url['url']
            each_url['id'] = tpm_str[tpm_str.rfind('/') + 1 :]
            each_url['name'] = each_tag.string
            each_month_attrs.append(each_url)
```

#### 按月份获取到图集列表
我们前面保留了month的标签，所以在each_month_tag中，含有**url**的标签和**month**两种，month来区分月。
```
<p class="url">
<p class="month">
```
```
for each_month_tag in month_tags:
        # print(each_month_tag)
        if each_month_tag == None:
            continue
        if 'month' in each_month_tag['class']:
            if first_flag == True:
                each_month_attrs = []
                first_flag = False
            else:
                # print(each_month_attrs)
                each_year_attr.append(each_month_attrs)
                each_month_attrs = []
```

#### 最后我们将每年的列表加入到年列表中
```
for each_arch_tag in arch_tags:
    ...
    year_attrs.append(each_year_attr)
```
最终生成的一个按年区分的列表，
- year_attrs, 包含每一年的列表，year_attrs[0]，表示第一年，按加入的顺序，应该表示的是2018年
- year_attrs[0]里面的列表就表示每个月的url列表，year_attrs[0][0]表示12月，year_attrs[0][11]表示1月
- year_attrs[0][0]，就表示每个月里面的url列表，这边我保存了对应的id序号（应该是网站用来存在的id）和说明。
- year_attrs[0][0][0]，每个url节点是一个字典数据，year_attrs[0][0][0]有三个key，分别是'id','url','name'。


## 下载列表中的每个图集
### 按月的粒度来创建线程下载
也可以每个图集创建一个线程来下载，但是那样数量会比较多，所以我按月的粒度来创建线程。
```
for each_year in year_attrs:
    for each_month in each_year:
        t = threading.Thread(target=download_each_month_picture, args=(each_month,))
        t.start()
        time.sleep(2)
```

### 分析下载的页面
#### 获取每个图集的最大页码
每个图集的第一页，都会有一个第几页的索引，可以看到索引通常是"上一页,1,2,3...49,下一页"，每个页码用的是<span>标签，所以我们获取到倒数第二个<span>标签就可以获取到最大页码。
```
content = requests.get(each_url['url'], custome_headers).content
        max_span = BeautifulSoup(content, 'lxml').find('div', class_='pagenavi').find_all('span')[-2].get_text()
```
#### 获取到第个图集的第n页路径
特别的，直接用os.path.join会变成**http://www.mzitu.com/136967\2**，用requests.get会异常，所以我直接用手动加成**http://www.mzitu.com/136967/2**的格式。

#### 分析并获取到图片的url
每一页的主体图片在标签结构如下：
```
<div class="main-image">
    <img src="图片的url" alt="说明">
</div>    
```
#### 下载url到指定目录
指定目录可以通过每个图集的id来存在，结构会清晰一些
```
base_dir = 'F:\\download\\meizitu'
for each_url in each_month:
    save_dir = '{}\\{}'.format(base_dir, each_url['id'])
```
```
for page in range(1, int(max_span) + 1):
    # page_url = os.path.join(each_url['url'], str(page))
    page_url = '{}/{}'.format(each_url['url'], page)
    content = requests.get(page_url, custome_headers).content
    img_url = BeautifulSoup(content, 'lxml').find('div', 'main-image').find('img').get('src')
    print(img_url)
    name = '{}\\{}'.format(save_dir, img_url[img_url.rfind('/') + 1 :])
    print(name)

    # save to dir
    content = requests.get(img_url, custome_headers).content
    with open(name, "ab") as outfile:
        outfile.write(content)
```
