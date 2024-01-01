#include <WiFi.h>
#include <PubSubClient.h>

char* ssid = "it1";
char* password = "sbtvc2565";
char* mqtt_server = "broker.netpie.io";
int mqtt_port = 1883;
char* mqtt_Client = "e8536a18-94a6-4b44-ab86-eb372d868b3e";
char* mqtt_username = "MPEaW1mYfyJVAA5LmwQhc9CQZ2V9DaZG";
char* mqtt_password = "yNb4DnN9j4V1BWh7VfeKC6fxI8#RgQx2";

WiFiClient espClient;
PubSubClient client(espClient);

char msg[150];

#define LED2 19
#define LED3 18
#define LED4 5
#define PTM 34

int Gas_analog = 35;

long lastMsg = 0;
int value = 0;

void reconnect() {
while (!client.connected()) {
Serial.print("Attempting MQTT connection...");
if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
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
digitalWrite(LED2, 0);
client.publish("@shadow/data/update", "{\"data\" : {\"led\" : \"on\"}}");
Serial.println("LED ON");
}
else if (message == "off") {
digitalWrite(LED2, 1);
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
pinMode(PTM,OUTPUT);
pinMode(Gas_analog, INPUT);
pinMode(LED2, OUTPUT);
digitalWrite(LED2, 2);
pinMode(LED3, OUTPUT);
digitalWrite(LED3, 3);
pinMode(LED4, OUTPUT);
digitalWrite(LED4, 4);
}

void loop() {
if (!client.connected()) {
reconnect();
}
client.loop();
int sensorValue = analogRead(34);
int gassensorAnalog = analogRead(Gas_analog);
long now = millis();
if (now - lastMsg > 5000) {

lastMsg = now;
String data = "{\"data\": {\"voltage\":" + String(sensorValue) + ", \"gas\":" + String(gassensorAnalog)+ "\"}}";
Serial.println(data);
data.toCharArray(msg, (data.length() + 1));
client.publish("@shadow/data/update", msg);
}
delay(1);
}
