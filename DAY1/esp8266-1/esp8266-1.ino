#define LED1 15
#define LED2 2
void setup() {
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);

}

void loop() {
digitalWrite(LED1, LOW);
delay(1000);
digitalWrite(LED1, HIGH);
delay(1000);
digitalWrite(LED2, LOW);
delay(1000);
digitalWrite(LED2, HIGH);
delay(1000);
}
