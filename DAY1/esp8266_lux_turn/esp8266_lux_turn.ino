#define ldr A0
float ADC_value = 0.0048828125;

void setup()
{
Serial.begin(9600);
pinMode(ldr, INPUT);
}

void loop()
{
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);
Serial.print("Light Value = ");
Serial.print(lux);
Serial.println(" Lux unit");
delay(1000);
if (lux < 100){
Serial.println("turn off");
}
else if (lux >= 100) {
Serial.println("turn on");
}
}
