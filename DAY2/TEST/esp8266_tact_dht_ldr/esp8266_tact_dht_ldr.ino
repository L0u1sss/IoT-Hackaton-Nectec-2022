#include <DHT.h>

#define sw1 16
#define led 2
#define DHTPIN 0
#define DHTTYPE DHT22
#define ldr A0

float ADC_value = 0.0048828125;
DHT dht(DHTPIN, DHTTYPE);
int checksw1;
int i=0;

void setup() {
Serial.begin(9600);
pinMode(sw1 ,INPUT_PULLUP);
pinMode(led,OUTPUT);
dht.begin();
digitalWrite(led, HIGH);
}

void loop() {
//ใช้DHT
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);
//ใช้LDR
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);
bool readsw1 = digitalRead(sw1);
 if ( checksw1 != readsw1 ){
if (readsw1 == 0){
i++;
}
checksw1 = readsw1;
}
else if (i == 1){
Serial.print("Light Value in the Room = ");
Serial.print(lux);
Serial.println("lux");
}
else if (i == 2){
Serial.print("Humidity Value in the Room = ");
Serial.print(h);
Serial.println("%H");
}
else if (i == 3){
Serial.print("Temperature Value in the Room = ");
Serial.print(t);
Serial.println("°C");
}
else if (i == 4){
Serial.print("Temperature Value in the Room = ");
Serial.print(f);
Serial.println("°F");
}
else if (i == 7){
i=1;
}
if (readsw1 == 0){
  digitalWrite(led,LOW);
 }
else if (readsw1 == 1){
  digitalWrite(led,HIGH);
}
}
