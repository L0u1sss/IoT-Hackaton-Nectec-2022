#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <DHT.h>

#define DHTPIN 0
#define DHTTYPE DHT22
#define ldr A0
#define led1 15

LiquidCrystal_I2C lcd(0x27, 16, 2);
float ADC_value = 0.0048828125;
DHT dht(DHTPIN, DHTTYPE);
int checksw1;
int i=0;

void setup() {
Serial.begin(9600);
dht.begin();
lcd.init();
lcd.backlight();
pinMode(led1,OUTPUT);
}

void loop() {

//ใช้DHT
float h = dht.readHumidity();
float t = dht.readTemperature();
float f = dht.readTemperature(true);
//ใช้LDR
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);


//tempC
lcd.clear();
digitalWrite(led1,HIGH);
lcd.setCursor(0, 0);
if (t>=25){
  lcd.print("Temperature High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80&&lux>=500){
  lcd.print("All Data High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80){
  lcd.print("Temp,Humi High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&lux>=500){
  lcd.print("Temp,Light High");
  digitalWrite(led1,LOW);
}
else if (h>=80&&lux>=500){
  lcd.print("humi,Light High");
  digitalWrite(led1,LOW);
}
else{
  lcd.print("IoT Training");
}
lcd.setCursor(0, 1);
lcd.print("Temperature = ");
lcd.print(t);
lcd.println("°C");
delay(10000);


//humi
lcd.clear();
digitalWrite(led1,HIGH);
lcd.setCursor(0, 0);
if (h>=80){
  lcd.print("Humidity High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80&&lux>=500){
  lcd.print("All Data High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80){
  lcd.print("Temp,Humi High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&lux>=500){
  lcd.print("Temp,Light High");
  digitalWrite(led1,LOW);
}
else if (h>=80&&lux>=500){
  lcd.print("humi,Light High");
  digitalWrite(led1,LOW);
}
else{
  lcd.print("IoT Training");
}
lcd.setCursor(0, 1);
lcd.print("Humidity = ");
lcd.print(h);
lcd.println("%H");
delay(10000);


//tempF
lcd.clear();
digitalWrite(led1,HIGH);
lcd.setCursor(0, 0);
if (t>=25){
  lcd.print("Temperature High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80&&lux>=500){
  lcd.print("All Data High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80){
  lcd.print("Temp,Humi High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&lux>=500){
  lcd.print("Temp,Light High");
  digitalWrite(led1,LOW);
}
else if (h>=80&&lux>=500){
  lcd.print("humi,Light High");
  digitalWrite(led1,LOW);
}
else{
  lcd.print("IoT Training");
}
lcd.setCursor(0, 1);
lcd.print("Temperature = ");
lcd.print(f);
lcd.println("°F");
delay(10000);


//light
lcd.clear();
digitalWrite(led1,HIGH);
lcd.setCursor(0, 0);
if (lux>=500){
  lcd.print("Light High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80&&lux>=500){
  lcd.print("All Data High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&h>=80){
  lcd.print("Temp,Humi High");
  digitalWrite(led1,LOW);
}
else if (t>=25&&lux>=500){
  lcd.print("Temp,Light High");
  digitalWrite(led1,LOW);
}
else if (h>=80&&lux>=500){
  lcd.print("humi,Light High");
  digitalWrite(led1,LOW);
}
else{
  lcd.print("IoT Training");
}
lcd.setCursor(0, 1);
lcd.print("Light = ");
lcd.print(lux);
lcd.println("lux");
delay(10000);
}
