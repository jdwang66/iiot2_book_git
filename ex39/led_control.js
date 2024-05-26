let color1 = "";
let color2 = "";
let color3 = "";

let CommandTopic = "control/leds/";
let ResultTopic = "control/results/leds/";
let client = false;

$(function () {
  jscolor.trigger("input");

  // 建立物件
  client = new Paho.MQTT.Client("ws://localhost:9001/", "mqtt01");

  // 連接MQTT伺服器，並指定連接的事件處理函式
  client.connect({
    onSuccess: onConnect,
  });

  // 收到訊息時的事件處理函式
  client.onMessageArrived = onMessageArrived;

  $("#led-1").change(function () {
    value = color1;
    $("#message-led-1").text("LED Color is set to " + value);
    $("#status-led-1").css({ fill: value });
    publish_message(color1, 1);
  });

  $("#led-2").change(function () {
    value = color2;
    $("#message-led-2").text("LED Color is set to " + value);
    $("#status-led-2").css({ fill: value });
    publish_message(color2, 2);
  });

  $("#led-3").change(function () {
    //value = $("#led-3").val();
    value = color3;
    $("#message-led-3").text("LED Color is set to " + value);
    $("#status-led-3").css({ fill: value });
    publish_message(color3, 3);
  });
});

function update(picker) {
  color1 = picker.toHEXString();
}

function update2(picker) {
  color2 = picker.toHEXString();
}

function update3(picker) {
  color3 = picker.toHEXString();
}

// 事件處理：成功連接 MQTT 伺服器
function onConnect() {
  console.log("onConnect then subscribe topic");
  $("#status").text("Connected with the MQTT Server");
  for (let i = 1; i < 4; i++) {
    client.subscribe(ResultTopic + i); // 訂閱主題
  }
}

// 事件處理：收到訊息
function onMessageArrived(message) {
  console.log(
    "MessageArrived:[" + message.destinationName + "]" + message.payloadString
  );

  if (!message.destinationName.startsWith(ResultTopic)) {
    return;
  }

  var ledNumber = message.destinationName.replace(ResultTopic, ""); // 取出led編號

  var payload = JSON.parse(message.payloadString);

  if (ledNumber && payload.Color) {
    $("#receive-led-" + ledNumber).text("Receive: " + payload.Color);
  }
}

// 發布訊息
function publish_message(color, ledId) {
  console.log("Send " + color1 + " to LED #1");
  var payload = {
    Color: color,
  };

  payloadString = JSON.stringify(payload);
  message = new Paho.MQTT.Message(payloadString);
  message.destinationName = CommandTopic + ledId;
  message.qos = 0;

  console.log(
    "publish message:[" + message.destinationName + "]" + payloadString
  );

  client.send(message);
}
