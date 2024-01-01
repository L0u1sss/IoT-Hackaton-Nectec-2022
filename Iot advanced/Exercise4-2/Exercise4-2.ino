#include <WiFi.h>
#include <PubSubClient.h>
#define led 19
#define ptm 34

const char* ssid = ":D";
const char* password = "bigblackgun";
const char* mqtt_server = "192.168.246.11";
const int mqtt_port = 1883;
const char* mqtt_Client = "esp-8266-phalat";
const char* mqtt_username = "phalat";
const char* mqtt_password = "12345678";
long lastMsg = 0;
char msg[150];
int lastState;

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("control/led");
    } else {
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

  if (String(topic) == "control/led" ) {
    if (message == "ON"){
      digitalWrite(led, 0);
      Serial.println("LED ON");
      client.publish("control/led/status", "LED ON");
    }
    else if (message == "OFF"){
      digitalWrite(led, 1);
      Serial.println("LED OFF");
      client.publish("control/led/status", "LED OFF");
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(ptm, INPUT);
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
  digitalWrite(led, 1);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int vr = analogRead(34);
  long now = millis();
  if (now - lastMsg > 2000) {
    int Resistant = analogRead(34);
    lastMsg = now;
    String data = String(Resistant);
    Serial.println(data);
    data.toCharArray(msg, (data.length() + 1));
    client.publish("phalat/data", msg);
  }
  delay(1000);
}
