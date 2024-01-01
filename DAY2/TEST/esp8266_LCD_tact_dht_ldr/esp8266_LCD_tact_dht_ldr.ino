#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <DHT.h>

#define sw1 16
#define led 2
#define DHTPIN 0
#define DHTTYPE DHT22
#define ldr A0

LiquidCrystal_I2C lcd(0x27, 16, 2);
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
lcd.init();
lcd.backlight();
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
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Train by I-Kit");
lcd.setCursor(0, 1);
lcd.print("Temperature = ");
lcd.print(t);
lcd.println("°C");
delay(500);
}
else if (i == 2){
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Train by I-Kit");
lcd.setCursor(0, 1);
lcd.print("Humidity = ");
lcd.print(h);
lcd.println("%H");
delay(500);
}
else if (i == 3){
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Train by I-Kit");
lcd.setCursor(0, 1);
lcd.print("Temperature = ");
lcd.print(f);
lcd.println("°F");
delay(500);
}
else if (i == 4){
  lcd.clear();
  lcd.setCursor(0, 0);
lcd.print("Train by I-Kit");
lcd.setCursor(0, 1);
lcd.print("Light = ");
lcd.print(lux);
lcd.println("lux");
delay(500);
}
else if (i == 5){
i=1;
}
if (readsw1 == 0){
  digitalWrite(led,LOW);
 }
else if (readsw1 == 1){
  digitalWrite(led,HIGH);
}

}
