#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define ldr A0

LiquidCrystal_I2C lcd(0x27, 16, 2);

float ADC_value = 0.0048828125;
void setup()
{
Serial.begin(9600);
pinMode(ldr, INPUT);
lcd.init();
lcd.backlight();
lcd.clear();

}
void loop()
{
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-
50.000000);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Data on I-Kit");
lcd.setCursor(0, 1);
lcd.print("light = ");
lcd.setCursor(8, 1);
lcd.print(lux);
lcd.setCursor(11, 1);
lcd.print(" lux");
delay(1000);
}
