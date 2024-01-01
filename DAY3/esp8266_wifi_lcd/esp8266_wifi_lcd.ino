#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
char* ssid = "it1";
char* password = "sbtvc2565";
void setup()
{
Serial.begin(9600);
lcd.init();
lcd.backlight();
lcd.clear();
Serial.println("Starting...");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED)
{
delay(250);
Serial.print(".");
lcd.setCursor(0, 0);
lcd.print("ConnectingtoWiFi");
}
lcd.setCursor(0, 0);
lcd.print("WiFi connected");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
}
void loop()
{
}
