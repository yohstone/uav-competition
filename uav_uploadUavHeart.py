 #-*- coding:utf-8 -*-
 # 使用授权码上传心跳包
import urllib 
import requests
import json
import ssl
import time


time = int(time.time()) #秒级时间戳

textmod = {
	"ID": "T123", 
	"Timestamp": time
}
print(textmod)

#json串数据使用
textmod = json.dumps(textmod).encode(encoding='utf-8')
#普通数据使用
#textmod = parse.urlencode(textmod).encode(encoding='utf-8')
#print(textmod)
#输出内容:b'{"params": {"user": "admin", "password": "zabbix"}, "auth": null, "method": "user.login", "jsonrpc": "2.0", "id": 1}'
header_dict = {
				"Content-Type" : "application/json",
				"Authorization" : "JWT eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGl0eSI6IjViNjk0MzRkZmQ2YzE1MmIwZDNiMmFjYSIsImlhdCI6MTU1NzY3NDUyNCwibmJmIjoxNTU3Njc0NTI0LCJleHAiOjE1NTc3NjA5MjR9.wrnFO4c5elPOHm-1ekTUz3AwVPcbxidYvAPe_sfFo_o"
				}
url='https://antiuav.tonghangyun.com.cn:9093/dc/antiuav/probe-pings'


res = requests.post(url, data=textmod,  headers=header_dict, verify=False)

#print(res.request.headers)
print(res.json())

