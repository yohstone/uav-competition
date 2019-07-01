 #-*- coding:utf-8 -*-
 # 登陆获取授权码
from urllib import parse,request
import json
textmod = {"login": "ceshi01","password":"123"}
#json串数据使用
textmod = json.dumps(textmod).encode(encoding='utf-8')
#普通数据使用
#textmod = parse.urlencode(textmod).encode(encoding='utf-8')
print(textmod)
#输出内容:b'{"params": {"user": "admin", "password": "zabbix"}, "auth": null, "method": "user.login", "jsonrpc": "2.0", "id": 1}'
header_dict = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Trident/7.0; rv:11.0) like Gecko',"Content-Type": "application/json"}
url='http://antiuav.tonghangyun.com.cn:9876/platform/auth'
req = request.Request(url=url, data=textmod, headers=header_dict)
res = request.urlopen(req)
res = res.read()
print(res)
#输出内容:b'{"jsonrpc":"2.0","result":"37d991fd583e91a0cfae6142d8d59d7e","id":1}'
#print(res.decode(encoding='utf-8'))
#输出内容:{"jsonrpc":"2.0","result":"37d991fd583e91a0cfae6142d8d59d7e","id":1}