'''
Created on 2018年5月4日

@author: caiyx1
'''

import urllib
from urllib import request
import re


page = 1
url_format = 'http://www.qiushibaike.com/hot/page/{0}'
get_url = url_format.format(page)
user_agent = 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) \
                Chrome/63.0.3239.132 Safari/537.36'

header_list = {'User-Agent' : user_agent}
try:
    '''
    先获取到当前的页面
    '''
    req = request.Request(get_url, headers = header_list)
    resp = request.urlopen(req)
    #print(resp.read())
    
    '''
    分析当前的页面，转码，提取
    
    '''
    content = resp.read().decode('utf-8')
#     print(content)
#     pattern = re.compile('<div.*?author">.*?<a.*?<img.*?>(.*?)</a>.*?<div.*?content">\
#             (.*?)<!--(.*?)-->.*?</div>(.*?)\
#             <div class="stats.*?class="number">(.*?)</i>', re.S)
    pattern = re.compile('<div class="author clearfix">.*?<h2>(.*?)</h2>.*?'
                         + '<span>(.*?)</span>.*?'
                         + 'class="number">(.*?)</i>', re.S)
    lists = re.findall(pattern, content)
    for item in lists:
        print(item[0])
        print(item[1])
        print(item[2])
    
       
except Exception as err:
    print(err)
    
    
'''
每个笑话的html例子
<div class="article block untagged mb15 typs_hot" id="qiushi_tag_120389099">


<div class="author clearfix">
<a href="/users/27941526/" target="_blank" rel="nofollow" style="height: 35px" onclick="_hmt.push(['_trackEvent','web-list-author-img','chick'])">

<img src="//pic.qiushibaike.com/system/avtnew/2794/27941526/thumb/20180504142039.JPEG?imageView2/1/w/90/h/90" alt="塞上燕脂凝夜紫">
</a>
<a href="/users/27941526/" target="_blank" onclick="_hmt.push(['_trackEvent','web-list-author-text','chick'])">
<h2>
塞上燕脂凝夜紫
</h2>
</a>
<div class="articleGender womenIcon">86</div>
</div>

<a href="/article/120389099" target="_blank" class="contentHerf" onclick="_hmt.push(['_trackEvent','web-list-content','chick'])">
<div class="content">
<span>


给闺女买的衣服鞋子上的小装饰，总是掉的七零八落。今天给她穿了新裙子，到幼儿园后时间还早，我趴窗户看她。<br>一个小女生对闺女说:“你裙子上的宝石（普通塑料珠子）好漂亮，能给我一个吗？”闺女二话不说抠掉一个给她。<br>小女生也不含糊，坐地上把自己凉鞋上的小水钻抠掉一个给了闺女……<br>俩人超默契！！！

</span>

</div>
</a>
<!-- 图片或gif -->


<div class="stats">
<!-- 笑脸、评论数等 -->


<span class="stats-vote"><i class="number">1268</i> 好笑</span>
<span class="stats-comments">
<span class="dash"> · </span>
<a href="/article/120389099" data-share="/article/120389099" id="c-120389099" class="qiushi_comments" target="_blank" onclick="_hmt.push(['_trackEvent','web-list-comment','chick'])">
<i class="number">9</i> 评论
</a>
</span>
</div>
<div id="qiushi_counts_120389099" class="stats-buttons bar clearfix">
<ul class="clearfix">
<li id="vote-up-120389099" class="up">
<a href="javascript:voting(120389099,1)" class="voting" data-article="120389099" id="up-120389099" rel="nofollow" onclick="_hmt.push(['_trackEvent','web-list-funny','chick'])">
<i></i>
<span class="number hidden">1282</span>
</a>
</li>
<li id="vote-dn-120389099" class="down">
<a href="javascript:voting(120389099,-1)" class="voting" data-article="120389099" id="dn-120389099" rel="nofollow" onclick="_hmt.push(['_trackEvent','web-list-cry','chick'])">
<i></i>
<span class="number hidden">-14</span>
</a>
</li>
<li class="comments">
<a href="/article/120389099" id="c-120389099" class="qiushi_comments" target="_blank" onclick="_hmt.push(['_trackEvent','web-list-comment01','chick'])">
<i></i>
</a>
</li>
</ul>
</div>
<div class="single-share">
<a class="share-wechat" data-type="wechat" title="分享到微信" rel="nofollow">微信</a>
<a class="share-qq" data-type="qq" title="分享到QQ" rel="nofollow">QQ</a>
<a class="share-qzone" data-type="qzone" title="分享到QQ空间" rel="nofollow">QQ空间</a>
<a class="share-weibo" data-type="weibo" title="分享到微博" rel="nofollow">微博</a>
</div>
<div class="single-clear"></div>


<a href="/article/120389099" class="indexGodCmt" onclick="_hmt.push(['_trackEvent','web_list_comment-popular','chick'])" rel="nofollow" target="_blank">
<div class="cmtMain">
<span class="cmt-god"></span>






<span class="cmt-name">gdufs96：</span>
<div class="main-text">
这么大方有礼貌的好孩子，想亲她们妈妈的跟在我后面排成一行
<div class="likenum">
<img src="//static.qiushibaike.com/images/newarticle/like@1.5.png?v=b7f830b3bb97b559891af61444d3b4ad">


22

</div>
</div>
</div>
</a>

</div>
'''