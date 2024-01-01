#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "it1";
const char* password = "sbtvc2565";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "ff135e7a-e73e-4fc6-9096-d81e20d72744";
const char* mqtt_username = "5Az1WWmdGUZeHwWSFZW2pMxqs3rKZ2bv";
const char* mqtt_password = "q4WtoSzdvJ)w~s61irxw$L80IJsWsBET";

WiFiClient espClient;
PubSubClient client(espClient);

#define ldr A0
float ADC_value = 0.0048828125;
char msg[150];

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
pinMode(ldr, INPUT);
}

void loop() {
if (!client.connected()) {
reconnect();
}
client.loop();
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);
Serial.println("Light Value = " + String(lux) + " Lux unit");
String data = "{\"data\": {\"light\":" + String(lux) + "}}";
Serial.println(data);
data.toCharArray(msg, (data.length() + 1));
client.publish("@shadow/data/update", msg);
delay(5000);
}
