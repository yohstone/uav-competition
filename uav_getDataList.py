 #-*- coding:utf-8 -*-
 # 获取某队上传过的数据
import urllib 
import requests
import json
import ssl
import time
import datetime

before = int(time.time()) - 3600*4  #4小时前
fromTime = time.strftime("%Y%m%d%H%M%S", time.localtime(before) )

toTime = time.strftime("%Y%m%d%H%M%S", time.localtime(int( time.time() ) ) )#秒级时间戳，现在
#toTime = datetime.datetime.now().strftime("%Y%m%d%H%M%S") #第二种转换方法

id = "T123"
timerange = fromTime + '-' + toTime
url = "https://antiuav.tonghangyun.com.cn:9093/dc/aircraft-offsets/{}/{}/antiuav".format(id,timerange)
#url = "https://antiuav.tonghangyun.com.cn:9093/dc/aircraft-offsets/"+id+"/"+timerange+"/antiuav" #第二种方法
#url = "https://antiuav.tonghangyun.com.cn:9093/dc/aircraft-offsets/%s/%s/antiuav"%(id,timerange) #第三种方法

header_dict = {
				"Content-Type" : "application/json",
				"Authorization" : "JWT eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZGVudGl0eSI6IjViNjk0MzRkZmQ2YzE1MmIwZDNiMmFjYSIsImlhdCI6MTU1NzY3NDUyNCwibmJmIjoxNTU3Njc0NTI0LCJleHAiOjE1NTc3NjA5MjR9.wrnFO4c5elPOHm-1ekTUz3AwVPcbxidYvAPe_sfFo_o"
				}

res = requests.get(url, headers=header_dict, verify=False)

#print(res.request.headers)
print(res.json())

