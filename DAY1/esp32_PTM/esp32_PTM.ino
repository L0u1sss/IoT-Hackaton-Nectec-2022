#define PTM 34
void setup()
{
Serial.begin(9600);
pinMode(PTM,OUTPUT);
}
void loop()
{
int sensorValue = analogRead(34);
Serial.print("ADC 10 bit = ");
Serial.print(sensorValue);
float volts = 5.00*(float)sensorValue/4095.00;
Serial.print(" , Voltage = ");
Serial.print(volts,2);
Serial.println(" V");
delay(1);
}
