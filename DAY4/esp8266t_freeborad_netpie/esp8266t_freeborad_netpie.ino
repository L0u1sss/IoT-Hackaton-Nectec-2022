#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
const char* ssid = "it1";
const char* password = "sbtvc2565";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "432d5927-0628-4c31-8632-6a8eecae51a2";
const char* mqtt_username = "HA7Y56jdQvA1WNw7ao7fTH9nN7wUVc1i";
const char* mqtt_password = "D8LYv-$XYp0hejEQjP!khJ_$Ieq41sJi";
WiFiClient espClient;
PubSubClient client(espClient);
#define ldr A0
float ADC_value = 0.0048828125;
char msg[150];
#define DHTPIN 0
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
#define LED1 15
long lastMsg = 0;
int value = 0;

void reconnect() {
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
Serial.println("connected");
client.subscribe("@msg/led");
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
if (String(topic) == "@msg/led") {
if (message == "on") {
digitalWrite(LED1, 0);
client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"on\"}}");
Serial.println("LED ON");
}
else if (message == "off") {
digitalWrite(LED1, 1);
client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"off\"}}");
Serial.println("LED OFF");
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
client.setCallback(callback);
pinMode(ldr, INPUT);
dht.begin();
pinMode(LED1, OUTPUT);
digitalWrite(LED1, 1);
}

void loop() {
if (!client.connected()) {
reconnect();
}
client.loop();
long now = millis();
if (now - lastMsg > 5000) {
float ldr_data = analogRead(ldr);
int lux = int((250.000000 / (ADC_value * ldr_data)) - 50.000000);
int humidity = dht.readHumidity();
int temperature = dht.readTemperature();
lastMsg = now;
String data = "{\"data\": {\"light\":" + String(lux) + ", \"temperature\":" + String(temperature) + ", \"humidity\":\"" + String(humidity) + "\"}}";
Serial.println(data);
data.toCharArray(msg, (data.length() + 1));
client.publish("@shadow/data/update", msg);
}
delay(1);
}
