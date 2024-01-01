#define led1 15
#define led 2
#define ldr A0
float ADC_value = 0.0048828125;

void setup() {
  Serial.begin(9600);
pinMode(led1, OUTPUT);
pinMode(ldr, INPUT);
for(int i = 0; i < 3; i++) {
  digitalWrite(led1,LOW);
  digitalWrite(led,LOW);
  delay(500);
  digitalWrite(led1,HIGH);
  digitalWrite(led,HIGH);
  delay(500);
  }
}


void loop() {
float ldr_data = analogRead(ldr);
int lux = int((250.000000/(ADC_value*ldr_data))-50.000000);
Serial.print("Light Value = ");
Serial.print(lux);
Serial.println(" Lux unit");

if(lux>=150){
  digitalWrite(led,LOW);
}
if (lux<150){
  digitalWrite(led,HIGH);
}
delay(1000);
}
