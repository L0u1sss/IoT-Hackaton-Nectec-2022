int LED2 = 19;
int LED3 = 18;
int LED4 = 5;
void setup() {
 pinMode(LED2,OUTPUT);
 pinMode(LED3,OUTPUT);
 pinMode(LED4,OUTPUT);
}


void loop() {
  digitalWrite(LED2,HIGH);
  digitalWrite(LED3,HIGH);
  digitalWrite(LED4,HIGH);
  delay(500);
  for (int i=0 ; i<3 ; i++){
 digitalWrite(LED2,LOW);
 delay(500);
 digitalWrite(LED2,HIGH);
 delay(500);
  }
  for (int i=0 ; i<5 ; i++){
 digitalWrite(LED3,LOW);
 delay(500);
 digitalWrite(LED3,HIGH);
 delay(500);
  }
  for (int i=0 ; i<2 ; i++){
 digitalWrite(LED4,LOW);
 delay(500);
 digitalWrite(LED4,HIGH);
 delay(500);
  }
  for (int i=0 ; i<3 ; i++){
 digitalWrite(LED2,LOW);
 digitalWrite(LED3,LOW);
 digitalWrite(LED4,LOW);
 delay(500);
 digitalWrite(LED2,HIGH);
 digitalWrite(LED3,HIGH);
 digitalWrite(LED4,HIGH);
 delay(500);
  }
}
