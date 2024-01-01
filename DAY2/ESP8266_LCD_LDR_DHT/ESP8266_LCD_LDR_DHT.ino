#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 0
#define DHTTYPE DHT22
#define ldr A0
LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHTTYPE);
float ADC_value = 0.0048828125;
void setup()
{
Serial.begin(9600);
pinMode(ldr, INPUT);
lcd.init();
lcd.backlight();
dht.begin();
lcd.clear();
}

void loop()
{
float h = dht.readHumidity();
int t = dht.readTemperature();
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);
lcd.setCursor(0, 0);
lcd.print("humi=");
lcd.setCursor(5, 0);
lcd.print(h);
lcd.setCursor(7, 0);
lcd.print(",temp=");
lcd.setCursor(13, 0);
lcd.print(t);
lcd.setCursor(0, 1);
lcd.print("light = ");
lcd.setCursor(8, 1);
lcd.print(lux);
lcd.setCursor(11, 1);
lcd.print(" lux");
delay(1000);
}
