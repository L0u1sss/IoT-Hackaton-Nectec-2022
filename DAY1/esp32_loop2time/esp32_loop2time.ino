#define LED2 19
#define LED3 18
#define LED4 5

void setup()
{
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
}

void loop()
{
for (int i = 0; i < 2; i++){
digitalWrite(LED2, LOW);
delay(1000);
digitalWrite(LED2, HIGH);
delay(1000);
}
for (int i = 0; i < 3; i++){
digitalWrite(LED3, LOW);
delay(1000);
digitalWrite(LED3, HIGH);

delay(1000);
}
for (int i = 0; i < 4; i++){
digitalWrite(LED4, LOW);
delay(1000);
digitalWrite(LED4, HIGH);
delay(1000);
}
}
