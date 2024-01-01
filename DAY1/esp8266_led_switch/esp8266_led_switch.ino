#define led1 15
#define led2 2
#define sw1 16
int checksw1;
int i=0;

void setup() {
Serial.begin(9600);
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT);
pinMode(sw1, INPUT_PULLUP);
digitalWrite(led1, 1);
digitalWrite(led2, 1);
}

void loop() {
bool readsw1 = digitalRead(sw1);
if ( checksw1 != readsw1 ){
if (readsw1 == 0){
i++;
}
checksw1 = readsw1;
delay(1);
}
if (i==1){
digitalWrite(led1 ,0);
}
else if (i == 2){
digitalWrite(led1, 1);

}
else if (i == 3){
digitalWrite(led2, 0);
}
else if (i == 4){
digitalWrite(led2, 1);
}
else if (i == 5){
digitalWrite(led1, 0);
digitalWrite(led2, 0);
}
else if (i == 6){
digitalWrite(led1, 1);
digitalWrite(led2, 1);

}
else if (i == 7){
i=1;
}
}
