#define ldr A0
void setup()
{
Serial.begin(9600);
pinMode(ldr, INPUT);
}
void loop()
{
int ldr_data = analogRead(ldr);
Serial.print("LDR Sensor Value = ");
Serial.println(ldr_data);
delay(1000);
}
