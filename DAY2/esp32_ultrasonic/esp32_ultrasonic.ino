int ultra_out = 13;
int ultra_range = 12;

void setup() {
Serial.begin(9600);
pinMode(ultra_range, OUTPUT);
digitalWrite(ultra_range, LOW);
pinMode(ultra_out, INPUT);
}
void loop() {
unsigned int val_ultra;
val_ultra = analogRead(ultra_out);
long cm;
cm = microsecondsToCentimeters(long(val_ultra));
Serial.print("Ultrasonic Distance : ");
Serial.print(cm);
Serial.println(" cm");
delay(1000);
}

long microsecondsToCentimeters(long microseconds)
{
return microseconds / 29 / 2;
}
