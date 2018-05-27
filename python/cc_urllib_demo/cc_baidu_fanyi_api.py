'''
Created on 2018年4月28日

@author: caiyx1
'''


from urllib import request
from urllib import parse
import json
import hashlib
import random


def translate_by_baidu(text, language_from = 'auto', language_to = 'zh'):
    base_url = 'http://api.fanyi.baidu.com/api/trans/vip/translate'
    app_id = '20180428000151628'
    salt = "{}".format(random.randint(32768, 65536))
    key = 'rYSPfae5DZJ_e3D_ZkQn'
    sign_str = app_id + text + salt + key
    
    md5_handler = hashlib.md5()
    sign = md5_handler.update(sign_str.encode(encoding='utf_8', errors='strict'))
    
    inquiry_url = base_url \
            + '?appid=' + app_id \
            + '&q=' + text \
            + '&from=' + language_from + '&to=' + language_to \
            + '&salt=' + salt \
            + '&sign=' + md5_handler.hexdigest() 
            
    try:
        resp = request.urlopen(inquiry_url)
        data = json.loads(resp.read())
        print('翻译前：' + data['trans_result'][0]['src'])
        print('翻译后：' + data['trans_result'][0]['dst'])
        
    except Exception as  e:
        print(e)
    
    
translate_by_baidu('cyan')    