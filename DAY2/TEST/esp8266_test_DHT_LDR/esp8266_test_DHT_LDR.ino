#include <DHT.h>

#define DHTPIN 0
#define DHTTYPE DHT22
#define ldr A0
#define led1 15
#define led 2
float ADC_value = 0.0048828125;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(9600);
pinMode(led1, OUTPUT);
pinMode(led, OUTPUT);
pinMode(ldr, INPUT);
dht.begin();
digitalWrite(led1,HIGH);
digitalWrite(led,HIGH);
}

void loop() {
float ldr_data = analogRead(ldr);
float t = dht.readTemperature();
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);
Serial.print("DHT22 Temperature: ");
Serial.print(t);
Serial.print(" °C ");
Serial.print("Light Value = ");
Serial.print(lux);
Serial.println(" Lux unit");
if(lux>=150){
  digitalWrite(led1,LOW);
}
if (lux<150){
  digitalWrite(led1,HIGH);
}
if (t>=25){
   digitalWrite(led,LOW);
    delay(200);
    digitalWrite(led,HIGH);
    delay(200);
  
  }
if (t<25){
  digitalWrite(led , HIGH);
}
delay(1000);
}
