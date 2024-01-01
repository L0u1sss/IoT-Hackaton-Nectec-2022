#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTphalat 0
#define DHTTYPE DHT22
#define led 2
DHT dht(DHTphalat, DHTTYPE);
#define ldr A0

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
  dht.begin();
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
  pinMode(led,OUTPUT);
  digitalWrite(led,1);
  pinMode(ldr, INPUT);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  int ldr_data = analogRead(ldr);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  String data = String(humidity) + "," + String(temperature)+ "," + String(ldr_data); // 50,25
  Serial.println(data);
  data.toCharArray(msg, (data.length() + 1));
  client.publish("phalat/data", msg);
  delay(2000);

}
