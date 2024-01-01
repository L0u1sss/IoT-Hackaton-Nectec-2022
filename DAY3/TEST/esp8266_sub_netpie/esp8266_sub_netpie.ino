#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "it1";
const char* password = "sbtvc2565";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "143b6050-0b66-48be-bb33-da632db2f116";
const char* mqtt_username = "aXxg5QTkRsgQEgs67HC4V5nwGgxMLVqz";
const char* mqtt_password = "BopoeI08Kw)2rDnmmqGmqr1CzGL6aJHg";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
Serial.println("connected");
client.subscribe("@msg/test2");
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
client.setCallback(callback);
}

void loop() {

if (!client.connected()) {
reconnect();
}
client.loop();

}
