#define ldr A0
#define led1 15
#define sw1 16
long lasttime = 0;
int checksw1;
int i;

float ADC_value = 0.0048828125;

void setup() {
Serial.begin(9600);
pinMode(led1, OUTPUT);
pinMode(ldr, INPUT);
pinMode(sw1, INPUT_PULLUP);

digitalWrite(led1, 1);
}

void loop() {
float ldr_data = analogRead(ldr);
int lux =
int((250.000000/(ADC_value*ldr_d
ata))-50.000000);
long now = millis();
if (now - lasttime > 5000) {
lasttime = now;
Serial.print("Light Value = ");
Serial.print(lux);
Serial.println(" Lux unit");

delay(500);
}
bool readsw1 = digitalRead(sw1);
if (checksw1 != readsw1){
if (readsw1 == 0){
i++;
}
checksw1 = readsw1;
delay(1);
}
if (i == 1){
digitalWrite(led1, 0);
}
if (i == 2){

digitalWrite(led1, 1);
}
if (i == 3){
i=1;
}
delay(1);
