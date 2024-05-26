import paho.mqtt.client as mqtt
import json

host = "localhost"
port = 9001

CommandTopic = "control/leds/"
ResultTopic = "control/results/leds/"
topicFilters=[]

# 建立連線後的回呼函式
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))  
    for i in range(1,4):
        topicFilters.append((CommandTopic + str(i),0))
    
    print(f'subcribe: {topicFilters}')

	# 每次連線後，重新設定訂閱主題
    client.subscribe(topicFilters)

# 接收訊息的回呼函式
def on_message(client, userdata, msg):
	# 印出接收訊息
    topic=msg.topic
    payload = msg.payload.decode('utf-8')
    print(f"Receive message: [{topic}] {payload}")
	
	# payload json字串轉為Python dict
    dict=json.loads(payload)  
    color=dict['Color']  # 取出color

	# 建立resultPayload dict
    resultPayload={}
    resultPayload['Color']=color

    ledId=msg.topic.replace(CommandTopic,"")  # 取出ledId

	# 建立發布主題
    topic = ResultTopic+ledId  

	# resultPayload dict轉json字串
    payload=json.dumps(resultPayload)  
    print(f"publish message: [{topic}] {payload}")
    
	# 發布訊息
    client.publish(topic, payload, 0)

# 建立mqtt Client物件
client = mqtt.Client("mqtt02", transport="websockets")

# 設定建立連線回呼函式
client.on_connect = on_connect

# 設定接收訊息回呼函式
client.on_message = on_message

# 連線至MQTT伺服器
print("MQTT Connect...")
client.connect(host, port, 60)

# 進入無窮處理迴圈
client.loop_forever()
