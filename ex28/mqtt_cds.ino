#include "WiFiS3.h"
#include "arduino_secrets.h"
#include <PubSubClient.h>

#define cds_topic "sensor/cds"
#define led_topic "sensor/led"

// cds
const byte cdsPin = A0;
int cdsValue = 0;

// led
const byte ledPin = 2;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

const char* mqtt_server = "192.168.1.119";

int status = WL_IDLE_STATUS;
WiFiClient wifi_client;
PubSubClient client(wifi_client);

void setup() {
  Serial.begin(9600);
  while (!Serial) {}  // wait for serial port to connect. Needed for native USB port only

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");   
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);   
    status = WiFi.begin(ssid, pass);  
    delay(10000);
  }
  
  printWifiStatus();

  analogReadResolution(14);  // 變更解析度為 14 位元
  pinMode(ledPin,OUTPUT);   

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
 
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    if (client.connect("MQTT_cds")) {
      Serial.println("connected");

      // subscribe      
      client.subscribe(led_topic);
    } else {
      Serial.print("MQTT connection failed, retry count: ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Input Message arrived [");
  Serial.print(topic);
  Serial.print(" ]");
  Serial.print((char)payload[0]);

  if ((char)payload[0] == '1') {
    digitalWrite(ledPin, HIGH);
  } else if ((char)payload[0] == '0') {
    digitalWrite(ledPin, LOW);
  } else {
    Serial.print("value error");
  }
  Serial.println();
}

long lastMsg=0;
void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
  long now=millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    cdsValue = analogRead(cdsPin);  //讀取光敏電阻類比電壓輸入
    Serial.print("cds Vaule: ");
    Serial.println(cdsValue);

    char buf[4];
    sprintf(buf, "%d", cdsValue);
    client.publish(cds_topic, buf);    
  }
}

void printWifiStatus() { 
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
