#include <ESP8266WiFi.h>
#include <DHT.h>
#include <PubSubClient.h>
#define ldr A0
#define DHTPIN 0
#define DHTTYPE DHT22
#define led1 15


const char* ssid = "Yanaraika";
const char* password = "12345678";
const char* mqtt_server = "192.168.246.11";
const int mqtt_port = 1883;
const char* mqtt_Client = "esp-8266-phalat";
const char* mqtt_username = "phalat";
const char* mqtt_password = "12345678";

 
 char msg[150];
 
 DHT dht(DHTPIN, DHTTYPE);
 WiFiClient espClient;
 PubSubClient client(espClient);
 
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
   pinMode(led1, OUTPUT);
   digitalWrite(led1, HIGH);
 }
 
 void callback(char* topic, byte* payload, unsigned int length) {
   Serial.print("Message arrived [");
   Serial.print(topic);
   Serial.print("] ");
   String(message);
   for (int i = 0; i < length; i++) {
     message = message + (char)payload[i];
   }
   Serial.println(message);
 
   if (String(topic) == "phalat/led1") {
     if (message == "on") {
       digitalWrite(led1, LOW);
       Serial.println("LED ON");
       client.publish("phalat/led1/status1", "LED1 ON");
     } else if (message == "off") {
       digitalWrite(led1, HIGH);
       Serial.println("LED OFF");
       client.publish("phalat/led1/status1", "LED1 OFF");
     }
   }
 }
 
 void reconnect() {
   while (!client.connected()) {
     Serial.print("Attempting MQTT connection…");
     if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
       Serial.println("connected");
       client.subscribe("phalat/led1");
     } else {
       Serial.print("failed, rc=");
       Serial.print(client.state());
       Serial.println("try again in 5 seconds");
       delay(5000);
     }
   }
 }
  float ADC_value = 0.0048828125;
    boolean flag = 0;
  unsigned long pre = 0;
  long inter = 10000;
 void loop() {
   if (!client.connected()) {
     reconnect();
   }
   client.loop();
   unsigned long cur = millis();
  if(cur - pre > inter){
    pre = cur;
    flag = 1;
  }
  if(flag == 1){
      flag = 0;
    int value = analogRead(A0);
    int lux = int((250.000000/(ADC_value*value))-50.000000);
   float humidity = dht.readHumidity();
   float temperature = dht.readTemperature();
   String data = String(humidity) + "," + String(temperature)+","+String(lux); // 50,25
   Serial.println(data);
   data.toCharArray(msg, (data.length() + 1));
   client.publish("phalat/data", msg);
   client.publish("phalat/led", msg);
  }
 }
