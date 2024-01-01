#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <DHT.h>
#define led2 19
#define led3 18
#define led4 5
#define PTM 34

const char* ssid = "Yanaraika";
const char* password = "12345678";
const char* mqtt_server = "192.168.246.11";
const int mqtt_port = 1883;
const char* mqtt_Client = "esp-8266-phalat";
const char* mqtt_username = "phalat";
const char* mqtt_password = "12345678";

char msg[150];

WiFiClient espClient;
PubSubClient client(espClient);
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String(message);
  for (int i = 0; i < length; i++) {
    message = message + (char)payload[i];
  }
  Serial.println(message);

  if (String(topic) == "phalat/led2") {
    if (message == "on") {
      digitalWrite(led2, LOW);
      Serial.println("LED ON");
      client.publish("phalat/led2/status2", "LED2 ON");
    } else if (message == "off") {
      digitalWrite(led2, HIGH);
      Serial.println("LED OFF");
      client.publish("phalat/led2/status2", "LED2 OFF");
    }
  }
  if (String(topic) == "phalat/led3") {
    if (message == "on") {
      digitalWrite(led3, LOW);
      Serial.println("LED ON");
      client.publish("phalat/led3/status3", "LED3 ON");
    } else if (message == "off") {
      digitalWrite(led3, HIGH);
      Serial.println("LED OFF");
      client.publish("phalat/led3/status3", "LED3 OFF");
    }
  }
  if (String(topic) == "phalat/led4") {
    if (message == "on") {
      digitalWrite(led4, LOW);
      Serial.println("LED ON");
      client.publish("phalat/led4/status4", "LED4 ON");
    } else if (message == "off") {
      digitalWrite(led4, HIGH);
      Serial.println("LED OFF");
      client.publish("phalat/led4/status4", "LED4 OFF");
    }
  }
}

void setup() {
  Serial.begin(9600);
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
  pinMode(led2, OUTPUT);
  digitalWrite(led2, HIGH);
  pinMode(led3, OUTPUT);
  digitalWrite(led3, HIGH);
  pinMode(led4, OUTPUT);
  digitalWrite(led4, HIGH);
  pinMode(PTM,OUTPUT);
}



void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("phalat/led2");
      client.subscribe("phalat/led3");
      client.subscribe("phalat/led4");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
boolean flag = 0;
unsigned long pre = 0;
long inter = 1000;
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  unsigned long cur = millis();
  if (cur - pre > inter) {
    pre = cur;
    flag = 1;
  }
  if (flag == 1) {
    flag = 0;
    int vr1 = analogRead(A0);
    int vr2 = map(vr1, 0, 4095, 0, 5);
    Serial.println(vr2);
    String data = String(vr2); // 50,25
    Serial.println(data);
    data.toCharArray(msg, (data.length() + 1));
    client.publish("phalat/data2", msg);
  }
}
