#include "WiFiS3.h"
#include "arduino_secrets.h"
#include <DFRobot_DHT11.h>
#include <PubSubClient.h>

#define DHT11_PIN 7
#define humi_topic "sensor/humi"
#define temp_topic "sensor/temp"

DFRobot_DHT11 DHT;

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

const char* mqtt_server = "192.168.1.119";

int status = WL_IDLE_STATUS;
WiFiClient wifi_client;
PubSubClient client(wifi_client);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
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

  client.setServer(mqtt_server, 1883);
 
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    if (client.connect("MQTT_dht")) {
      Serial.println("connected");
    } else {
      Serial.print("MQTT connection failed, retry count: ");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

long lastMsg=0;
int temp=0;
int humi=0;

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  long now=millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;

    DHT.read(DHT11_PIN);  
    temp = DHT.temperature;
    humi = DHT.humidity;

    Serial.print("temp:");
    Serial.print(temp);
    Serial.println(" °C");  

    Serial.print("humi:");
    Serial.print(humi);
    Serial.println(" %");

    client.publish(temp_topic, String(temp).c_str(), true);
    client.publish(humi_topic, String(humi).c_str(), true);
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
