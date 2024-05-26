import influxdb_client
import os
from influxdb_client import InfluxDBClient, Point, WritePrecision
from influxdb_client.client.write_api import SYNCHRONOUS
from dotenv import load_dotenv

# 載入環境變數
load_dotenv()
token = os.environ.get("INFLUXDB_TOKEN")

# 設定變數
org = "iof"
url = "http://localhost:8086"

# 初始化 query client
client = influxdb_client.InfluxDBClient(url=url, token=token, org=org)
query_api = client.query_api()

# 建立 query
query = """
from(bucket: "mydb2")
|> range(start: -2h)
|> filter(fn: (r) => r._measurement == "mqtt")
"""

# 執行 query
tables = query_api.query(query=query, org=org)

# 印出 query 結果
results = []
for table in tables:
    for record in table.records:
        results.append(
            (record.get_field(), record.get_value()))

print(results)

# 建立 query, 計算平均
query2 = """
from(bucket: "mydb2")
|> range(start: -2h)
|> filter(fn: (r) => r._measurement == "mqtt")
|> mean()
"""

# 執行 query
tables = query_api.query(query=query2, org=org)

# 印出結果
results = []
for table in tables:
    for record in table.records:
        results.append(
            (record.get_field(), record.get_value()))

print(results)
