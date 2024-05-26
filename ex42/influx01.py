import influxdb_client
import os
from influxdb_client import Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS
import random
import datetime
from dotenv import load_dotenv

# 載入環境變數
load_dotenv()

# 取得 influxdb token
token = os.environ.get("INFLUXDB_TOKEN")

# 定義變數
bucket = "mydb2"
org = "iof"
url = "http://localhost:8086"


# 初始化 write client
client = influxdb_client.InfluxDBClient(url=url, token=token, org=org)
write_api = client.write_api(write_options=SYNCHRONOUS)

# 現在時間
x1=datetime.datetime.now()

# 2小時前的時間
x1 = x1 + datetime.timedelta(hours=-2)

for i in range(120):
    timestamp=int(datetime.datetime.timestamp(x1))
    t=random.randint(20,22)
    h=random.randint(50,55)
    co=random.randint(0,20)    
    point = (
        Point("mqtt").tag("sensor","temp").field("temp", t)
        .time(timestamp, WritePrecision.S),
        Point("mqtt").tag("sensor", "hum").field("hum", h)
        .time(timestamp,WritePrecision.S),
        Point("mqtt").tag("sensor", "co").field("co", co)
        .time(timestamp, WritePrecision.S),
    )

    # 寫入 influxDB
    write_api.write(bucket=bucket, org=org, record=point)

    # 增加 1 分鐘
    x1=x1+datetime.timedelta(minutes=1)  # days, hours, minutes 
    
