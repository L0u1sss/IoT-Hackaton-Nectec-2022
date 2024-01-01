#include <ESP8266WiFi.h>
#include <PubSubClient.h>
const char* ssid = "it1";
const char* password = "sbtvc2565";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "80b801b5-e116-4136-a9ce-c07772870d1b";
const char* mqtt_username = "LPLvsHX1BgJSfnofUWd4QXWsj6c9NSkY";
const char* mqtt_password = "wuZO3rXFSS4g#08K(gKGP!S#Zw#MpgbB";
WiFiClient espClient;
PubSubClient client(espClient);
void reconnect() {
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
if (client.connect(mqtt_Client, mqtt_username,
mqtt_password)) {

Serial.println("connected");
}
else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println("try again in 5 seconds");
delay(5000);
}
}
}
void setup() {
Serial.begin(9600);
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
}
void loop() {
if (!client.connected()) {
reconnect();
}
client.loop();
}
