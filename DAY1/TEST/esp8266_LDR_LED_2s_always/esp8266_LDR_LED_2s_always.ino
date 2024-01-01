#define led1 15
#define led 2
#define ldr A0
float ADC_value = 0.0048828125;



void setup() {
  Serial.begin(9600);
pinMode(led1, OUTPUT);
pinMode(led, OUTPUT);
pinMode(ldr, INPUT);
for(int i = 0; i < 3; i++) {
  digitalWrite(led1,LOW);
  delay(500);
  digitalWrite(led1,HIGH);
  delay(500);
  }
}


void loop() {
  static unsigned long time_1 = millis();
  static unsigned long time_2 = millis();
   if(millis() - time_1 > 2000){
    time_1 = millis();
    digitalWrite(led1,LOW);
    }
   if(millis() - time_2 > 4000){
    time_2 = millis();
    digitalWrite(led1,HIGH);
    }
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);
Serial.print("Light Value = ");
Serial.print(lux);
Serial.println(" Lux unit");

if(lux>=150){
  digitalWrite(led,LOW);
}
else if (lux<150) {
  digitalWrite(led,HIGH);
}

}
