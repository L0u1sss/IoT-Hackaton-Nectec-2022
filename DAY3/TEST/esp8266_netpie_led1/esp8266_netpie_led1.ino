#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define led1 15

const char* ssid = "it1";
const char* password = "sbtvc2565";
const char* mqtt_server = "mqtt.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "ff3b752f-50cd-4d96-9b45-75469c9accc0";
const char* mqtt_username = "FWeBmxYj1EgcewNvth9oXXLy9uNQghZM";
const char* mqtt_password = "7bC~xDlUl)eAni8FTch7OZY0E7oAZmH#";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
Serial.println("connected");
client.subscribe("@msg/esp8266/led1");
}
else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println("try again in 5 seconds");
delay(5000);
}
}
}

void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("Message arrived [");
Serial.print(topic);
Serial.print("] ");
String message;
for (int i = 0; i < length; i++) {
message = message + (char)payload[i];
}
Serial.println(message);
if (String(topic) == "@msg/esp8266/led1" ){
  if (message == "on"){
    digitalWrite(led1, 0);
    Serial.println("Led1 ON");
  }
  else if (message == "off"){
    digitalWrite(led1, 1);
    Serial.println("Led1 OFF");
  }
}
}

void setup() {
Serial.begin(9600);
pinMode(led1,OUTPUT);
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
client.setServer(mqtt_server, mqtt_port);
client.setCallback(callback);
}

void loop() {

if (!client.connected()) {
reconnect();
}
client.loop();

}
