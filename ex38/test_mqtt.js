onst TOPIC = "testTopic"; // 主題
var client = false;

$(function () {
  // 建立物件
  client = new Paho.MQTT.Client("ws://localhost:9001/", "mqtt01");

  // 連接MQTT伺服器，並指定連接的事件處理函式
  client.connect({
    onSuccess: onConnect,
  });

  // 收到訊息時的事件處理函式
  client.onMessageArrived = onMessageArrived;

  $("#mqtt_pub").click(function () {
    publish_message();
  });
});

// 事件處理：成功連接 MQTT 伺服器
function onConnect() {
  console.log("onConnect then subscribe topic");
  client.subscribe(TOPIC); // 訂閱主題
}

// 事件處理：收到訊息
function onMessageArrived(message) {
  console.log("onMessageArrived:" + message.payloadString);

  // 訊息顯示在網頁上
  $("#mqtt_receive").text(message.payloadString);
}

// 發布訊息
function publish_message() {
  var input_text = $("#mqtt_text");
  var payload = input_text.val(); // 訊息負載

  console.log("publish message : " + payload);

  var message = new Paho.MQTT.Message(payload); // 建立物件
  message.destinationName = TOPIC; // 設定主題
  client.send(message); // 發布

  input_text.val("");
}
